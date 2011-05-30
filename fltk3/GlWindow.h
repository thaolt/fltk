//
// "$Id: GlWindow.h 8157 2011-01-01 14:01:53Z AlbrechtS $"
//
// OpenGL header file for the Fast Light Tool Kit (FLTK).
//
// Copyright 1998-2010 by Bill Spitzak and others.
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
 fltk3::GlWindow widget . */

#ifndef Fltk3_Gl_Window_H
#define Fltk3_Gl_Window_H

#include "Window.h"

#ifndef GLContext
/**
 Opaque pointer type to hide system specific implementation.
 */
typedef void* GLContext; // actually a GLXContext or HGLDC
#endif

class Fl_Gl_Window;

namespace fltk3 {
  
  class GlChoice; // structure to hold result of glXChooseVisual

  /**
   The fltk3::GlWindow widget sets things up so OpenGL works.
   
   It also keeps an OpenGL "context" for that window, so that changes to the
   lighting and projection may be reused between redraws. fltk3::GlWindow
   also flushes the OpenGL streams and swaps buffers after draw() returns.
   
   OpenGL hardware typically provides some overlay bit planes, which
   are very useful for drawing UI controls atop your 3D graphics.  If the
   overlay hardware is not provided, FLTK tries to simulate the overlay.
   This works pretty well if your graphics are double buffered, but not
   very well for single-buffered.
   
   Please note that the FLTK drawing and clipping functions
   will not work inside an fltk3::GlWindow. All drawing
   should be done using OpenGL calls exclusively.
   Even though fltk3::GlWindow is derived from fltk3::Group, 
   it is not useful to add other FLTK Widgets as children,
   unless those widgets are modified to draw using OpenGL calls.
   */
  class FLTK3_EXPORT GlWindow : public fltk3::Window {
    
    friend class ::Fl_Gl_Window;

    int mode_;
    const int *alist;
    GlChoice *g;
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
    void show(int a, char **b) {fltk3::Window::show(a,b);}
    void flush();
    void hide();
    void resize(int,int,int,int);
    int handle(int);
    
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
     See char fltk3::GlWindow::valid() const 
     */
    void valid(char v) {if (v) valid_f_ |= 1; else valid_f_ &= 0xfe;}
    void invalidate();
    
    /**
     Will only be set if the 
     OpenGL context is created or recreated. It differs from
     fltk3::GlWindow::valid() which is also set whenever the context
     changes size.
     */
    char context_valid() const {return valid_f_ & 2;}
    /**
     See char fltk3::GlWindow::context_valid() const 
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
     
     - \c fltk3::RGB - RGB color (not indexed)
     - \c fltk3::RGB8 - RGB color with at least 8 bits of each color
     - \c fltk3::INDEX - Indexed mode
     - \c fltk3::SINGLE - not double buffered
     - \c fltk3::DOUBLE - double buffered
     - \c fltk3::ACCUM - accumulation buffer
     - \c fltk3::ALPHA - alpha channel in color
     - \c fltk3::DEPTH - depth buffer
     - \c fltk3::STENCIL - stencil buffer
     - \c fltk3::MULTISAMPLE - multisample antialiasing
     
     fltk3::RGB and fltk3::SINGLE have a value of zero, so they
     are "on" unless you give fltk3::INDEX or fltk3::DOUBLE.
     
     If the desired combination cannot be done, FLTK will try turning off 
     fltk3::MULTISAMPLE.  If this also fails the show() will call 
     fltk3::error() and not show the window.
     
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
    fltk3::Mode mode() const {return (fltk3::Mode)mode_;}
    /** See fltk3::Mode mode() const */
    int mode(int a) {return mode(a,0);}
    /** See fltk3::Mode mode() const */
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
    
    // Note: Doxygen docs in Widget.h to avoid redundancy.
    virtual fltk3::GlWindow* as_gl_window() {return this;}
    
    ~GlWindow();
    /**
     Creates a new fltk3::GlWindow widget using the given size, and label string. 
     The default boxtype is fltk3::NO_BOX. The default mode is fltk3::RGB|fltk3::DOUBLE|fltk3::DEPTH.
     */
    GlWindow(int W, int H, const char *l=0) : fltk3::Window(W,H,l) {init();}
    /**
     Creates a new fltk3::GlWindow widget using the given position,
     size, and label string. The default boxtype is fltk3::NO_BOX. The
     default mode is fltk3::RGB|fltk3::DOUBLE|fltk3::DEPTH.
     */
    
    GlWindow(int X, int Y, int W, int H, const char *l=0)
    : fltk3::Window(X,Y,W,H,l) {init();}
    
  protected:
    /**
     Draws the fltk3::GlWindow.
     
     You \e \b must override the draw() method.
     */
    virtual void draw();
  };
  
}

#endif

//
// End of "$Id: GlWindow.h 8157 2011-01-01 14:01:53Z AlbrechtS $".
//
