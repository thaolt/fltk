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
// "$Id: x.H 6614 2009-01-01 16:11:32Z matt $"
//
// X11 header file for the Fast Light Tool Kit (FLTK).
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

// These are internal fltk symbols that are necessary or useful for
// calling Xlib.  You should include this file if (and ONLY if) you
// need to call Xlib directly.  These symbols may not exist on non-X
// systems.

#if !defined(Fl_X_H) && !defined(FL_DOXYGEN) 
#  define Fl_X_H

#  include "Enumerations.H"

#  ifdef WIN32
#    include "win32.H"
#  elif defined(__APPLE__)
#    include "osx.h"
#  else
#    if defined(_ABIN32) || defined(_ABI64) // fix for broken SGI Irix X .h files
#      pragma set woff 3322
#    endif
#    include <X11/Xlib.h>
#    include <X11/Xutil.h>
#    if defined(_ABIN32) || defined(_ABI64)
#      pragma reset woff 3322
#    endif
#    include <X11/Xatom.h>
#    include "Fl_Window.H"
#    include "Xutf8.h"
// Mirror X definition of Region to Fl_Region, for portability...
typedef Region Fl_Region;

FL_EXPORT void fl_open_display();
FL_EXPORT void fl_open_display(Display*);
FL_EXPORT void fl_close_display();

// constant info about the X server connection:
extern FL_EXPORT Display *fl_display;
extern FL_EXPORT Window fl_message_window;
extern FL_EXPORT int fl_screen;
extern FL_EXPORT XVisualInfo *fl_visual;
extern FL_EXPORT Colormap fl_colormap;

// drawing functions:
extern FL_EXPORT GC fl_gc;
extern FL_EXPORT Window fl_window;
//extern FL_EXPORT XFontStruct* fl_xfont;
extern FL_EXPORT XUtf8FontStruct* fl_xfont;
extern FL_EXPORT void *fl_xftfont;
FL_EXPORT ulong fl_xpixel(Fl_Color i);
FL_EXPORT ulong fl_xpixel(uchar r, uchar g, uchar b);
FL_EXPORT void fl_clip_region(Fl_Region);
FL_EXPORT Fl_Region fl_clip_region();
FL_EXPORT Fl_Region XRectangleRegion(int x, int y, int w, int h); // in fl_rect.cxx

// feed events into fltk:
FL_EXPORT int fl_handle(const XEvent&);

// you can use these in Fl::add_handler() to look at events:
extern FL_EXPORT const XEvent* fl_xevent;
extern FL_EXPORT ulong fl_event_time;

// off-screen pixmaps: create, destroy, draw into, copy to window:
typedef ulong Fl_Offscreen;
#define fl_create_offscreen(w,h) \
  XCreatePixmap(fl_display, fl_window, w, h, fl_visual->depth)
// begin/end are macros that save the old state in local variables:
#    define fl_begin_offscreen(pixmap) \
  Window _sw=fl_window; fl_window=pixmap; fl_push_no_clip()
#    define fl_end_offscreen() \
  fl_pop_clip(); fl_window = _sw

#    define fl_copy_offscreen(x,y,w,h,pixmap,srcx,srcy) \
  XCopyArea(fl_display, pixmap, fl_window, fl_gc, srcx, srcy, w, h, x, y)
#    define fl_delete_offscreen(pixmap) XFreePixmap(fl_display, pixmap)

// Bitmap masks
typedef ulong Fl_Bitmask;

extern FL_EXPORT Fl_Bitmask fl_create_bitmask(int w, int h, const uchar *data);
extern FL_EXPORT Fl_Bitmask fl_create_alphamask(int w, int h, int d, int ld, const uchar *data);
extern FL_EXPORT void fl_delete_bitmask(Fl_Bitmask bm);

