//
// "$Id: Fl.H 5188 2006-06-09 07:48:08Z matt $"
//
// Main header file for the Fast Light Tool Kit (FLTK).
//
// Copyright 1998-2005 by Bill Spitzak and others.
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
// Please report all bugs and problems on the following page:
//
//     http://www.fltk.org/str.php
//

module fl.fl;

private import std.c.osx.carbon.carbon;

private import fl.x;
private import fl.window;
private import fl.widget;
private import fl.image;
private import fl.boxtype;
private import fl.tooltip;

/+- This file was imported from C++ using a script
#ifndef Fl_H
#  define Fl_H

#  include "Enumerations.H"
#  ifndef Fl_Object
#    define Fl_Object Fl_Widget
#  endif

#  ifdef check
#    undef check
#  endif

class Fl_Widget;
class Fl_Window;
class Fl_Image;
struct Fl_Label;
-+/
typedef void function(Fl_Label, int,int,int,int, Fl_Align) Fl_Label_Draw_F;
typedef void function(Fl_Label, inout int, inout int) Fl_Label_Measure_F;
typedef void function(int,int,int,int, Fl_Color) Fl_Box_Draw_F;

typedef void function(void*) Fl_Timeout_Handler;

class Fl {

private:
  const double FOREVER = 1e20;

/+-
  Fl() {}; // no constructor!
-+/

public: // should be private!

  static Fl_Event e_number;
  static int e_x;
  static int e_y;
  static int e_x_root;
  static int e_y_root;
  static int e_dx;
  static int e_dy;
  static int e_state;
  static int e_clicks;
  static int e_is_click;
  static int e_keysym;
  static char[] e_text;
  static int e_length;
  static Fl_Widget belowmouse_;
  static Fl_Widget pushed_;
  static Fl_Widget focus_;
  static Fl_Damage damage_;
  static Fl_Widget selection_owner_;
  static Fl_Window modal_;
  static Fl_Window grab_;
  static int compose_state;
  static int visible_focus_;
  static int dnd_text_ops_;

  static void damage(Fl_Damage d) {
    damage_ = d;
  }
/+-
  static void (*idle)();
-+/

  static char[] scheme_;
  static Fl_Image scheme_bg_;
  static int e_original_keysym; // late addition

public:
/+-

  // API version number
  static double version();

  // argument parsers:
  static int arg(int, char**, int&);
  static int args(int, char**, int&, int (*)(int,char**,int&) = 0);
  static const char* const help;
  static void args(int, char**);

  // things called by initialization:
  static void display(const char*);
  static int visual(int);
  static int gl_visual(int, int *alist=0);
  static void own_colormap();
  static void get_system_colors();
  static void foreground(uchar, uchar, uchar);
  static void background(uchar, uchar, uchar);
  static void background2(uchar, uchar, uchar);

  // schemes:
  static int scheme(const char*);
  static const char* scheme() {return scheme_;}
  static int reload_scheme();

  // execution:
  static int wait();
-+/
  static double wait(double time_to_wait) {
    // delete all widgets that were listed during callbacks
    do_widget_deletion();
  
    version (Win32) { /+-
      return fl_wait(time_to_wait);
    -+/ }
    version (Apple) {
      flush();
      /+= pri 3: activate me
      if (idle) {
        if (!in_idle) {
          in_idle = 1;
          idle();
          in_idle = 0;
        }
        // the idle function may turn off idle, we can then wait:
        if (idle) time_to_wait = 0.0;
      } =+/
      return fl_wait(time_to_wait);
    }
    version (X11) { /+-
      if (first_timeout) {
        elapse_timeouts();
        Timeout *t;
        while ((t = first_timeout)) {
          if (t->time > 0) break;
          // The first timeout in the array has expired.
          missed_timeout_by = t->time;
          // We must remove timeout from array before doing the callback:
          void (*cb)(void*) = t->cb;
          void *argp = t->arg;
          first_timeout = t->next;
          t->next = free_timeout;
          free_timeout = t;
          ++free_timeout_count;
          --first_timeout_count;
          // Now it is safe for the callback to do add_timeout:
          cb(argp);
        }
      } else {
        reset_clock = 1; // we are not going to check the clock
      }
      run_checks();
    //  if (idle && !fl_ready()) {
      if (idle) {
        if (!in_idle) {
          in_idle = 1;
          idle();
          in_idle = 0;
        }
        // the idle function may turn off idle, we can then wait:
        if (idle) time_to_wait = 0.0;
      }
      if (first_timeout && first_timeout->time < time_to_wait)
        time_to_wait = first_timeout->time;
      if (time_to_wait <= 0.0) {
        // do flush second so that the results of events are visible:
        int ret = fl_wait(0.0);
        flush();
        return ret;
      } else {
        // do flush first so that user sees the display:
        flush();
        return fl_wait(time_to_wait);
      } 
    -+/ }
  }

/+-
  static int check();
  static int ready();
-+/
  static int run() {
    while (Fl_X.first) 
      wait(FOREVER);
    return 0;
  }
/+-
  static Fl_Widget* readqueue();
  static void add_timeout(double t, Fl_Timeout_Handler,void* = 0);
  static void repeat_timeout(double t, Fl_Timeout_Handler,void* = 0);
  static int  has_timeout(Fl_Timeout_Handler, void* = 0);
  static void remove_timeout(Fl_Timeout_Handler, void* = 0);
  static void add_check(Fl_Timeout_Handler, void* = 0);
  static int  has_check(Fl_Timeout_Handler, void* = 0);
  static void remove_check(Fl_Timeout_Handler, void* = 0);
  static void add_fd(int fd, int when, void (*cb)(int,void*),void* =0);
  static void add_fd(int fd, void (*cb)(int, void*), void* = 0);
  static void remove_fd(int, int when);
  static void remove_fd(int);
  static void add_idle(void (*cb)(void*), void* = 0);
  static int  has_idle(void (*cb)(void*), void* = 0);
  static void remove_idle(void (*cb)(void*), void* = 0);
  static int damage() {return damage_;}
  static void redraw();
-+/
  static void flush() {
    /+= pri 1: port me over =+/
  }
/+-
  static void (*warning)(const char*, ...);
  static void (*error)(const char*, ...);
  static void (*fatal)(const char*, ...);
-+/
  static Fl_Window first_window() {
    Fl_X i = Fl_X.first;
    return i ? i.w : null;
  }
  
