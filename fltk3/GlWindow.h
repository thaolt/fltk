//
// "$Id$"
//

// 123 TODO: remove stray comments
// 123 TODO: add namespace statements
// 123 TODO: replace class name, constructors and destructor
// 123 TODO: add friend statement for Twin Class
// 123 TODO: add 'compat(FLTK2)' to constructors
// 123 TODO: add twin class with all constructors
// 123 TODO: change all arguments to the FLTK2 class name
// 123 TODO: change the source code to use the new class names
// 123 TODO: add casting to return values
// 123 TODO: move all FLTK2-only functions to the FLTK3 section and implement them
// 123 TODO: remove the FLTK1 and FLTK2 sections in the headers
// 123 TODO: 

//
// "$Id: Fl_Gl_Window.H 6664 2009-02-18 09:27:54Z AlbrechtS $"
//
// OpenGL header file for the Fast Light Tool Kit (FLTK).
//
// Copyright 1998-2009 by Bill Spitzak and others.
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

/* \file
   Fl_Gl_Window widget . */

#ifndef Fl_Gl_Window_H
#define Fl_Gl_Window_H

#include "Window.h"

#ifndef GLContext
/**
  Opaque pointer type to hide system specific implementation.
*/
typedef void* GLContext; // actually a GLXContext or HGLDC
#endif

class Fl_Gl_Choice; // structure to hold result of glXChooseVisual

/**
  The Fl_Gl_Window widget sets things up so OpenGL works.
  
  It also keeps an OpenGL "context" for that window, so that changes to the
  lighting and projection may be reused between redraws. Fl_Gl_Window
  also flushes the OpenGL streams and swaps buffers after draw() returns.

  OpenGL hardware typically provides some overlay bit planes, which
  are very useful for drawing UI controls atop your 3D graphics.  If the
  overlay hardware is not provided, FLTK tries to simulate the overlay.
  This works pretty well if your graphics are double buffered, but not
  very well for single-buffered.

  Please note that the FLTK drawing and clipping functions
  will not work inside an Fl_Gl_Window. All drawing
  should be done using OpenGL calls exclusively.
  Even though Fl_Gl_Window is derived from Fl_Group, 
  it is not useful to add other FLTK Widgets as children,
  unless those widgets are modified to draw using OpenGL calls.
*/
class FL_EXPORT Fl_Gl_Window : public Fl_Window {

  int mode_;
  const int *alist;
  Fl_Gl_Choice *g;
  GLContext context_;
  char valid_f_;
  char damage1_; // damage() of back buffer
  virtual void draw_overlay();
  void init();

  void *overlay;
  void make_overlay();
  friend class _Fl_Gl_Overlay;

  static int can_do(int, const int *);
  int mode(int, const int *);

public:

  void show();
  void show(int a, char **b) {Fl_Window::show(a,b);}
  void flush();
  void hide();
  void resize(int,int,int,int);

  /**
    Is turned off when FLTK creates a new context for this window or 
    when the window resizes, and is turned on \e after draw() is called.
    You can use this inside your draw() method to avoid unnecessarily
    initializing the OpenGL context. Just do this:
    \code
    void mywindow::draw() {
     if (!valid()) {
       glViewport(0,0,w(),h());
       glFrustum(...);
       ...other initialization...
     }
     if (!context_valid()) {
       ...load textures, etc. ...
     }
     ... draw your geometry here ...
    }
    \endcode
    
    You can turn valid() on by calling valid(1).  You
    should only do this after fixing the transformation inside a draw()
    or after make_current().  This is done automatically after 
    draw() returns.
  */
  char valid() const {return valid_f_ & 1;}
  /**
    See char Fl_Gl_Window::valid() const 
  */
  void valid(char v) {if (v) valid_f_ |= 1; else valid_f_ &= 0xfe;}
  void invalidate();

  /**
    Will only be set if the 
    OpenGL context is created or recreated. It differs from
    Fl_Gl_Window::valid() which is also set whenever the context
    changes size.
  */
  char context_valid() const {return valid_f_ & 2;}
  /**
    See char Fl_Gl_Window::context_valid() const 
  */
  void context_valid(char v) {if (v) valid_f_ |= 2; else valid_f_ &= 0xfd;}