// this object contains all X-specific stuff about a window:
// Warning: this object is highly subject to change!  It's definition
// is only here so that fl_xid can be declared inline:
class FL_EXPORT Fl_X {
public:
  Window xid;
  Window other_xid;
  Fl_Window *w;
  Fl_Region region;
  Fl_X *next;
  char wait_for_expose;
  char backbuffer_bad; // used for XDBE
  static Fl_X* first;
  static Fl_X* i(const Fl_Window* wi) {return wi->i;}
  void setwindow(Fl_Window* wi) {w=wi; wi->i=this;}
  void sendxjunk();
  static void make_xid(Fl_Window*,XVisualInfo* =fl_visual, Colormap=fl_colormap);
  static Fl_X* set_xid(Fl_Window*, Window);
  // kludges to get around protection:
  void flush() {w->flush();}
  static void x(Fl_Window* wi, int X) {wi->x(X);}
  static void y(Fl_Window* wi, int Y) {wi->y(Y);}
};

// convert xid <-> Fl_Window:
inline Window fl_xid(const Fl_Window*w) {return Fl_X::i(w)->xid;}
FL_EXPORT Fl_Window* fl_find(Window xid);

extern FL_EXPORT char fl_override_redirect; // hack into Fl_X::make_xid()
extern FL_EXPORT int fl_background_pixel;  // hack into Fl_X::make_xid()

// Dummy function to register a function for opening files via the window manager...
inline void fl_open_callback(void (*)(const char *)) {}

extern FL_EXPORT int fl_parse_color(const char* p, uchar& r, uchar& g, uchar& b);

#  endif
#endif

//
// End of "$Id: x.H 6614 2009-01-01 16:11:32Z matt $".
//

/* suggested twin class
// This is the Twin Class to fltk::x
class x : public fltk::x {
public:
  x(int x, int t, int w, int h, const char *label=0)
  : fltk::x(x, y, w, h, label), compat_(FLTK1) { }
};
*/

// ----- FLTK1 -----------------------------------------------------------------
#if 0
//
// "$Id: x.H 6614 2009-01-01 16:11:32Z matt $"
//
// X11 header file for the Fast Light Tool Kit (FLTK).
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

// These are internal fltk symbols that are necessary or useful for
// calling Xlib.  You should include this file if (and ONLY if) you
// need to call Xlib directly.  These symbols may not exist on non-X
// systems.

#if !defined(Fl_X_H) && !defined(FL_DOXYGEN) 
#  define Fl_X_H

#  include "Enumerations.H"

#  ifdef WIN32
#    include "win32.H"
#  elif defined(__APPLE__)
#    include "mac.H"
#  else
#    if defined(_ABIN32) || defined(_ABI64) // fix for broken SGI Irix X .h files
#      pragma set woff 3322
#    endif
#    include <X11/Xlib.h>
#    include <X11/Xutil.h>
#    if defined(_ABIN32) || defined(_ABI64)
#      pragma reset woff 3322
#    endif
#    include <X11/Xatom.h>
#    include "Fl_Window.H"
#    include "Xutf8.h"
// Mirror X definition of Region to Fl_Region, for portability...
typedef Region Fl_Region;

FL_EXPORT void fl_open_display();
FL_EXPORT void fl_open_display(Display*);
FL_EXPORT void fl_close_display();

// constant info about the X server connection:
extern FL_EXPORT Display *fl_display;
extern FL_EXPORT Window fl_message_window;
extern FL_EXPORT int fl_screen;
extern FL_EXPORT XVisualInfo *fl_visual;
extern FL_EXPORT Colormap fl_colormap;

// drawing functions:
extern FL_EXPORT GC fl_gc;
extern FL_EXPORT Window fl_window;
//extern FL_EXPORT XFontStruct* fl_xfont;
extern FL_EXPORT XUtf8FontStruct* fl_xfont;
extern FL_EXPORT void *fl_xftfont;
FL_EXPORT ulong fl_xpixel(Fl_Color i);
FL_EXPORT ulong fl_xpixel(uchar r, uchar g, uchar b);
FL_EXPORT void fl_clip_region(Fl_Region);
FL_EXPORT Fl_Region fl_clip_region();
FL_EXPORT Fl_Region XRectangleRegion(int x, int y, int w, int h); // in fl_rect.cxx

// feed events into fltk:
FL_EXPORT int fl_handle(const XEvent&);