  static Fl_Window next_window(Fl_Window window) {
    Fl_X i = Fl_X.i(window).next;
    return i ? i.w : null;
  }
  
  static void first_window(Fl_Window window) {
    if (!window || !window.shown()) return;
    fl_find(fl_xid(window));
  }

  static Fl_Window modal() {return modal_;}
  static Fl_Window grab() {return grab_;}
/+-
  static void grab(Fl_Window*);
-+/
  // event information:
  static Fl_Event event()		{return e_number;}
  static int event_x()	{return e_x;}
  static int event_y()	{return e_y;}
  static int event_x_root()	{return e_x_root;}
  static int event_y_root()	{return e_y_root;}
  static int event_dx()	{return e_dx;}
  static int event_dy()	{return e_dy;}
/+-
  static void get_mouse(int &,int &);
-+/
  static int event_clicks()	{return e_clicks;}
  static void event_clicks(int i) {e_clicks = i;}
  static int event_is_click()	{return e_is_click;}
  static void event_is_click(int i) {e_is_click = i;} // only 0 works!
  static int event_button()	{return e_keysym-FL_Button;}
  static int event_state()	{return e_state;}
  static int event_state(int i) {return e_state&i;}
  static int event_key()	{return e_keysym;}
  static int event_original_key(){return e_original_keysym;}
/+-
  static int event_key(int);
  static int get_key(int);
-+/
  static char[] event_text() {return e_text;}
  static int event_length() {return e_length;}
/+-
  static int compose(inout int del);
-+/
  static void compose_reset() {compose_state = 0;}
/+-
  static int event_inside(int,int,int,int);
  static int event_inside(const Fl_Widget*);
  static int test_shortcut(int);
-+/

  // event destinations:
  static int handle(Fl_Event e, Fl_Window window) {
    e_number = e;
    if (fl_local_grab) 
      return fl_local_grab(e);
  
    Fl_Widget wi = window;
    switch (e) {
  
    case FL_CLOSE:
      if (grab() || modal() && window != modal()) return 0;
      wi.do_callback();
      return 1;
  
    case FL_SHOW:
      wi.show(); // this calls Fl_Widget::show(), not Fl_Window::show()
      return 1;

    case FL_HIDE:
      wi.hide(); // this calls Fl_Widget::hide(), not Fl_Window::hide()
      return 1;
  /+= pri 2
    case FL_PUSH:
  #ifdef DEBUG
      printf("Fl::handle(e=%d, window=%p);\n", e, window);
  #endif // DEBUG
  
      if (grab()) wi = grab();
      else if (modal() && wi != modal()) return 0;
      pushed_ = wi;
      Fl_Tooltip::current(wi);
      if (send(e, wi, window)) return 1;
      // raise windows that are clicked on:
      window->show();
      return 1;
  
    case FL_DND_ENTER:
    case FL_DND_DRAG:
      dnd_flag = 1;
      break;
  
    case FL_DND_LEAVE:
      dnd_flag = 1;
      belowmouse(0);
      dnd_flag = 0;
      return 1;
  
    case FL_DND_RELEASE:
      wi = belowmouse();
      break;
  
    case FL_MOVE:
    case FL_DRAG:
      fl_xmousewin = window; // this should already be set, but just in case.
      if (pushed()) {
        wi = pushed();
        if (grab()) wi = grab();
        e_number = e = FL_DRAG;
        break;
      }
      if (modal() && wi != modal()) wi = 0;
      if (grab()) wi = grab();
      {Fl_Widget* pbm = belowmouse();
      int ret = (wi && send(e, wi, window));
      if (pbm != belowmouse()) {
  #ifdef DEBUG
        printf("Fl::handle(e=%d, window=%p);\n", e, window);
  #endif // DEBUG
        Fl_Tooltip::enter(belowmouse());
      }
      return ret;}
  
    case FL_RELEASE: {
  //    printf("FL_RELEASE: window=%p, pushed() = %p, grab() = %p, modal() = %p\n",
  //           window, pushed(), grab(), modal());
  
      if (grab()) {
        wi = grab();
        pushed_ = 0; // must be zero before callback is done!
      } else if (pushed()) {
        wi = pushed();
        pushed_ = 0; // must be zero before callback is done!
      } else if (modal() && wi != modal()) return 0;
      int r = send(e, wi, window);
      fl_fix_focus();
      return r;}
 =+/ 
    case FL_UNFOCUS:
      window = null;
    case FL_FOCUS:
      fl_xfocus = window;
      fl_fix_focus();
      return 1;
  /+= pri 3
    case FL_KEYBOARD:
  #ifdef DEBUG
      printf("Fl::handle(e=%d, window=%p);\n", e, window);
  #endif // DEBUG
  
      Fl_Tooltip::enter((Fl_Widget*)0);
  
      fl_xfocus = window; // this should not happen!  But maybe it does:
  
      // Try it as keystroke, sending it to focus and all parents:
      for (wi = grab() ? grab() : focus(); wi; wi = wi->parent())
        if (send(FL_KEYBOARD, wi, window)) return 1;
  
      // recursive call to try shortcut:
      if (handle(FL_SHORTCUT, window)) return 1;
  
      // and then try a shortcut with the case of the text swapped, by
      // changing the text and falling through to FL_SHORTCUT case:
      {unsigned char* c = (unsigned char*)event_text(); // cast away const
      if (!isalpha(*c)) return 0;
      *c = isupper(*c) ? tolower(*c) : toupper(*c);}
      e_number = e = FL_SHORTCUT;
  
    case FL_SHORTCUT:
      if (grab()) {wi = grab(); break;} // send it to grab window
  
      // Try it as shortcut, sending to mouse widget and all parents:
      wi = belowmouse(); if (!wi) {wi = modal(); if (!wi) wi = window;}
      for (; wi; wi = wi->parent()) if (send(FL_SHORTCUT, wi, window)) return 1;
  
      // try using add_handle() functions:
      if (send_handlers(FL_SHORTCUT)) return 1;
  
      // make Escape key close windows:
      if (event_key()==FL_Escape) {
        wi = modal(); if (!wi) wi = window;
        wi->do_callback();
        return 1;
      }
  
      return 0;
  =+/
    case FL_ENTER:
      fl_xmousewin = window;
      fl_fix_focus();
      Fl_Tooltip.enter(belowmouse());
      return 1;
  
    case FL_LEAVE:
      if (!pushed_) {
        belowmouse(null);
        Fl_Tooltip.enter(null);
      }
      if (window == fl_xmousewin) {
        fl_xmousewin = null; 
        fl_fix_focus();
      }
      return 1;
  /+= later
    case FL_MOUSEWHEEL:
      fl_xfocus = window; // this should not happen!  But maybe it does:
  
      // Try sending it to the grab and then the window:
      if (grab()) {
        if (send(FL_MOUSEWHEEL, grab(), window)) return 1;
      }
      if (send(FL_MOUSEWHEEL, window, window)) return 1;
=+/
    default:
      break;
    }
    if (wi && send(e, wi, window)) {
      dnd_flag = 0;
      return 1;
    }
    dnd_flag = 0;
    return send_handlers(e);
  }