  /**  Returns non-zero if the hardware supports the given or current OpenGL mode. */
  static int can_do(int m) {return can_do(m,0);}
  /**  Returns non-zero if the hardware supports the given or current OpenGL mode. */
  static int can_do(const int *m) {return can_do(0, m);}
  /**  Returns non-zero if the hardware supports the given or current OpenGL mode. */
  int can_do() {return can_do(mode_,alist);}
  /**
    Set or change the OpenGL capabilites of the window.  The value can be
    any of the following OR'd together:

    - \c FL_RGB - RGB color (not indexed)
    - \c FL_RGB8 - RGB color with at least 8 bits of each color
    - \c FL_INDEX - Indexed mode
    - \c FL_SINGLE - not double buffered
    - \c FL_DOUBLE - double buffered
    - \c FL_ACCUM - accumulation buffer
    - \c FL_ALPHA - alpha channel in color
    - \c FL_DEPTH - depth buffer
    - \c FL_STENCIL - stencil buffer
    - \c FL_MULTISAMPLE - multisample antialiasing

    FL_RGB and FL_SINGLE have a value of zero, so they
    are "on" unless you give FL_INDEX or FL_DOUBLE.

    If the desired combination cannot be done, FLTK will try turning off 
    FL_MULTISAMPLE.  If this also fails the show() will call 
    Fl::error() and not show the window.

    You can change the mode while the window is displayed.  This is most
    useful for turning double-buffering on and off.  Under X this will
    cause the old X window to be destroyed and a new one to be created.  If
    this is a top-level window this will unfortunately also cause the
    window to blink, raise to the top, and be de-iconized, and the xid()
    will change, possibly breaking other code.  It is best to make the GL
    window a child of another window if you wish to do this!

    mode() must not be called within draw() since it
    changes the current context.
  */
  Fl_Mode mode() const {return (Fl_Mode)mode_;}
  /** See Fl_Mode mode() const */
  int mode(int a) {return mode(a,0);}
  /** See Fl_Mode mode() const */
  int mode(const int *a) {return mode(0, a);}
  /** void See void context(void* v, int destroy_flag) */
  void* context() const {return context_;}
  void context(void*, int destroy_flag = 0);
  void make_current();
  void swap_buffers();
  void ortho();

  /**
    Returns true if the hardware overlay is possible.  If this is false,
    FLTK will try to simulate the overlay, with significant loss of update
    speed.  Calling this will cause FLTK to open the display.
  */
  int can_do_overlay();
  /**
    This method causes draw_overlay() to be called at a later time.
    Initially the overlay is clear. If you want the window to display
    something in the overlay when it first appears, you must call this
    immediately after you show() your window.
  */
  void redraw_overlay();
  void hide_overlay();
  /**
    The make_overlay_current() method selects the OpenGL context
    for the widget's overlay.  It is called automatically prior to the 
    draw_overlay() method being called and can also be used to
    implement feedback and/or selection within the handle()
    method.
  */
  void make_overlay_current();

  ~Fl_Gl_Window();
  /**
    Creates a new Fl_Gl_Window widget using the given size, and label string. 
    The default boxtype is FL_NO_BOX. The default mode is FL_RGB|FL_DOUBLE|FL_DEPTH.
  */
  Fl_Gl_Window(int W, int H, const char *l=0) : Fl_Window(W,H,l) {init();}
  /**
    Creates a new Fl_Gl_Window widget using the given position,
    size, and label string. The default boxtype is FL_NO_BOX. The
    default mode is FL_RGB|FL_DOUBLE|FL_DEPTH.
  */

  Fl_Gl_Window(int X, int Y, int W, int H, const char *l=0)
    : Fl_Window(X,Y,W,H,l) {init();}

protected:
  /**
    Draws the Fl_Gl_Window.

    You \e \b must override the draw() method.
  */
  virtual void draw();
};

#endif

//
// End of "$Id: Fl_Gl_Window.H 6664 2009-02-18 09:27:54Z AlbrechtS $".
//

/* suggested twin class
// This is the Twin Class to fltk::GlWindow
class Fl_Gl_Window : public fltk::GlWindow {
public:
  Fl_Gl_Window(int x, int t, int w, int h, const char *label=0)
  : fltk::GlWindow(x, y, w, h, label), compat_(FLTK1) { }
};
*/

// ----- FLTK1 -----------------------------------------------------------------
#if 0
//
// "$Id: Fl_Gl_Window.H 6664 2009-02-18 09:27:54Z AlbrechtS $"
//
// OpenGL header file for the Fast Light Tool Kit (FLTK).
//
// Copyright 1998-2009 by Bill Spitzak and others.
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

/* \file
   Fl_Gl_Window widget . */

#ifndef Fl_Gl_Window_H
#define Fl_Gl_Window_H

#include "Fl_Window.H"

#ifndef GLContext
/**
  Opaque pointer type to hide system specific implementation.
*/
typedef void* GLContext; // actually a GLXContext or HGLDC
#endif

class Fl_Gl_Choice; // structure to hold result of glXChooseVisual

