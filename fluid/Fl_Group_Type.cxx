// Fl_Group_Type.C

// Object describing an Fl_Group
// Probably also links to Fl_Window_Type.C

// Also the Fl_Tabs widget, with special stuff to select tab items
// and insure that only one is visible.

#include <FL/Fl.H>
#include <FL/Fl_Group.H>
#include <FL/fl_message.H>
#include "Fl_Widget_Type.H"

class igroup : public Fl_Group {
public:
  void resize(int,int,int,int);
  igroup(int x,int y,int w,int h) : Fl_Group(x,y,w,h) {Fl_Group::current(0);}
};
// Override group's resize behavior to do nothing to children:
void igroup::resize(int X, int Y, int W, int H) {
  Fl_Widget::resize(X,Y,W,H);
  redraw();
}

class Fl_Group_Type : public Fl_Widget_Type {
public:
  virtual const char *type_name() {return "Fl_Group";}
  Fl_Widget *widget(int x,int y,int w,int h) {
    igroup *g = new igroup(x,y,w,h); Fl_Group::current(0); return g;}
  Fl_Widget_Type *_make() {return new Fl_Group_Type();}
  Fl_Type *make();
  void write_code1();
  void write_code2();
  void add_child(Fl_Type*, Fl_Type*);
  void move_child(Fl_Type*, Fl_Type*);
  void remove_child(Fl_Type*);
  int is_parent() const {return 1;}
  int is_group() const {return 1;}
};
Fl_Group_Type Fl_Group_type;	// the "factory"

Fl_Type *Fl_Group_Type::make() {
  return Fl_Widget_Type::make();
}

void fix_group_size(Fl_Type *tt) {
  if (!tt || !tt->is_group()) return;
  Fl_Group_Type* t = (Fl_Group_Type*)tt;
  int X = t->o->x();
  int Y = t->o->y();
  int R = X+t->o->w();
  int B = Y+t->o->h();
  for (Fl_Type *nn = t->next; nn && nn->level > t->level; nn = nn->next) {
    if (!nn->is_widget() || nn->is_menu_item()) continue;
    Fl_Widget_Type* n = (Fl_Widget_Type*)nn;
    int x = n->o->x();	if (x < X) X = x;
    int y = n->o->y();	if (y < Y) Y = y;
    int r = x+n->o->w();if (r > R) R = r;
    int b = y+n->o->h();if (b > B) B = b;
  }
  t->o->resize(X,Y,R-X,B-Y);
}

extern int force_parent;

void group_cb(Fl_Widget *, void *) {
  // Find the current widget:
  Fl_Type *qq = Fl_Type::current;
  while (qq && (!qq->is_widget() || qq->is_menu_item())) qq = qq->parent;
  if (!qq || qq->level <= 1) {
    fl_message("Please select widgets to group");
    return;
  }
  Fl_Widget_Type* q = (Fl_Widget_Type*)qq;
  force_parent = 1;
  Fl_Group_Type *n = (Fl_Group_Type*)(Fl_Group_type.make());
  n->move_before(q);
  n->o->resize(q->o->x(),q->o->y(),q->o->w(),q->o->h());
  for (Fl_Type *t = Fl_Type::first; t;) {
    if (t->level != n->level || t == n || !t->selected) {
      t = t->next; continue;}
    Fl_Type *nxt = t->remove();
    t->add(n);
    t = nxt;
  }
  fix_group_size(n);
}

void ungroup_cb(Fl_Widget *, void *) {
  // Find the group:
  Fl_Type *q = Fl_Type::current;
  while (q && (!q->is_widget() || q->is_menu_item())) q = q->parent;
  if (q) q = q->parent;
  if (!q || q->level <= 1) {
    fl_message("Please select widgets in a group");
    return;
  }
  Fl_Type* n;
  for (n = q->next; n && n->level > q->level; n = n->next) {
    if (n->level == q->level+1 && !n->selected) {
      fl_message("Please select all widgets in group");
      return;
    }
  }
  for (n = q->next; n && n->level > q->level;) {
    Fl_Type *nxt = n->remove();
    n->insert(q);
    n = nxt;
  }
  delete q;
}

////////////////////////////////////////////////////////////////

#include <stdio.h>

void Fl_Group_Type::write_code1() {
  Fl_Widget_Type::write_code1();
}

void Fl_Group_Type::write_code2() {
  write_c("%so->end();\n", indent());
  if (resizable()) write_c("%sFl_Group::current()->resizable(o);\n", indent());
  Fl_Widget_Type::write_code2();
}

////////////////////////////////////////////////////////////////

#include <FL/Fl_Tabs.H>

class itabs : public Fl_Tabs {
public:
  void resize(int,int,int,int);
  itabs(int x,int y,int w,int h) : Fl_Tabs(x,y,w,h) {}
};
// Override group's resize behavior to do nothing to children:
void itabs::resize(int X, int Y, int W, int H) {
  Fl_Widget::resize(X,Y,W,H);
  redraw();
}