  static Fl_Widget belowmouse() {
    return belowmouse_;
  }

  static void belowmouse(Fl_Widget o) {
    if (grab()) return; // don't do anything while grab is on
    Fl_Widget p = belowmouse_;
    if (o != p) {
      belowmouse_ = o;
      Fl_Event old_event = e_number;
      e_number = dnd_flag ? FL_DND_LEAVE : FL_LEAVE;
      for (; p && !p.contains(o); p = p.parent()) {
        p.handle(e_number);
      }
      e_number = old_event;
    }
  }

  static Fl_Widget pushed() {
    return pushed_;
  }

/+-
  static void pushed(Fl_Widget*);
-+/

  static Fl_Widget focus() {
    return focus_;
  }

  static void focus(Fl_Widget o) {
    if (o && !o.visible_focus()) return;
    if (grab()) return; // don't do anything while grab is on
    Fl_Widget p = focus_;
    if (o != p) {
      Fl.compose_reset();
      focus_ = o;
      // make sure that fl_xfocus is set to the top level window
      // of this widget, or fl_fix_focus will clear our focus again
      if (o) {
        Fl_Window win = null, w1 = o.window();
        while (w1) { win=w1; w1=win.window(); }
        if (win) fl_xfocus = win;
      }
      // take focus from the old focused window
      fl_oldfocus = null;
      Fl_Event old_event = e_number;
      e_number = FL_UNFOCUS;
      for (; p; p = p.parent()) {
        p.handle(FL_UNFOCUS);
        fl_oldfocus = p;
      }
      e_number = old_event;
    }
  }
/+-
  static void add_handler(int (*h)(int));
  static void remove_handler(int (*h)(int));

  // cut/paste:
  static void copy(const char* stuff, int len, int clipboard = 0);
  static void paste(Fl_Widget &receiver, int clipboard /*=0*/);
  static int dnd();
  // These are for back-compatability only:
  static Fl_Widget* selection_owner() {return selection_owner_;}
  static void selection_owner(Fl_Widget*);
  static void selection(Fl_Widget &owner, const char*, int len);
  static void paste(Fl_Widget &receiver);
-+/

  // screen size:
  version (Apple) {
    static int x() {
      BitMap r;  GetQDGlobalsScreenBits(&r);
      return r.bounds.left;
    }
   
    static int y() {
      BitMap r;
      GetQDGlobalsScreenBits(&r);
      return r.bounds.top + 20; // \todo 20 pixel menu bar?
    }
            
    static int w() {
      BitMap r;
      GetQDGlobalsScreenBits(&r);
      return r.bounds.right - r.bounds.left;
    }     
    
    static int h() {
      BitMap r;
      GetQDGlobalsScreenBits(&r);
      return r.bounds.bottom - r.bounds.top - 20;
    }
  }
/+-
#if defined(WIN32) || defined(__APPLE__)
  static int x();
  static int y();
#else
  static int x() {return 0;}
  static int y() {return 0;}
#endif /* WIN32 || __APPLE__ */
  static int w();
  static int h();

  // multi-head support:
  static int screen_count();
  static void screen_xywh(int &x, int &y, int &w, int &h) {
    screen_xywh(x, y, w, h, e_x_root, e_y_root);
  }
  static void screen_xywh(int &x, int &y, int &w, int &h, int mx, int my);
  static void screen_xywh(int &x, int &y, int &w, int &h, int n);

  // color map:
  static void	set_color(Fl_Color, uchar, uchar, uchar);
-+/
  static void set_color(Fl_Color i, Fl_Color c) 
  in {
    assert(i<=255 && i>=0);
  }
  body {
    if (fl_cmap[i] != c) {
      fl_cmap[i] = c;
    }
  }

/+-
  static unsigned get_color(Fl_Color);
  static void	get_color(Fl_Color, uchar&, uchar&, uchar&);
  static void	free_color(Fl_Color, int overlay = 0);

  // fonts:
  static const char* get_font(Fl_Font);
  static const char* get_font_name(Fl_Font, int* attributes = 0);
  static int get_font_sizes(Fl_Font, int*& sizep);
  static void set_font(Fl_Font, const char*);
  static void set_font(Fl_Font, Fl_Font);
  static Fl_Font set_fonts(const char* = 0);