/**
  The Fl_Gl_Window widget sets things up so OpenGL works.
  
  It also keeps an OpenGL "context" for that window, so that changes to the
  lighting and projection may be reused between redraws. Fl_Gl_Window
  also flushes the OpenGL streams and swaps buffers after draw() returns.

  OpenGL hardware typically provides some overlay bit planes, which
  are very useful for drawing UI controls atop your 3D graphics.  If the
  overlay hardware is not provided, FLTK tries to simulate the overlay.
  This works pretty well if your graphics are double buffered, but not
  very well for single-buffered.

  Please note that the FLTK drawing and clipping functions
  will not work inside an Fl_Gl_Window. All drawing
  should be done using OpenGL calls exclusively.
  Even though Fl_Gl_Window is derived from Fl_Group, 
  it is not useful to add other FLTK Widgets as children,
  unless those widgets are modified to draw using OpenGL calls.
*/
class FL_EXPORT Fl_Gl_Window : public Fl_Window {

  int mode_;
  const int *alist;
  Fl_Gl_Choice *g;
  GLContext context_;
  char valid_f_;
  char damage1_; // damage() of back buffer
  virtual void draw_overlay();
  void init();

  void *overlay;
  void make_overlay();
  friend class _Fl_Gl_Overlay;

  static int can_do(int, const int *);
  int mode(int, const int *);

public:

  void show();
  void show(int a, char **b) {Fl_Window::show(a,b);}
  void flush();
  void hide();
  void resize(int,int,int,int);

  /**
    Is turned off when FLTK creates a new context for this window or 
    when the window resizes, and is turned on \e after draw() is called.
    You can use this inside your draw() method to avoid unnecessarily
    initializing the OpenGL context. Just do this:
    \code
    void mywindow::draw() {
     if (!valid()) {
       glViewport(0,0,w(),h());
       glFrustum(...);
       ...other initialization...
     }
     if (!context_valid()) {
       ...load textures, etc. ...
     }
     ... draw your geometry here ...
    }
    \endcode
    
    You can turn valid() on by calling valid(1).  You
    should only do this after fixing the transformation inside a draw()
    or after make_current().  This is done automatically after 
    draw() returns.
  */
  char valid() const {return valid_f_ & 1;}
  /**
    See char Fl_Gl_Window::valid() const 
  */
  void valid(char v) {if (v) valid_f_ |= 1; else valid_f_ &= 0xfe;}
  void invalidate();

  /**
    Will only be set if the 
    OpenGL context is created or recreated. It differs from
    Fl_Gl_Window::valid() which is also set whenever the context
    changes size.
  */
  char context_valid() const {return valid_f_ & 2;}
  /**
    See char Fl_Gl_Window::context_valid() const 
  */
  void context_valid(char v) {if (v) valid_f_ |= 2; else valid_f_ &= 0xfd;}

  /**  Returns non-zero if the hardware supports the given or current OpenGL mode. */
  static int can_do(int m) {return can_do(m,0);}
  /**  Returns non-zero if the hardware supports the given or current OpenGL mode. */
  static int can_do(const int *m) {return can_do(0, m);}
  /**  Returns non-zero if the hardware supports the given or current OpenGL mode. */
  int can_do() {return can_do(mode_,alist);}
  /**
    Set or change the OpenGL capabilites of the window.  The value can be
    any of the following OR'd together:

    - \c FL_RGB - RGB color (not indexed)
    - \c FL_RGB8 - RGB color with at least 8 bits of each color
    - \c FL_INDEX - Indexed mode
    - \c FL_SINGLE - not double buffered
    - \c FL_DOUBLE - double buffered
    - \c FL_ACCUM - accumulation buffer
    - \c FL_ALPHA - alpha channel in color
    - \c FL_DEPTH - depth buffer
    - \c FL_STENCIL - stencil buffer
    - \c FL_MULTISAMPLE - multisample antialiasing

    FL_RGB and FL_SINGLE have a value of zero, so they
    are "on" unless you give FL_INDEX or FL_DOUBLE.

    If the desired combination cannot be done, FLTK will try turning off 
    FL_MULTISAMPLE.  If this also fails the show() will call 
    Fl::error() and not show the window.

    You can change the mode while the window is displayed.  This is most
    useful for turning double-buffering on and off.  Under X this will
    cause the old X window to be destroyed and a new one to be created.  If
    this is a top-level window this will unfortunately also cause the
    window to blink, raise to the top, and be de-iconized, and the xid()
    will change, possibly breaking other code.  It is best to make the GL
    window a child of another window if you wish to do this!

    mode() must not be called within draw() since it
    changes the current context.
  */
  Fl_Mode mode() const {return (Fl_Mode)mode_;}
  /** See Fl_Mode mode() const */
  int mode(int a) {return mode(a,0);}
  /** See Fl_Mode mode() const */
  int mode(const int *a) {return mode(0, a);}
  /** void See void context(void* v, int destroy_flag) */
  void* context() const {return context_;}
  void context(void*, int destroy_flag = 0);
  void make_current();
  void swap_buffers();
  void ortho();

