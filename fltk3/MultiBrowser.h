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
// "$Id: Fl_Multi_Browser.H 6614 2009-01-01 16:11:32Z matt $"
//
// Multi browser header file for the Fast Light Tool Kit (FLTK).
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
   Fl_Multi_Browser widget . */

#ifndef Fl_Multi_Browser_H
#define Fl_Multi_Browser_H

#include "Fl_Browser.H"

/**
  The Fl_Multi_Browser class is a subclass of Fl_Browser
  which lets the user select any set of the lines.  The user interface
  is Macintosh style: clicking an item turns off all the others and
  selects that one, dragging selects all the items the mouse moves over,
  and shift + click toggles the items. This is different then how forms
  did it.  Normally the callback is done when the user releases the
  mouse, but you can change this with when().
  <P>See Fl_Browser for methods to add and remove lines from the browser.
*/
class Fl_Multi_Browser : public Fl_Browser {
public:
  /**
      Creates a new Fl_Multi_Browser widget using the given
    position, size, and label string. The default boxtype is FL_DOWN_BOX.
    The constructor specializes Fl_Browser() by setting the type to FL_MULTI_BROWSER.
    The destructor destroys the widget and frees all memory that has been allocated.
  */
    Fl_Multi_Browser(int X,int Y,int W,int H,const char *L=0)
	: Fl_Browser(X,Y,W,H,L) {type(FL_MULTI_BROWSER);}
};

#endif

//
// End of "$Id: Fl_Multi_Browser.H 6614 2009-01-01 16:11:32Z matt $".
//

/* suggested twin class
// This is the Twin Class to fltk::MultiBrowser
class Fl_Multi_Browser : public fltk::MultiBrowser {
public:
  Fl_Multi_Browser(int x, int t, int w, int h, const char *label=0)
  : fltk::MultiBrowser(x, y, w, h, label), compat_(FLTK1) { }
};
*/

// ----- FLTK1 -----------------------------------------------------------------
#if 0
//
// "$Id: Fl_Multi_Browser.H 6614 2009-01-01 16:11:32Z matt $"
//
// Multi browser header file for the Fast Light Tool Kit (FLTK).
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
   Fl_Multi_Browser widget . */

#ifndef Fl_Multi_Browser_H
#define Fl_Multi_Browser_H

#include "Fl_Browser.H"

/**
  The Fl_Multi_Browser class is a subclass of Fl_Browser
  which lets the user select any set of the lines.  The user interface
  is Macintosh style: clicking an item turns off all the others and
  selects that one, dragging selects all the items the mouse moves over,
  and shift + click toggles the items. This is different then how forms
  did it.  Normally the callback is done when the user releases the
  mouse, but you can change this with when().
  <P>See Fl_Browser for methods to add and remove lines from the browser.
*/
class Fl_Multi_Browser : public Fl_Browser {
public:
  /**
      Creates a new Fl_Multi_Browser widget using the given
    position, size, and label string. The default boxtype is FL_DOWN_BOX.
    The constructor specializes Fl_Browser() by setting the type to FL_MULTI_BROWSER.
    The destructor destroys the widget and frees all memory that has been allocated.
  */
    Fl_Multi_Browser(int X,int Y,int W,int H,const char *L=0)
	: Fl_Browser(X,Y,W,H,L) {type(FL_MULTI_BROWSER);}
};

#endif

//
// End of "$Id: Fl_Multi_Browser.H 6614 2009-01-01 16:11:32Z matt $".
//
#endif
// ----- FLTK2 -----------------------------------------------------------------
#if 0
//
// "$Id: MultiBrowser.h 4886 2006-03-30 09:55:32Z fabien $"
//
// Browser that lets the user select more than one item at a time.
// Most of the implementation is in the base Browser class.
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
//

#ifndef fltk_MultiBrowser_h
#define fltk_MultiBrowser_h

#include "Browser.h"

namespace fltk {

// This class is entirely inline.  If that changes, add FL_API to its declaration
class MultiBrowser : public Browser {
public:
    MultiBrowser(int x,int y,int w,int h,const char *l=0)
	: Browser(x,y,w,h,l) {type(MULTI);}
};

}

#endif

//
// End of "$Id: MultiBrowser.h 4886 2006-03-30 09:55:32Z fabien $".
//
#endif
// ----- END -------------------------------------------------------------------
//
// End of "$Id$"
//