  // labeltypes:
  static void set_labeltype(Fl_Labeltype,Fl_Label_Draw_F*,Fl_Label_Measure_F*);
  static void set_labeltype(Fl_Labeltype, Fl_Labeltype from);

-+/
  // boxtypes:
  static Fl_Box_Draw_F get_boxtype(Fl_Boxtype t) {
    return fl_box_table[t].f;
  }

  static void set_boxtype(Fl_Boxtype t, Fl_Box_Draw_F f, ubyte a, ubyte b, ubyte c, ubyte d)
  {
    fl_box_table[t].f   = f;
    fl_box_table[t].set = 1;
    fl_box_table[t].dx  = a;
    fl_box_table[t].dy  = b;
    fl_box_table[t].dw  = c;
    fl_box_table[t].dh  = d;
  }

  static void set_boxtype(Fl_Boxtype t, Fl_Boxtype f) {
    fl_box_table[t] = fl_box_table[f];
  }

  static int box_dx(Fl_Boxtype t) {
    return fl_box_table[t].dx;
  }

  static int box_dy(Fl_Boxtype t) {
    return fl_box_table[t].dy;
  }

  static int box_dw(Fl_Boxtype t) {
    return fl_box_table[t].dw;
  }

  static int box_dh(Fl_Boxtype t) {
    return fl_box_table[t].dh;
  }

  static int draw_box_active() {
    return draw_it_active;
  }

/+-
  // back compatability:
  static void set_abort(void (*f)(const char*,...)) {fatal = f;}
-+/
  static void function(Fl_Window ,void*) atclose = &default_atclose;

  static void default_atclose(Fl_Window window, void* v) {
    window.hide();
    Fl_Widget.default_callback(window, v);
  }

/+-
  static void set_atclose(void (*f)(Fl_Window*,void*)) {atclose = f;}
  static int event_shift() {return e_state&FL_SHIFT;}
  static int event_ctrl() {return e_state&FL_CTRL;}
  static int event_alt() {return e_state&FL_ALT;}
  static int event_buttons() {return e_state&0x7f000000;}
  static int event_button1() {return e_state&FL_BUTTON1;}
  static int event_button2() {return e_state&FL_BUTTON2;}
  static int event_button3() {return e_state&FL_BUTTON3;}
  static void set_idle(void (*cb)()) {idle = cb;}
  static void grab(Fl_Window&win) {grab(&win);}
  static void release() {grab(0);}

  // Visible focus methods...
  static void visible_focus(int v) { visible_focus_ = v; }
  static int  visible_focus() { return visible_focus_; }

  // Drag-n-drop text operation methods...
  static void dnd_text_ops(int v) { dnd_text_ops_ = v; }
  static int  dnd_text_ops() { return dnd_text_ops_; }

  // Multithreading support:
  static void lock();
  static void unlock();
  static void awake(void* message = 0);
  static void* thread_message();

  // Widget deletion:
  static void delete_widget(Fl_Widget *w);
-+/
  static void do_widget_deletion() {
    /+= pri 3: port me =+/
  }
/+-
  static void watch_widget_pointer(Fl_Widget *&w);
  static void release_widget_pointer(Fl_Widget *&w);
  static void clear_widget_pointer(Fl_Widget const *w);
-+/
}


//
// End of "$Id: Fl.H 5188 2006-06-09 07:48:08Z matt $".
//

/+- This file was imported from C++ using a script
//
// "$Id: Fl.cxx 5257 2006-07-16 20:37:41Z matt $"
//
// Main event handling code for the Fast Light Tool Kit (FLTK).
//
// Copyright 1998-2006 by Bill Spitzak and others.
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
// Please report all bugs and problems on the following page:
//
//     http://www.fltk.org/str.php
//

// warning: the Apple Quartz version still uses some Quickdraw calls,
//          mostly to get around the single active context in QD and 
//          to implement clipping. This should be changed into pure
//          Quartz calls in the near future.

#include <FL/Fl.H>
#include <FL/Fl_Window.H>
#include <FL/x.H>
#include <FL/Fl_Tooltip.H>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include "flstring.h"

#ifdef DEBUG
#  include <stdio.h>
#endif // DEBUG

#ifdef WIN32
#  include <ole2.h>
void fl_free_fonts(void);
HBRUSH fl_brush_action(int action);
void fl_cleanup_pens(void);
void fl_release_dc(HWND,HDC);
void fl_cleanup_dc_list(void);
#endif // WIN32

//
// Globals...
//

Fl_Widget	*Fl::belowmouse_,
		*Fl::pushed_,
		*Fl::focus_,
		*Fl::selection_owner_;
int		Fl::damage_,
		Fl::e_number,
		Fl::e_x,
		Fl::e_y,
		Fl::e_x_root,
		Fl::e_y_root,
		Fl::e_dx,
		Fl::e_dy,
		Fl::e_state,
		Fl::e_clicks,
		Fl::e_is_click,
		Fl::e_keysym,
                Fl::e_original_keysym;
char		*Fl::e_text = (char *)"";
int		Fl::e_length;
int		Fl::visible_focus_ = 1,
		Fl::dnd_text_ops_ = 1;

-+/
Fl_Window fl_xfocus;	// which window X thinks has focus
Fl_Window fl_xmousewin;// which window X thinks has FL_ENTER
/+-
Fl_Window *Fl::grab_;	// most recent Fl::grab()
Fl_Window *Fl::modal_;	// topmost modal() window

//
// 'Fl::version()' - Return the API version number...
//

double
Fl::version() {
  return FL_VERSION;
}


//
// 'Fl:event_inside()' - Return whether or not the mouse event is inside
//                       the given rectangle.
//

int Fl::event_inside(int xx,int yy,int ww,int hh) /*const*/ {
  int mx = e_x - xx;
  int my = e_y - yy;
  return (mx >= 0 && mx < ww && my >= 0 && my < hh);
}