static const char tabs_type_name[] = "Fl_Tabs";

class Fl_Tabs_Type : public Fl_Group_Type {
public:
  virtual const char *type_name() {return tabs_type_name;}
  Fl_Widget *widget(int x,int y,int w,int h) {
    itabs *g = new itabs(x,y,w,h); Fl_Group::current(0); return g;}
  Fl_Widget_Type *_make() {return new Fl_Tabs_Type();}
  Fl_Type* click_test(int,int);
  void add_child(Fl_Type*, Fl_Type*);
  void remove_child(Fl_Type*);
};
Fl_Tabs_Type Fl_Tabs_type;	// the "factory"

// This is called when user clicks on a widget in the window.  See
// if it is a tab title, and adjust visibility and return new selection:
// If none, return o unchanged:

Fl_Type* Fl_Tabs_Type::click_test(int x, int y) {
  Fl_Tabs *t = (Fl_Tabs*)o;
  Fl_Widget *a = t->which(x,y);
  if (!a) return 0; // didn't click on tab
  // okay, run the tabs ui until they let go of mouse:
  t->handle(FL_PUSH);
  Fl::pushed(t);
  while (Fl::pushed()==t) Fl::wait();
  return (Fl_Type*)(t->value()->user_data());
}

// This is called when o is created.  If it is in the tab group make
// sure it is visible:

void Fl_Group_Type::add_child(Fl_Type* cc, Fl_Type* before) {
  Fl_Widget_Type* c = (Fl_Widget_Type*)cc;
  Fl_Widget* b = before ? ((Fl_Widget_Type*)before)->o : 0;
  ((Fl_Group*)o)->insert(*(c->o), b);
  o->redraw();
}

void Fl_Tabs_Type::add_child(Fl_Type* c, Fl_Type* before) {
  Fl_Group_Type::add_child(c, before);
  ((Fl_Tabs*)o)->value(0);
}

// This is called when o is deleted.  If it is in the tab group make
// sure it is not visible:

void Fl_Group_Type::remove_child(Fl_Type* cc) {
  Fl_Widget_Type* c = (Fl_Widget_Type*)cc;
  ((Fl_Group*)o)->remove(c->o);
  o->redraw();
}

void Fl_Tabs_Type::remove_child(Fl_Type* cc) {
  Fl_Widget_Type* c = (Fl_Widget_Type*)cc;
  Fl_Tabs *t = (Fl_Tabs*)o;
  if (t->value() == c->o) t->value(0);
  Fl_Group_Type::remove_child(c);
}

// move, don't change selected value:

void Fl_Group_Type::move_child(Fl_Type* cc, Fl_Type* before) {
  Fl_Widget_Type* c = (Fl_Widget_Type*)cc;
  Fl_Widget* b = before ? ((Fl_Widget_Type*)before)->o : 0;
  ((Fl_Group*)o)->remove(c->o);
  ((Fl_Group*)o)->insert(*(c->o), b);
  o->redraw();
}

////////////////////////////////////////////////////////////////
// some other group subclasses that fluid does not treat specially:

#include <FL/Fl_Scroll.H>

static const char scroll_type_name[] = "Fl_Scroll";

static Fl_Menu_Item scroll_type_menu[] = {
  {"BOTH", 0, 0, 0/*(void*)Fl_Scroll::BOTH*/},
  {"HORIZONTAL", 0, 0, (void*)Fl_Scroll::HORIZONTAL},
  {"VERTICAL", 0, 0, (void*)Fl_Scroll::VERTICAL},
  {"HORIZONTAL_ALWAYS", 0, 0, (void*)Fl_Scroll::HORIZONTAL_ALWAYS},
  {"VERTICAL_ALWAYS", 0, 0, (void*)Fl_Scroll::VERTICAL_ALWAYS},
  {"BOTH_ALWAYS", 0, 0, (void*)Fl_Scroll::BOTH_ALWAYS},
  {0}};

class Fl_Scroll_Type : public Fl_Group_Type {
  Fl_Menu_Item *subtypes() {return scroll_type_menu;}
public:
  virtual const char *type_name() {return scroll_type_name;}
  Fl_Widget_Type *_make() {return new Fl_Scroll_Type();}
};
Fl_Scroll_Type Fl_Scroll_type;	// the "factory"

////////////////////////////////////////////////////////////////

static const char tile_type_name[] = "Fl_Tile";

class Fl_Tile_Type : public Fl_Group_Type {
public:
  virtual const char *type_name() {return tile_type_name;}
  Fl_Widget_Type *_make() {return new Fl_Tile_Type();}
};
Fl_Tile_Type Fl_Tile_type;	// the "factory"
