// fl_labeltype.C

// Drawing code for the (one) common label types.
// Other label types (symbols) are in their own source files
// to avoid linking if not used.

#include <FL/Fl.H>
#include <FL/Fl_Widget.H>
#include <FL/Fl_Group.H>
#include <FL/fl_draw.H>

void
fl_no_label(const Fl_Label*,int,int,int,int,Fl_Align) {}

void
fl_normal_label(const Fl_Label* o, int X, int Y, int W, int H, Fl_Align align)
{
  fl_font(o->font, o->size);
  fl_color((Fl_Color)o->color);
  fl_draw(o->value, X, Y, W, H, align);
}

void
fl_normal_measure(const Fl_Label* o, int& W, int& H) {
  fl_font(o->font, o->size);
  fl_measure(o->value, W, H);
}

#define MAX_LABELTYPE 16

static Fl_Label_Draw_F* table[MAX_LABELTYPE] = {
  fl_normal_label,
  fl_no_label,
  fl_normal_label,	// _FL_SYMBOL_LABEL,
  fl_normal_label,	// _FL_SHADOW_LABEL,
  fl_normal_label,	// _FL_ENGRAVED_LABEL,
  fl_normal_label,	// _FL_EMBOSSED_LABEL,
  fl_no_label,		// _FL_BITMAP_LABEL,
  fl_no_label,		// _FL_PIXMAP_LABEL,
  fl_no_label,		// _FL_IMAGE_LABEL,
  // FL_FREE_LABELTYPE+n:
  fl_no_label, fl_no_label, fl_no_label,
  fl_no_label, fl_no_label, fl_no_label, fl_no_label,
};

static Fl_Label_Measure_F* measure[MAX_LABELTYPE];

void Fl::set_labeltype(Fl_Labeltype t,Fl_Label_Draw_F* f,Fl_Label_Measure_F*m) 
{
  table[t] = f; measure[t] = m;
}

////////////////////////////////////////////////////////////////

// draw label with arbitrary alignment in arbitrary box:
void Fl_Label::draw(int X, int Y, int W, int H, Fl_Align align) const {
  if (!value) return;
  table[type](this, X, Y, W, H, align);
}

void Fl_Label::measure(int& W, int& H) const {
  if (!value) return;
  Fl_Label_Measure_F* f = ::measure[type]; if (!f) f = fl_normal_measure;
  f(this, W, H);
}

// The normal call for a draw() method:
void Fl_Widget::draw_label() const {
  int X = x_+Fl::box_dx(box());
  int W = w_-Fl::box_dw(box());
  if (W > 11 && align()&(FL_ALIGN_LEFT|FL_ALIGN_RIGHT)) {X += 3; W -= 6;}
  draw_label(X, y_+Fl::box_dy(box()), W, h_-Fl::box_dh(box()));
}

// draw() can use this instead to change the bounding box:
void Fl_Widget::draw_label(int X, int Y, int W, int H) const {
  // quit if we are not drawing a label inside the widget:
  if ((align()&15) && !(align() & FL_ALIGN_INSIDE)) return;
  draw_label(X,Y,W,H,align());
}

Fl_Font Fl_Widget::default_font_;
int Fl_Widget::default_size_;

// Anybody can call this to force the label to draw anywhere:
extern char fl_draw_shortcut;
void Fl_Widget::draw_label(int X, int Y, int W, int H, Fl_Align a) const {
  if (flags()&SHORTCUT_LABEL) fl_draw_shortcut = 1;
  Fl_Label l1 = label_;
  if (!active_r()) l1.color |= 8;
  if (l1.font<4) l1.font |= default_font_;
  l1.size += default_size_;
  l1.draw(X,Y,W,H,a);
  fl_draw_shortcut = 0;
}

// include these vars here so they can be referenced without including
// Fl_Input_ code:
#include <FL/Fl_Input_.H>

Fl_Boxtype Fl_Input_::default_box_ = FL_DOWN_BOX;
Fl_Font Fl_Input_::default_font_;
int Fl_Input_::default_size_;