int Fl::event_inside(const Fl_Widget *o) /*const*/ {
  int mx = e_x - o->x();
  int my = e_y - o->y();
  return (mx >= 0 && mx < o->w() && my >= 0 && my < o->h());
}

//
//
// timer support
//

#ifdef WIN32

/// implementation in Fl_win32.cxx

#elif defined(__APPLE__)

/// implementation in Fl_mac.cxx

#else

//
// X11 timers
//


////////////////////////////////////////////////////////////////
// Timeouts are stored in a sorted list, so only the first one needs
// to be checked to see if any should be called.
  
struct Timeout {
  double time;
  void (*cb)(void*);
  void* arg;
  Timeout* next;
};
static Timeout* first_timeout, *free_timeout;
static int first_timeout_count, free_timeout_count;

#include <sys/time.h>

// I avoid the overhead of getting the current time when we have no
// timeouts by setting this flag instead of getting the time.
// In this case calling elapse_timeouts() does nothing, but records
// the current time, and the next call will actualy elapse time.
static char reset_clock = 1;

static void elapse_timeouts() {
  static struct timeval prevclock;
  struct timeval newclock;
  gettimeofday(&newclock, NULL);
  double elapsed = newclock.tv_sec - prevclock.tv_sec +
    (newclock.tv_usec - prevclock.tv_usec)/1000000.0;
  prevclock.tv_sec = newclock.tv_sec;
  prevclock.tv_usec = newclock.tv_usec;
  if (reset_clock) {
    reset_clock = 0;
  } else if (elapsed > 0) {
    for (Timeout* t = first_timeout; t; t = t->next) t->time -= elapsed;
  }
}

// Continuously-adjusted error value, this is a number <= 0 for how late
// we were at calling the last timeout. This appears to make repeat_timeout
// very accurate even when processing takes a significant portion of the
// time interval:
static double missed_timeout_by;

void Fl::add_timeout(double time, Fl_Timeout_Handler cb, void *argp) {
  elapse_timeouts();
  repeat_timeout(time, cb, argp);
}

void Fl::repeat_timeout(double time, Fl_Timeout_Handler cb, void *argp) {
  time += missed_timeout_by; if (time < -.05) time = 0;
  Timeout* t = free_timeout;
  if (t) {
      free_timeout = t->next;
      --free_timeout_count;
  } else {
      t = new Timeout;
  }
  t->time = time;
  t->cb = cb;
  t->arg = argp;
  // insert-sort the new timeout:
  Timeout** p = &first_timeout; 
  while (*p && (*p)->time <= time) p = &((*p)->next);
  t->next = *p;
  *p = t;
}

int Fl::has_timeout(Fl_Timeout_Handler cb, void *argp) {
  for (Timeout* t = first_timeout; t; t = t->next)
    if (t->cb == cb && t->arg == argp) return 1;
  return 0;
}

void Fl::remove_timeout(Fl_Timeout_Handler cb, void *argp) {
  // This version removes all matching timeouts, not just the first one.
  // This may change in the future.
  for (Timeout** p = &first_timeout; *p;) {
    Timeout* t = *p;
    if (t->cb == cb && (t->arg == argp || !argp)) {
      *p = t->next;
      t->next = free_timeout;
      free_timeout = t;
    } else {
      p = &(t->next);
    }
  }
}

#endif

////////////////////////////////////////////////////////////////
// Checks are just stored in a list. They are called in the reverse
// order that they were added (this may change in the future).
// This is a bit messy because I want to allow checks to be added,
// removed, and have wait() called from inside them, to do this
// next_check points at the next unprocessed one for the outermost
// call to Fl::wait().

struct Check {
  void (*cb)(void*);
  void* arg;
  Check* next;
};
static Check *first_check, *next_check, *free_check;

void Fl::add_check(Fl_Timeout_Handler cb, void *argp) {
  Check* t = free_check;
  if (t) free_check = t->next;
  else t = new Check;
  t->cb = cb;
  t->arg = argp;
  t->next = first_check;
  if (next_check == first_check) next_check = t;
  first_check = t;
}

void Fl::remove_check(Fl_Timeout_Handler cb, void *argp) {
  for (Check** p = &first_check; *p;) {
    Check* t = *p;
    if (t->cb == cb && t->arg == argp) {
      if (next_check == t) next_check = t->next;
      *p = t->next;
      t->next = free_check;
      free_check = t;
    } else {
      p = &(t->next);
    }
  }
}

#if !defined(__APPLE__)
static void run_checks()
{
  // checks are a bit messy so that add/remove and wait may be called
  // from inside them without causing an infinite loop:
  if (next_check == first_check) {
    while (next_check) {
      Check* checkp = next_check;
      next_check = checkp->next;
      (checkp->cb)(checkp->arg);
    }
    next_check = first_check;
  }
}
#endif // !__APPLE__

#ifndef WIN32
static char in_idle;
#endif

////////////////////////////////////////////////////////////////
// wait/run/check/ready:

void (*Fl::idle)(); // see Fl_add_idle.cxx for the add/remove functions

extern int fl_ready(); // in Fl_<platform>.cxx
extern int fl_wait(double time); // in Fl_<platform>.cxx


#ifdef WIN32
class Fl_Win32_At_Exit {
public:
  Fl_Win32_At_Exit() { }
  ~Fl_Win32_At_Exit() {
    fl_free_fonts();        // do some WIN32 cleanup
    fl_cleanup_pens();
    OleUninitialize();
    fl_brush_action(1);
    fl_cleanup_dc_list();
  }
};
static Fl_Win32_At_Exit win32_at_exit;
#endif



int Fl::wait() {
  if (!Fl_X::first) return 0;
  wait(FOREVER);
  return Fl_X::first != 0; // return true if there is a window
}

int Fl::check() {
  wait(0.0);
  return Fl_X::first != 0; // return true if there is a window
}

