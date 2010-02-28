/*
 *  Fl_Device.cxx
 *
 */

#include <FL/Fl.H>
#include <FL/Fl_Device.H>
#include <FL/Fl_Printer.H>
#include <FL/fl_draw.H>
#include <FL/Fl_Image.H>

extern Fl_Device *fl_device;

void Fl_Virtual_Printer::print_widget(Fl_Widget* widget, int delta_x, int delta_y) 
{ 
  int old_x, old_y, new_x, new_y, is_window;
  if ( ! widget->visible() ) return;
  is_window = (widget->as_window() != NULL);
  widget->damage(FL_DAMAGE_ALL);
  // set origin to the desired top-left position of the widget
  origin(&old_x, &old_y);
  new_x = old_x + delta_x;
  new_y = old_y + delta_y;
  if (!is_window) {
    new_x -= widget->x();
    new_y -= widget->y();
  }
  if (new_x != old_x || new_y != old_y) {
    translate(new_x - old_x, new_y - old_y );
  }
  // if widget is a window, clip all drawings to the window area
  if (is_window) fl_push_clip(0, 0, widget->w(), widget->h() );
#ifdef __APPLE__
  CGContextRef save_gc = fl_gc;
#elif defined(WIN32) // && !defined(__CYGWIN__)
  HDC save_gc = fl_gc;
#else
  _XGC *save_gc = fl_gc;	// FIXME
#endif
  widget->draw();
  fl_gc = save_gc;
  if (is_window) fl_pop_clip();
  // find subwindows of widget and print them
  traverse(widget);
  // reset origin to where it was
  if(new_x != old_x || new_y != old_y) {
    untranslate();
  }
}


void Fl_Virtual_Printer::traverse(Fl_Widget *widget)
{
  Fl_Group *g = widget->as_group();
  if (!g) return;
  int n = g->children();
  for (int i = 0; i < n; i++) {
    Fl_Widget *c = g->child(i);
    if ( !c->visible() ) continue;
    if ( c->as_window() ) {
      print_widget(c, c->x(), c->y());
    }
    else traverse(c);
  }
}

void Fl_Virtual_Printer::origin(int *x, int *y)
{
  if (x) *x = x_offset;
  if (y) *y = y_offset;
}

void Fl_Virtual_Printer::print_window_part(Fl_Window *win, int x, int y, int w, int h, int delta_x, int delta_y)
{
#ifdef __APPLE__
  CGContextRef save_gc = fl_gc;
#elif defined(WIN32)
  HDC save_gc = fl_gc;
#else
  _XGC *save_gc = fl_gc;
#endif
  Fl_Window *save_front = Fl::first_window();
  win->show();
  Fl::check();
  win->make_current();
  uchar *image_data = fl_read_image(NULL, x, y, w, h);
  save_front->show();
  fl_gc = save_gc;
  Fl_RGB_Image *image = new Fl_RGB_Image(image_data, w, h);
  image->draw(delta_x, delta_y);
  add_image(image, image_data);
}

void Fl_Virtual_Printer::add_image(Fl_Image *image, const uchar *data)
{
  struct chain_elt *elt =  (struct chain_elt *)calloc(sizeof(struct chain_elt), 1);
  elt->image = image;
  elt->data = data;
  if (image_list_) { elt->next = image_list_; }
  image_list_ = elt;
}

void Fl_Virtual_Printer::delete_image_list()
{
  while(image_list_) {
    struct chain_elt *next = image_list_->next;
    delete image_list_->image;
    if (image_list_->data) delete image_list_->data;
    free(image_list_);
    image_list_ = next;
  }
}

int Fl_Virtual_Printer::start_job(int pagecount, int *frompage, int *topage) {return 1;}
int Fl_Virtual_Printer::start_page (void) {return 1;}
int Fl_Virtual_Printer::printable_rect(int *w, int *h) {return 1;}
void Fl_Virtual_Printer::margins(int *left, int *top, int *right, int *bottom) {}
void Fl_Virtual_Printer::origin(int x, int y) {}
void Fl_Virtual_Printer::scale (float scale_x, float scale_y) {}
void Fl_Virtual_Printer::rotate(float angle) {}
int Fl_Virtual_Printer::end_page (void) {return 1;}
void Fl_Virtual_Printer::end_job (void) {}
void Fl_Virtual_Printer::translate(int x, int y) {}
void Fl_Virtual_Printer::untranslate(void) {}

extern Fl_Device *fl_device;

Fl_Device *Fl_Device::set_current(void)
{
  Fl_Device *current = fl_device;
  fl_device = this;
  return current;
}

Fl_Device *Fl_Device::current(void)
{
  return fl_device;
}