  /**
    Returns true if the hardware overlay is possible.  If this is false,
    FLTK will try to simulate the overlay, with significant loss of update
    speed.  Calling this will cause FLTK to open the display.
  */
  int can_do_overlay();
  /**
    This method causes draw_overlay() to be called at a later time.
    Initially the overlay is clear. If you want the window to display
    something in the overlay when it first appears, you must call this
    immediately after you show() your window.
  */
  void redraw_overlay();
  void hide_overlay();
  /**
    The make_overlay_current() method selects the OpenGL context
    for the widget's overlay.  It is called automatically prior to the 
    draw_overlay() method being called and can also be used to
    implement feedback and/or selection within the handle()
    method.
  */
  void make_overlay_current();

  ~Fl_Gl_Window();
  /**
    Creates a new Fl_Gl_Window widget using the given size, and label string. 
    The default boxtype is FL_NO_BOX. The default mode is FL_RGB|FL_DOUBLE|FL_DEPTH.
  */
  Fl_Gl_Window(int W, int H, const char *l=0) : Fl_Window(W,H,l) {init();}
  /**
    Creates a new Fl_Gl_Window widget using the given position,
    size, and label string. The default boxtype is FL_NO_BOX. The
    default mode is FL_RGB|FL_DOUBLE|FL_DEPTH.
  */

  Fl_Gl_Window(int X, int Y, int W, int H, const char *l=0)
    : Fl_Window(X,Y,W,H,l) {init();}

protected:
  /**
    Draws the Fl_Gl_Window.

    You \e \b must override the draw() method.
  */
  virtual void draw();
};

#endif

//
// End of "$Id: Fl_Gl_Window.H 6664 2009-02-18 09:27:54Z AlbrechtS $".
//
#endif
// ----- FLTK2 -----------------------------------------------------------------
#if 0
//
// "$Id: GlWindow.h 5892 2007-06-08 18:15:37Z spitzak $"
//
// OpenGL window. You must subclass this and implement draw() if
// you want this to work.
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
// Please report all bugs and problems to "fltk-bugs@fltk.org".

#ifndef fltk_GlWindow_h
#define fltk_GlWindow_h

#include "Window.h"

namespace fltk {

#ifndef GLContext // you can define this to the correct type if wanted
typedef void* GLContext; //!< Actually a GLXContext or HGLDC
#endif

class GlChoice; // structure to hold result of glXChooseVisual
class GlOverlay; // used by X version for the overlay

enum {
  NO_AUTO_SWAP = 1024,
  NO_ERASE_OVERLAY = 2048
};

class FL_GL_API GlWindow : public Window {

public:

  void create();
  void flush();
  void destroy();
  void layout();

  char valid() const {return valid_;}
  void valid(char i) {valid_ = i;}
  void invalidate();

  int mode() const {return mode_;}
  bool mode(int a);
  static bool can_do(int);
  bool can_do() const {return can_do(mode_);}

  GLContext context() const {return context_;}
  // this wrapper is so c++mangled name does not depend on GLContext type:
  void context(GLContext v, bool destroy_flag = false) {_context(v,destroy_flag);}
  void make_current();
  void swap_buffers();
  void ortho();

  bool can_do_overlay();
  void redraw_overlay();
  void hide_overlay();
  void make_overlay_current();

  ~GlWindow();
  GlWindow(int W, int H, const char *l=0) : Window(W,H,l) {init();}
  GlWindow(int X, int Y, int W, int H, const char *l=0)
    : Window(X,Y,W,H,l) {init();}

  virtual void draw() = 0;
  virtual void draw_overlay();

  virtual int handle( int event );

private:

  int mode_;
  GlChoice *gl_choice;
  GLContext context_;
  void _context(void*, bool destroy_flag);
  char valid_;
  char damage1_; // damage() of back buffer
  void init();

  void *overlay;
  void make_overlay();
  friend class GlOverlay;

  void draw_swap();
};

}

#endif

//
// End of "$Id: GlWindow.h 5892 2007-06-08 18:15:37Z spitzak $".
//
#endif
// ----- END -------------------------------------------------------------------
//
// End of "$Id$"
//
