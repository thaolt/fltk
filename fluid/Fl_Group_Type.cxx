//
// "$Id: Fl_Group_Type.cxx,v 1.19 2004/05/15 20:52:44 spitzak Exp $"
//
// fltk::Group object code for the Fast Light Tool Kit (FLTK).
//
// Object describing an fltk::Group and links to WindowType.C and
// the fltk::Tabs widget, with special stuff to select tab items and
// insure that only one is visible.
//
// Copyright 1998-2003 by Bill Spitzak and others.
//
// This library is free software; you can redistribute it and/or
// modify it under the terms of the GNU Library General Public
// License as published by the Free Software Foundation; either
// version 2 of the License, or (at your option) any later version.
//
// This library is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
// Library General Public License for more details.
//
// You should have received a copy of the GNU Library General Public
// License along with this library; if not, write to the Free Software
// Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307
// USA.
//
// Please report all bugs and problems to "fltk-bugs@fltk.org".
//


#include "FluidType.h"
#include <fltk/events.h>
#include <fltk/run.h>
#include <fltk/Group.h>
#include <fltk/ask.h>

class igroup : public fltk::Group {
public:
  igroup(int x,int y,int w,int h) : fltk::Group(x,y,w,h) {
    fltk::Group::current(0);
    resizable(0);
  }
};

WidgetType* GroupType::_make() {return new GroupType();}

GroupType::~GroupType() {
  for (FluidType* q = first_child; q; q = q->next_brother) {
	  remove_child(q);
	  if(q->is_widget() && (((WidgetType *)q)->o->parent() == o)) {
		  ((WidgetType *)q)->o->parent(0);
		  // fltk::Group destructor will delete all its children!!
		  ((WidgetType *)q)->o = 0;
	  }
  }
}

fltk::Widget *GroupType::widget(int x,int y,int w,int h) {
  igroup *g = new igroup(x,y,w,h);
  fltk::Group::current(0);
  return g;
}

const char* GroupType::type_name() const {return "fltk::Group";}

int GroupType::is_parent() const {return 1;}
int GroupType::is_group() const {return 1;}

GroupType Grouptype;	// the "factory"

FluidType *GroupType::make() {
  return WidgetType::make();
}

// Enlarge the group to surround all it's children.  This is done to
// all groups whenever the user moves any widgets.
void fix_group_size(FluidType *t) {
  if (!t || !t->is_group() || t->is_menu_button()) return;
  fltk::Group* g = (fltk::Group*)((GroupType*)t)->o;
  //if (g->resizable()) return;
  int X = 0;
  int Y = 0;
  int R = g->w();
  int B = g->h();
  for (FluidType *nn = t->first_child; nn; nn = nn->next_brother) {
    if (nn->is_widget()) {
      fltk::Widget* o = ((WidgetType*)nn)->o;
      int x = o->x();  if (x < X) X = x;
      int y = o->y();  if (y < Y) Y = y;
      int r = x+o->w();if (r > R) R = r;
      int b = y+o->h();if (b > B) B = b;
    }
  }
  g->resize(g->x()+X,g->y()+Y,R-X,B-Y);
  if (X || Y) {
    for (FluidType *nn = t->first_child; nn; nn = nn->next_brother) {
      if (nn->is_widget()) {
	fltk::Widget* o = ((WidgetType*)nn)->o;
	o->x(o->x()-X);
	o->y(o->y()-Y);
      }
    }
  }
  g->init_sizes();
}

extern int force_parent;

void group_cb(fltk::Widget *, void *) {
  // Find the current widget:
  FluidType *qq = FluidType::current;
  while (qq && (!qq->is_widget() || qq->is_menu_item())) qq = qq->parent;
  if (!qq || !qq->parent || !qq->parent->is_widget()) {
    fltk::message("Please select widgets to group");
    return;
  }
  WidgetType* q = (WidgetType*)qq;
  force_parent = 1;
  GroupType *n = (GroupType*)(Grouptype.make());
  n->move_before(q);
  n->o->resize(0,0,0,0);
  for (FluidType *t = q->parent->first_child; t;) {
    FluidType* next = t->next_brother;
    if (t->selected && t != n) {
      t->remove();
      t->add(n);
    }
    t = next;
  }
  fix_group_size(n);
}

void ungroup_cb(fltk::Widget *, void *) {
  // Find the group:
  FluidType *q = FluidType::current;
  while (q && (!q->is_widget() || q->is_menu_item())) q = q->parent;
  if (q) q = q->parent;
  if (!q || !q->parent->is_widget()) {
    fltk::message("Please select widgets in a group");
    return;
  }
  for (FluidType* n = q->first_child; n;) {
    FluidType* next = n->next_brother;
    if (n->selected) {
      n->remove();
      n->insert(q);
    }
    n = next;
  }
  if (!q->first_child) delete q;
}

const Enumeration *GroupType::subtypes() const {return 0;}

////////////////////////////////////////////////////////////////

#include <stdio.h>

void GroupType::write_code() {
  write_code1();
  if (first_child) {
    write_c("%so->begin();\n", indent());
    for (FluidType* q = first_child; q; q = q->next_brother) q->write_code();
    write_c("%so->end();\n", indent());
  }
  write_extra_code();
  if (resizable()) write_c("%sfltk::Group::current()->resizable(o);\n", indent());
  write_block_close();
}