int Fl::ready() {
#if ! defined( WIN32 )  &&  ! defined(__APPLE__)
  if (first_timeout) {
    elapse_timeouts();
    if (first_timeout->time <= 0) return 1;
  } else {
    reset_clock = 1;
  }
#endif
  return fl_ready();
}

////////////////////////////////////////////////////////////////
// Window list management:

Fl_X* Fl_X::first;
-+/

Fl_Window fl_find(WindowRef xid) {
  Fl_X window;
  for (Fl_X pp = Fl_X.first; pp; pp = window.next) {
    window = pp;
/+
#ifdef __APPLE_QD__
    if (window->xid == xid && !window->w->window()) {
#elif defined(__APPLE_QUARTZ__)
+/
    if (window.xid == xid && !window.w.window()) {
/+
#else
    if (window->xid == xid) {
#endif // __APPLE__
+/
      if (window != Fl_X.first && !Fl.modal()) {
        // make this window be first to speed up searches
        // this is not done if modal is true to avoid messing up modal stack
        pp = window.next;
        window.next = Fl_X.first;
        Fl_X.first = window;
      }
      return window.w;
    }
  }
  return null;
}

/+-
void Fl::redraw() {
  for (Fl_X* i = Fl_X::first; i; i = i->next) i->w->redraw();
}

void Fl::flush() {
  if (damage()) {
    damage_ = 0;
    for (Fl_X* i = Fl_X::first; i; i = i->next) {
      if (i->wait_for_expose) {damage_ = 1; continue;}
      Fl_Window* wi = i->w;
      if (!wi->visible_r()) continue;
      if (wi->damage()) {i->flush(); wi->clear_damage();}
      // destroy damage regions for windows that don't use them:
      if (i->region) {XDestroyRegion(i->region); i->region = 0;}
    }
  }

#ifdef WIN32
  GdiFlush();
#elif defined(__APPLE_QD__)
  GrafPtr port;
  GetPort( &port );
  if ( port )
    QDFlushPortBuffer( port, 0 );
#elif defined (__APPLE_QUARTZ__)
  if (fl_gc)
    CGContextFlush(fl_gc);
#else
  if (fl_display) XFlush(fl_display);
#endif
}
-+/
////////////////////////////////////////////////////////////////
// Event handlers:

class handler_link {
  int function(Fl_Event) handle;
  handler_link next;
};

static handler_link handlers = null;

/+-
void Fl::add_handler(int (*ha)(int)) {
  handler_link *l = new handler_link;
  l->handle = ha;
  l->next = handlers;
  handlers = l;
}

void Fl::remove_handler(int (*ha)(int)) {
  handler_link *l, *p;

  // Search for the handler in the list...
  for (l = handlers, p = 0; l && l->handle != ha; p = l, l = l->next);

  if (l) {
    // Found it, so remove it from the list...
    if (p) p->next = l->next;
    else handlers = l->next;

    // And free the record...
    delete l;
  }
}
-+/

int function(int) fl_local_grab = null; // used by fl_dnd.cxx

static int send_handlers(Fl_Event e) {
  for (handler_link hl = handlers; hl; hl = hl.next)
    if (hl.handle(e)) return 1;
  return 0;
}

////////////////////////////////////////////////////////////////

Fl_Widget fl_oldfocus; // kludge for Fl_Group...


static byte dnd_flag = 0; // make 'belowmouse' send DND_LEAVE instead of LEAVE
/+-
void Fl::pushed(Fl_Widget *o) {
  pushed_ = o;
}

static void nothing(Fl_Widget *) {}
void (*Fl_Tooltip::enter)(Fl_Widget *) = nothing;
void (*Fl_Tooltip::exit)(Fl_Widget *) = nothing;

// Update modal(), focus() and other state according to system state,
// and send FL_ENTER, FL_LEAVE, FL_FOCUS, and/or FL_UNFOCUS events.
// This is the only function that produces these events in response
// to system activity.
// This is called whenever a window is added or hidden, and whenever
// X says the focus or mouse window have changed.
-+/

void fl_fix_focus() {
  /+= pri 1
#ifdef DEBUG
  puts("fl_fix_focus();");
#endif // DEBUG

  if (Fl::grab()) return; // don't do anything while grab is on.

  // set focus based on Fl::modal() and fl_xfocus
  Fl_Widget* w = fl_xfocus;
  if (w) {
    int saved = Fl::e_keysym;
    if (Fl::e_keysym < (FL_Button + FL_LEFT_MOUSE) ||
        Fl::e_keysym > (FL_Button + FL_RIGHT_MOUSE))
      Fl::e_keysym = 0; // make sure widgets don't think a keystroke moved focus
    while (w->parent()) w = w->parent();
    if (Fl::modal()) w = Fl::modal();
    if (!w->contains(Fl::focus()))
      if (!w->take_focus()) Fl::focus(w);
    Fl::e_keysym = saved;
  } else
    Fl::focus(0);

// MRS: Originally we checked the button state, but a user reported that it
//      broke click-to-focus in FLWM?!?
//  if (!(Fl::event_state() & 0x7f00000 /*FL_BUTTONS*/)) {
  if (!Fl::pushed()) {
    // set belowmouse based on Fl::modal() and fl_xmousewin:
    w = fl_xmousewin;
    if (w) {
      if (Fl::modal()) w = Fl::modal();
      if (!w->contains(Fl::belowmouse())) {
        int old_event = Fl::e_number;
	w->handle(Fl::e_number = FL_ENTER);
	Fl::e_number = old_event;
	if (!w->contains(Fl::belowmouse())) Fl::belowmouse(w);
      } else {
	// send a FL_MOVE event so the enter/leave state is up to date
	Fl::e_x = Fl::e_x_root-fl_xmousewin->x();
	Fl::e_y = Fl::e_y_root-fl_xmousewin->y();
        int old_event = Fl::e_number;
	w->handle(Fl::e_number = FL_MOVE);
	Fl::e_number = old_event;
      }
    } else {
      Fl::belowmouse(0);
      Fl_Tooltip::enter(0);
    }
  }
  =+/
}

// This function is called by ~Fl_Widget() and by Fl_Widget::deactivate
// and by Fl_Widget::hide().  It indicates that the widget does not want
// to receive any more events, and also removes all global variables that
// point at the widget.
// I changed this from the 1.0.1 behavior, the older version could send
// FL_LEAVE or FL_UNFOCUS events to the widget.  This appears to not be
// desirable behavior and caused flwm to crash.

void fl_throw_focus(Fl_Widget o) {
  if (o.contains(Fl.pushed())) Fl.pushed_ = null;
/+- #ifndef WIN32
  if (o->contains(fl_selection_requestor)) fl_selection_requestor = 0;
#endif -+/
  if (o.contains(Fl.belowmouse())) Fl.belowmouse_ = null;
  if (o.contains(Fl.focus())) Fl.focus_ = null;
  if (o == fl_xfocus) fl_xfocus = null;
  if (o == Fl_Tooltip.current()) Fl_Tooltip.current(null);
  if (o == fl_xmousewin) fl_xmousewin = null;
  Fl_Tooltip.exit(o);
  fl_fix_focus();
}

////////////////////////////////////////////////////////////////

// Call to->handle but first replace the mouse x/y with the correct
// values to account for nested X windows. 'window' is the outermost
// window the event was posted to by X:
static int send(Fl_Event event, Fl_Widget to, Fl_Window window) {
  int dx, dy;
  Fl_Event old_event = Fl.e_number;
  if (window) {
    dx = window.x();
    dy = window.y();
  } else {
    dx = dy = 0;
  }
  for (Fl_Widget w = to; w; w = w.parent())
    if (w.type()>=FL_WINDOW) {dx -= w.x(); dy -= w.y();}
  int save_x = Fl.e_x; Fl.e_x += dx;
  int save_y = Fl.e_y; Fl.e_y += dy;
  int ret = to.handle(Fl.e_number = event);
  Fl.e_number = old_event;
  Fl.e_y = save_y;
  Fl.e_x = save_x;
  return ret;
}

/+-
////////////////////////////////////////////////////////////////
// hide() destroys the X window, it does not do unmap!

#if !defined(WIN32) && USE_XFT
extern void fl_destroy_xft_draw(Window);
#endif

void Fl_Window::hide() {
  clear_visible();

  if (!shown()) return;

  // remove from the list of windows:
  Fl_X* ip = i;
  Fl_X** pp = &Fl_X::first;
  for (; *pp != ip; pp = &(*pp)->next) if (!*pp) return;
  *pp = ip->next;

#ifdef __APPLE_QD__
  // remove all childwindow links
  for ( Fl_X *pc = Fl_X::first; pc; pc = pc->next )
  { 
    if ( pc->xidNext == ip ) pc->xidNext = ip->xidNext;
    if ( pc->xidChildren == ip ) pc->xidChildren = ip->xidNext;   
  }
#elif defined(__APPLE_QUARTZ__)
  // remove all childwindow links
  for ( Fl_X *pc = Fl_X::first; pc; pc = pc->next )
  {
    if ( pc->xidNext == ip ) pc->xidNext = ip->xidNext;
    if ( pc->xidChildren == ip ) pc->xidChildren = ip->xidNext;
  }
#endif // __APPLE__

  i = 0;

  // recursively remove any subwindows:
  for (Fl_X *wi = Fl_X::first; wi;) {
    Fl_Window* W = wi->w;
    if (W->window() == this) {
      W->hide();
      W->set_visible();
      wi = Fl_X::first;
    } else wi = wi->next;
  }

  if (this == Fl::modal_) { // we are closing the modal window, find next one:
    Fl_Window* W;
    for (W = Fl::first_window(); W; W = Fl::next_window(W))
      if (W->modal()) break;
    Fl::modal_ = W;
  }

  // Make sure no events are sent to this window:
  fl_throw_focus(this);
  handle(FL_HIDE);

#ifdef WIN32
  // this little trick keeps the current clipboard alive, even if we are about
  // to destroy the window that owns the selection.
  if (GetClipboardOwner()==ip->xid) {
    Fl_Window *w1 = Fl::first_window();
    if (w1 && OpenClipboard(fl_xid(w1))) {
      EmptyClipboard();
      SetClipboardData(CF_TEXT, NULL);
      CloseClipboard();
    }
  }
  // Send a message to myself so that I'll get out of the event loop...
  PostMessage(ip->xid, WM_APP, 0, 0);
  if (ip->private_dc) fl_release_dc(ip->xid, ip->private_dc);
    if (ip->xid == fl_window && fl_gc) {
      fl_release_dc(fl_window, fl_gc);
      fl_window = (HWND)-1;
      fl_gc = 0;
    }
#elif defined(__APPLE_QD__)
  if ( ip->xid == fl_window )
    fl_window = 0;
#elif defined(__APPLE_QUARTZ__)
  Fl_X::q_release_context(ip);
  if ( ip->xid == fl_window )
    fl_window = 0;
#endif

  if (ip->region) XDestroyRegion(ip->region);

#ifdef WIN32
  // this little trickery seems to avoid the popup window stacking problem
  HWND p = GetForegroundWindow();
  if (p==GetParent(ip->xid)) {
    ShowWindow(ip->xid, SW_HIDE);
    ShowWindow(p, SW_SHOWNA);
  }
  XDestroyWindow(fl_display, ip->xid);
#elif defined(__APPLE_QD__)
  if ( !parent() ) // don't destroy shared windows!
  {
    // + RemoveTrackingHandler( dndTrackingHandler, ip->xid );
    // + RemoveReceiveHandler( dndReceiveHandler, ip->xid );
    XDestroyWindow(fl_display, ip->xid);
  }
#elif defined(__APPLE_QUARTZ__)
  if ( !parent() ) // don't destroy shared windows!
  {
    // + RemoveTrackingHandler( dndTrackingHandler, ip->xid );
    // + RemoveReceiveHandler( dndReceiveHandler, ip->xid );
    XDestroyWindow(fl_display, ip->xid);
  }
#else
# if USE_XFT
  fl_destroy_xft_draw(ip->xid);
# endif
  XDestroyWindow(fl_display, ip->xid);
#endif
  
#ifdef WIN32
  // Try to stop the annoying "raise another program" behavior
  if (non_modal() && Fl::first_window() && Fl::first_window()->shown())
    Fl::first_window()->show();
#endif
  delete ip;
}

////////////////////////////////////////////////////////////////
// Back compatability cut & paste functions for fltk 1.1 only:

void Fl::selection_owner(Fl_Widget *owner) {selection_owner_ = owner;}

void Fl::selection(Fl_Widget &owner, const char* text, int len) {
  selection_owner_ = &owner;
  Fl::copy(text, len, 0);
}

void Fl::paste(Fl_Widget &receiver) {
  Fl::paste(receiver, 0);
}

////////////////////////////////////////////////////////////////

#include <FL/fl_draw.H>


void Fl_Widget::damage(uchar fl, int X, int Y, int W, int H) {
  Fl_Widget* wi = this;
  // mark all parent widgets between this and window with FL_DAMAGE_CHILD:
  while (wi->type() < FL_WINDOW) {
    wi->damage_ |= fl;
    wi = wi->parent();
    if (!wi) return;
    fl = FL_DAMAGE_CHILD;
  }
  Fl_X* i = Fl_X::i((Fl_Window*)wi);
  if (!i) return; // window not mapped, so ignore it

  // clip the damage to the window and quit if none:
  if (X < 0) {W += X; X = 0;}
  if (Y < 0) {H += Y; Y = 0;}
  if (W > wi->w()-X) W = wi->w()-X;
  if (H > wi->h()-Y) H = wi->h()-Y;
  if (W <= 0 || H <= 0) return;

  if (!X && !Y && W==wi->w() && H==wi->h()) {
    // if damage covers entire window delete region:
    wi->damage(fl);
    return;
  }

  if (wi->damage()) {
    // if we already have damage we must merge with existing region:
    if (i->region) {
#ifdef WIN32
      Fl_Region R = XRectangleRegion(X, Y, W, H);
      CombineRgn(i->region, i->region, R, RGN_OR);
      XDestroyRegion(R);
#elif defined(__APPLE_QD__)
      Fl_Region R = NewRgn(); 
      SetRectRgn(R, X, Y, X+W, Y+H);
      UnionRgn(R, i->region, i->region);
      DisposeRgn(R);
#elif defined(__APPLE_QUARTZ__)
      Fl_Region R = NewRgn();
      SetRectRgn(R, X, Y, X+W, Y+H);
      UnionRgn(R, i->region, i->region);
      DisposeRgn(R);
#else
      XRectangle R;
      R.x = X; R.y = Y; R.width = W; R.height = H;
      XUnionRectWithRegion(&R, i->region, i->region);
#endif
    }
    wi->damage_ |= fl;
  } else {
    // create a new region:
    if (i->region) XDestroyRegion(i->region);
    i->region = XRectangleRegion(X,Y,W,H);
    wi->damage_ = fl;
  }
  Fl::damage(FL_DAMAGE_CHILD);
}

#ifdef WIN32
#  include "Fl_win32.cxx"
#elif defined(__APPLE__)
#  include "Fl_mac.cxx"
#endif

//
// The following methods allow callbacks to schedule the deletion of
// widgets at "safe" times.
//

static int		num_dwidgets = 0, alloc_dwidgets = 0;
static Fl_Widget	**dwidgets = 0;

void
Fl::delete_widget(Fl_Widget *wi) {
  if (!wi) return;

  if (num_dwidgets >= alloc_dwidgets) {
    Fl_Widget	**temp;

    temp = new Fl_Widget *[alloc_dwidgets + 10];
    if (alloc_dwidgets) {
      memcpy(temp, dwidgets, alloc_dwidgets * sizeof(Fl_Widget *));
      delete[] dwidgets;
    }

    dwidgets = temp;
    alloc_dwidgets += 10;
  }

  dwidgets[num_dwidgets] = wi;
  num_dwidgets ++;
}


void
Fl::do_widget_deletion() {
  if (!num_dwidgets) return;

  for (int i = 0; i < num_dwidgets; i ++)
    delete dwidgets[i];

  num_dwidgets = 0;
}

static Fl_Widget ***widget_watch = 0;
static int num_widget_watch = 0;
static int max_widget_watch = 0;

void Fl::watch_widget_pointer(Fl_Widget *&w) 
{
  Fl_Widget **wp = &w;
  int i;
  for (i=0; i<num_widget_watch; ++i) {
    if (widget_watch[i]==wp) return;
  }
  for (i=0; i<num_widget_watch; ++i) {
    if (widget_watch[i]==0L) {
      widget_watch[i] = wp;
      return;
    }
  }
  if (num_widget_watch==max_widget_watch) {
    max_widget_watch += 8;
    widget_watch = (Fl_Widget***)realloc(widget_watch, sizeof(Fl_Widget**)*max_widget_watch);
  }
  widget_watch[num_widget_watch++] = wp;
}

void Fl::release_widget_pointer(Fl_Widget *&w)
{
  Fl_Widget **wp = &w;
  int i;
  for (i=0; i<num_widget_watch; ++i) {
    if (widget_watch[i]==wp) {
      widget_watch[i] = 0L;
      return;
    }
  }
}

void Fl::clear_widget_pointer(Fl_Widget const *w) 
{
  if (w==0L) return;
  int i;
  for (i=0; i<num_widget_watch; ++i) {
    if (widget_watch[i] && *widget_watch[i]==w) {
      *widget_watch[i] = 0L;
    }
  }
}


//
// End of "$Id: Fl.cxx 5257 2006-07-16 20:37:41Z matt $".
//
    End of automatic import -+/