// you can use these in Fl::add_handler() to look at events:
extern FL_EXPORT const XEvent* fl_xevent;
extern FL_EXPORT ulong fl_event_time;

// off-screen pixmaps: create, destroy, draw into, copy to window:
typedef ulong Fl_Offscreen;
#define fl_create_offscreen(w,h) \
  XCreatePixmap(fl_display, fl_window, w, h, fl_visual->depth)
// begin/end are macros that save the old state in local variables:
#    define fl_begin_offscreen(pixmap) \
  Window _sw=fl_window; fl_window=pixmap; fl_push_no_clip()
#    define fl_end_offscreen() \
  fl_pop_clip(); fl_window = _sw

#    define fl_copy_offscreen(x,y,w,h,pixmap,srcx,srcy) \
  XCopyArea(fl_display, pixmap, fl_window, fl_gc, srcx, srcy, w, h, x, y)
#    define fl_delete_offscreen(pixmap) XFreePixmap(fl_display, pixmap)

// Bitmap masks
typedef ulong Fl_Bitmask;

extern FL_EXPORT Fl_Bitmask fl_create_bitmask(int w, int h, const uchar *data);
extern FL_EXPORT Fl_Bitmask fl_create_alphamask(int w, int h, int d, int ld, const uchar *data);
extern FL_EXPORT void fl_delete_bitmask(Fl_Bitmask bm);

// this object contains all X-specific stuff about a window:
// Warning: this object is highly subject to change!  It's definition
// is only here so that fl_xid can be declared inline:
class FL_EXPORT Fl_X {
public:
  Window xid;
  Window other_xid;
  Fl_Window *w;
  Fl_Region region;
  Fl_X *next;
  char wait_for_expose;
  char backbuffer_bad; // used for XDBE
  static Fl_X* first;
  static Fl_X* i(const Fl_Window* wi) {return wi->i;}
  void setwindow(Fl_Window* wi) {w=wi; wi->i=this;}
  void sendxjunk();
  static void make_xid(Fl_Window*,XVisualInfo* =fl_visual, Colormap=fl_colormap);
  static Fl_X* set_xid(Fl_Window*, Window);
  // kludges to get around protection:
  void flush() {w->flush();}
  static void x(Fl_Window* wi, int X) {wi->x(X);}
  static void y(Fl_Window* wi, int Y) {wi->y(Y);}
};

// convert xid <-> Fl_Window:
inline Window fl_xid(const Fl_Window*w) {return Fl_X::i(w)->xid;}
FL_EXPORT Fl_Window* fl_find(Window xid);

extern FL_EXPORT char fl_override_redirect; // hack into Fl_X::make_xid()
extern FL_EXPORT int fl_background_pixel;  // hack into Fl_X::make_xid()

// Dummy function to register a function for opening files via the window manager...
inline void fl_open_callback(void (*)(const char *)) {}

extern FL_EXPORT int fl_parse_color(const char* p, uchar& r, uchar& g, uchar& b);

#  endif
#endif

//
// End of "$Id: x.H 6614 2009-01-01 16:11:32Z matt $".
//
#endif
// ----- FLTK2 -----------------------------------------------------------------
#if 0
// "$Id: x.h 5586 2007-01-07 07:23:21Z spitzak $"
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

/** \file
  "Portably" include either x11.h, win32.h, or osx.h header files,
  depending on your system. Since the system-specific interfaces
  resemble each other somewhat, use of this header and some macros
  may allow you to merge system-specific code for different systems
  together.
*/

#ifndef fltk_x_h
# define fltk_x_h
# if defined(_WIN32) && !USE_X11
#  include "win32.h"
# elif defined(__APPLE__) && !USE_X11
#  include "osx.h"
# else
#  define USE_X11 1
#  include "x11.h"
# endif
#endif

#if USE_CAIRO
# include "fltk_cairo.h"
#endif 
//
// End of "$Id: x.h 5586 2007-01-07 07:23:21Z spitzak $".
//
#endif
// ----- END -------------------------------------------------------------------
//
// End of "$Id$"
//
