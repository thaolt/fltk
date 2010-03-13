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
// "$Id: Fl_Menu_Window.H 6909 2009-09-28 14:41:43Z matt $"
//
// Menu window header file for the Fast Light Tool Kit (FLTK).
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
   Fl_Menu_Window widget . */

#ifndef Fl_Menu_Window_H
#define Fl_Menu_Window_H

#include "SingleWindow.h"

/**
  The Fl_Menu_Window widget is a window type used for menus. By
  default the window is drawn in the hardware overlay planes if they are
  available so that the menu don't force the rest of the window to
  redraw.
*/
class FL_EXPORT Fl_Menu_Window : public Fl_Single_Window {
public:
  void show();
  void erase();
  void flush();
  void hide();
  /** Tells if hardware overlay mode is set */
  unsigned int overlay() {return !(flags()&NO_OVERLAY);}
  /** Tells FLTK to use hardware overlay planes if they are available.  */
  void set_overlay() {clear_flag(NO_OVERLAY);}
  /** Tells FLTK to use normal drawing planes instead of overlay planes.
      This is usually necessary if your menu contains multi-color pixmaps. */
  void clear_overlay() {set_flag(NO_OVERLAY);}
  ~Fl_Menu_Window();
  /** Creates a new Fl_Menu_Window widget using the given size, and label string. */
  Fl_Menu_Window(int W, int H, const char *l = 0)
    : Fl_Single_Window(W,H,l) { image(0); }
  /** Creates a new Fl_Menu_Window widget using the given position, size, and label string. */
  Fl_Menu_Window(int X, int Y, int W, int H, const char *l = 0)
    : Fl_Single_Window(X,Y,W,H,l) { image(0); }
};

#endif

//
// End of "$Id: Fl_Menu_Window.H 6909 2009-09-28 14:41:43Z matt $".
//

/* suggested twin class
// This is the Twin Class to fltk::MenuWindow
class Fl_Menu_Window : public fltk::MenuWindow {
public:
  Fl_Menu_Window(int x, int t, int w, int h, const char *label=0)
  : fltk::MenuWindow(x, y, w, h, label), compat_(FLTK1) { }
};
*/

// ----- FLTK1 -----------------------------------------------------------------
#if 0
//
// "$Id: Fl_Menu_Window.H 6909 2009-09-28 14:41:43Z matt $"
//
// Menu window header file for the Fast Light Tool Kit (FLTK).
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
   Fl_Menu_Window widget . */

#ifndef Fl_Menu_Window_H
#define Fl_Menu_Window_H

#include "Fl_Single_Window.H"

/**
  The Fl_Menu_Window widget is a window type used for menus. By
  default the window is drawn in the hardware overlay planes if they are
  available so that the menu don't force the rest of the window to
  redraw.
*/
class FL_EXPORT Fl_Menu_Window : public Fl_Single_Window {
public:
  void show();
  void erase();
  void flush();
  void hide();
  /** Tells if hardware overlay mode is set */
  unsigned int overlay() {return !(flags()&NO_OVERLAY);}
  /** Tells FLTK to use hardware overlay planes if they are available.  */
  void set_overlay() {clear_flag(NO_OVERLAY);}
  /** Tells FLTK to use normal drawing planes instead of overlay planes.
      This is usually necessary if your menu contains multi-color pixmaps. */
  void clear_overlay() {set_flag(NO_OVERLAY);}
  ~Fl_Menu_Window();
  /** Creates a new Fl_Menu_Window widget using the given size, and label string. */
  Fl_Menu_Window(int W, int H, const char *l = 0)
    : Fl_Single_Window(W,H,l) { image(0); }
  /** Creates a new Fl_Menu_Window widget using the given position, size, and label string. */
  Fl_Menu_Window(int X, int Y, int W, int H, const char *l = 0)
    : Fl_Single_Window(X,Y,W,H,l) { image(0); }
};

#endif

//
// End of "$Id: Fl_Menu_Window.H 6909 2009-09-28 14:41:43Z matt $".
//
#endif
// ----- FLTK2 -----------------------------------------------------------------
#if 0
// "$Id: MenuWindow.h 5600 2007-01-13 00:04:55Z spitzak $"
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

#ifndef fltk_MenuWindow_h
#define fltk_MenuWindow_h

#include "Window.h"

namespace fltk {

class FL_API MenuWindow : public Window {
  enum {NO_OVERLAY = 0x08000000};

public:

  virtual void create();
  virtual void flush();
  virtual void destroy();

  static NamedStyle* default_style;

  int overlay() {return !flag(NO_OVERLAY);}
  void set_overlay() {clear_flag(NO_OVERLAY);}
  void clear_overlay() {set_flag(NO_OVERLAY);}
  ~MenuWindow();
  MenuWindow(int W, int H, const char *l = 0);
  MenuWindow(int X, int Y, int W, int H, const char *l = 0);

};

}

#endif

//
// End of "$Id: MenuWindow.h 5600 2007-01-13 00:04:55Z spitzak $".
//
#endif
// ----- END -------------------------------------------------------------------
//
// End of "$Id$"
//
