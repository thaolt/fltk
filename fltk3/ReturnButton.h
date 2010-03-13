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
// "$Id: Fl_Return_Button.H 6614 2009-01-01 16:11:32Z matt $"
//
// Return button header file for the Fast Light Tool Kit (FLTK).
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
   Fl_Return_Button widget . */

#ifndef Fl_Return_Button_H
#define Fl_Return_Button_H
#include "Button.h"

/**
  The Fl_Return_Button is a subclass of Fl_Button that
  generates a callback when it is pressed or when the user presses the
  Enter key.  A carriage-return symbol is drawn next to the button label.
  <P ALIGN=CENTER>\image html Fl_Return_Button.gif 
  \image latex Fl_Return_Button.eps "Fl_Return_Button" width=4cm
*/
class FL_EXPORT Fl_Return_Button : public Fl_Button {
protected:
  void draw();
public:
  int handle(int);
  /**
    Creates a new Fl_Return_Button widget using the given
    position, size, and label string. The default boxtype is FL_UP_BOX.
    <P> The inherited destructor deletes the button.
  */
  Fl_Return_Button(int X, int Y, int W, int H,const char *l=0)
    : Fl_Button(X,Y,W,H,l) {}
};

#endif

//
// End of "$Id: Fl_Return_Button.H 6614 2009-01-01 16:11:32Z matt $".
//

/* suggested twin class
// This is the Twin Class to fltk::ReturnButton
class Fl_Return_Button : public fltk::ReturnButton {
public:
  Fl_Return_Button(int x, int t, int w, int h, const char *label=0)
  : fltk::ReturnButton(x, y, w, h, label), compat_(FLTK1) { }
};
*/

// ----- FLTK1 -----------------------------------------------------------------
#if 0
//
// "$Id: Fl_Return_Button.H 6614 2009-01-01 16:11:32Z matt $"
//
// Return button header file for the Fast Light Tool Kit (FLTK).
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
   Fl_Return_Button widget . */

#ifndef Fl_Return_Button_H
#define Fl_Return_Button_H
#include "Fl_Button.H"

/**
  The Fl_Return_Button is a subclass of Fl_Button that
  generates a callback when it is pressed or when the user presses the
  Enter key.  A carriage-return symbol is drawn next to the button label.
  <P ALIGN=CENTER>\image html Fl_Return_Button.gif 
  \image latex Fl_Return_Button.eps "Fl_Return_Button" width=4cm
*/
class FL_EXPORT Fl_Return_Button : public Fl_Button {
protected:
  void draw();
public:
  int handle(int);
  /**
    Creates a new Fl_Return_Button widget using the given
    position, size, and label string. The default boxtype is FL_UP_BOX.
    <P> The inherited destructor deletes the button.
  */
  Fl_Return_Button(int X, int Y, int W, int H,const char *l=0)
    : Fl_Button(X,Y,W,H,l) {}
};

#endif

//
// End of "$Id: Fl_Return_Button.H 6614 2009-01-01 16:11:32Z matt $".
//
#endif
// ----- FLTK2 -----------------------------------------------------------------
#if 0
// "$Id: ReturnButton.h 4886 2006-03-30 09:55:32Z fabien $"
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

#ifndef fltk_ReturnButton_h
#define fltk_ReturnButton_h

#include "Button.h"

namespace fltk {

class FL_API ReturnButton : public Button {
public:
  ReturnButton(int x,int y,int w,int h,const char *l=0);
  static NamedStyle* default_style;
protected:
  void draw();
};

}

#endif

// End of "$Id: ReturnButton.h 4886 2006-03-30 09:55:32Z fabien $".
#endif
// ----- END -------------------------------------------------------------------
//
// End of "$Id$"
//