////////////////////////////////////////////////////////////////

#include <fltk/PackedGroup.h>

#if 0
// I took this out because I don't think it is needed for back-compatability
static const Enumeration pack_type_menu[] = {
  {"normal",		0,		(void*)fltk::PackedGroup::NORMAL},
  {"all-vertical",	"HORIZONTAL",	(void*)fltk::PackedGroup::ALL_CHILDREN_VERTICAL},
  {0}};
#endif

class PackType : public GroupType {
  //const Enumeration *subtypes() const {return pack_type_menu;}
public:
  virtual const char *type_name() const {return "fltk::PackedGroup";}
  WidgetType *_make() {return new PackType();}
};

PackType Packtype;	// the "factory"

////////////////////////////////////////////////////////////////

#include <fltk/TabGroup.h>

class itabs : public fltk::TabGroup {
public:
  itabs(int x,int y,int w,int h) : fltk::TabGroup(x,y,w,h) {
    fltk::Group::current(0);
    resizable(0);
  }
};

class TabsType : public GroupType {
public:
  virtual const char *type_name() const {return "fltk::TabGroup";}
  fltk::Widget *widget(int x,int y,int w,int h) {
    itabs *g = new itabs(x,y,w,h); fltk::Group::current(0); return g;}
  WidgetType *_make() {return new TabsType();}
  FluidType* click_test(int,int);
  void add_child(FluidType*, FluidType*);
  void remove_child(FluidType*);
};

TabsType Tabstype;	// the "factory"

// This is called when user clicks on a widget in the window.  See
// if it is a tab title, and adjust visibility and return new selection:
// If none, return o unchanged:

FluidType* TabsType::click_test(int x, int y) {
  fltk::TabGroup *t = (fltk::TabGroup*)o;
  fltk::Widget *a = t->which(x,y);
  if (!a) return 0; // didn't click on tab
  // okay, run the tabs ui until they let go of mouse:
  t->handle(fltk::PUSH);
  fltk::pushed(t);
  while (fltk::pushed()==t) fltk::wait();
  return (FluidType*)(t->value()->user_data());
}

// This is called when o is created.  If it is in the tab group make
// sure it is visible:

void GroupType::add_child(FluidType* cc, FluidType* before) {
  WidgetType* c = (WidgetType*)cc;
  fltk::Widget* b = before ? ((WidgetType*)before)->o : 0;
  ((fltk::Group*)o)->insert(*(c->o), b);
  o->redraw();
}

void TabsType::add_child(FluidType* c, FluidType* before) {
  GroupType::add_child(c, before);
}

// This is called when o is deleted.  If it is in the tab group make
// sure it is not visible:

void GroupType::remove_child(FluidType* cc) {
  WidgetType* c = (WidgetType*)cc;
  ((fltk::Group*)o)->remove(c->o);
  o->redraw();
}

void TabsType::remove_child(FluidType* cc) {
  WidgetType* c = (WidgetType*)cc;
  fltk::TabGroup *t = (fltk::TabGroup*)o;
  if (t->value() == c->o) t->value(0);
  GroupType::remove_child(c);
}

// move, don't change selected value:

void GroupType::move_child(FluidType* cc, FluidType* before) {
  WidgetType* c = (WidgetType*)cc;
  fltk::Widget* b = before ? ((WidgetType*)before)->o : 0;
  ((fltk::Group*)o)->remove(c->o);
  ((fltk::Group*)o)->insert(*(c->o), b);
  o->redraw();
}

////////////////////////////////////////////////////////////////
// some other group subclasses that fluid does not treat specially:

#include <fltk/ScrollGroup.h>

static const Enumeration scroll_type_menu[] = {
  {"Both",		"BOTH",		(void*)fltk::ScrollGroup::BOTH},
  {"Horizontal",	"HORIZONTAL",	(void*)fltk::ScrollGroup::HORIZONTAL},
  {"Vertical",		"VERTICAL",	(void*)fltk::ScrollGroup::VERTICAL},
  {"Horizontal Always",	"HORIZONTAL_ALWAYS", (void*)fltk::ScrollGroup::HORIZONTAL_ALWAYS},
  {"Vertical Always",	"VERTICAL_ALWAYS", (void*)fltk::ScrollGroup::VERTICAL_ALWAYS},
  {"Both Always",	"BOTH_ALWAYS",	(void*)fltk::ScrollGroup::BOTH_ALWAYS},
  {0}};

class ScrollType : public GroupType {
  const Enumeration *subtypes() const {return scroll_type_menu;}
public:
  virtual const char *type_name() const {return "fltk::ScrollGroup";}
  WidgetType *_make() {return new ScrollType();}
};

ScrollType Scrolltype;	// the "factory"

////////////////////////////////////////////////////////////////

class TileType : public GroupType {
public:
  virtual const char *type_name() const {return "fltk::TiledGroup";}
  WidgetType *_make() {return new TileType();}
};

TileType Tiletype;	// the "factory"

//
// End of "$Id: Fl_Group_Type.cxx,v 1.19 2004/05/15 20:52:44 spitzak Exp $".
//
