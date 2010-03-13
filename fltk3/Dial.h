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
// "$Id: Fl_Dial.H 6614 2009-01-01 16:11:32Z matt $"
//
// Dial header file for the Fast Light Tool Kit (FLTK).
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
   Fl_Dial widget . */

#ifndef Fl_Dial_H
#define Fl_Dial_H

#ifndef Fl_Valuator_H
#include "Valuator.h"
#endif

// values for type():
#define FL_NORMAL_DIAL	0	/**< type() for dial variant with dot */
#define FL_LINE_DIAL	1	/**< type() for dial variant with line */
#define FL_FILL_DIAL	2	/**< type() for dial variant with filled arc */

/**
  The Fl_Dial widget provides a circular dial to control a
  single floating point value.
  <P ALIGN=CENTER>\image html dial.gif 
  \image latex dial.eps "Fl_Dial" width=4cm
  Use type() to set the type of the dial to:
  <UL>
  <LI>FL_NORMAL_DIAL - Draws a normal dial with a knob. </LI>
  <LI>FL_LINE_DIAL - Draws a dial with a line. </LI>
  <LI>FL_FILL_DIAL - Draws a dial with a filled arc. </LI>
  </UL>

*/
class FL_EXPORT Fl_Dial : public Fl_Valuator {

  short a1,a2;

protected:

  // these allow subclasses to put the dial in a smaller area:
  void draw(int X, int Y, int W, int H);
  int handle(int event, int X, int Y, int W, int H);
  void draw();

public:

  int handle(int);
  /**
    Creates a new Fl_Dial widget using the given position, size,
    and label string. The default type is FL_NORMAL_DIAL.
  */
  Fl_Dial(int x,int y,int w,int h, const char *l = 0);
  /** 
     Sets Or gets the angles used for the minimum and maximum values.  The default
     values are 45 and 315 (0 degrees is straight down and the angles
     progress clockwise).  Normally angle1 is less than angle2, but if you
     reverse them the dial moves counter-clockwise.
  */
  short angle1() const {return a1;}
  /** See short angle1() const */
  void angle1(short a) {a1 = a;}
  /** See short angle1() const */
  short angle2() const {return a2;}
  /** See short angle1() const */
  void angle2(short a) {a2 = a;}
  /** See short angle1() const */
  void angles(short a, short b) {a1 = a; a2 = b;}

};

#endif

//
// End of "$Id: Fl_Dial.H 6614 2009-01-01 16:11:32Z matt $".
//

/* suggested twin class
// This is the Twin Class to fltk::Dial
class Fl_Dial : public fltk::Dial {
public:
  Fl_Dial(int x, int t, int w, int h, const char *label=0)
  : fltk::Dial(x, y, w, h, label), compat_(FLTK1) { }
};
*/

// ----- FLTK1 -----------------------------------------------------------------
#if 0
//
// "$Id: Fl_Dial.H 6614 2009-01-01 16:11:32Z matt $"
//
// Dial header file for the Fast Light Tool Kit (FLTK).
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
   Fl_Dial widget . */

#ifndef Fl_Dial_H
#define Fl_Dial_H

#ifndef Fl_Valuator_H
#include "Fl_Valuator.H"
#endif

// values for type():
#define FL_NORMAL_DIAL	0	/**< type() for dial variant with dot */
#define FL_LINE_DIAL	1	/**< type() for dial variant with line */
#define FL_FILL_DIAL	2	/**< type() for dial variant with filled arc */

/**
  The Fl_Dial widget provides a circular dial to control a
  single floating point value.
  <P ALIGN=CENTER>\image html dial.gif 
  \image latex dial.eps "Fl_Dial" width=4cm
  Use type() to set the type of the dial to:
  <UL>
  <LI>FL_NORMAL_DIAL - Draws a normal dial with a knob. </LI>
  <LI>FL_LINE_DIAL - Draws a dial with a line. </LI>
  <LI>FL_FILL_DIAL - Draws a dial with a filled arc. </LI>
  </UL>

*/
class FL_EXPORT Fl_Dial : public Fl_Valuator {

  short a1,a2;

protected:

  // these allow subclasses to put the dial in a smaller area:
  void draw(int X, int Y, int W, int H);
  int handle(int event, int X, int Y, int W, int H);
  void draw();

public:

  int handle(int);
  /**
    Creates a new Fl_Dial widget using the given position, size,
    and label string. The default type is FL_NORMAL_DIAL.
  */
  Fl_Dial(int x,int y,int w,int h, const char *l = 0);
  /** 
     Sets Or gets the angles used for the minimum and maximum values.  The default
     values are 45 and 315 (0 degrees is straight down and the angles
     progress clockwise).  Normally angle1 is less than angle2, but if you
     reverse them the dial moves counter-clockwise.
  */
  short angle1() const {return a1;}
  /** See short angle1() const */
  void angle1(short a) {a1 = a;}
  /** See short angle1() const */
  short angle2() const {return a2;}
  /** See short angle1() const */
  void angle2(short a) {a2 = a;}
  /** See short angle1() const */
  void angles(short a, short b) {a1 = a; a2 = b;}

};

#endif

//
// End of "$Id: Fl_Dial.H 6614 2009-01-01 16:11:32Z matt $".
//
#endif
// ----- FLTK2 -----------------------------------------------------------------
#if 0
//
// "$Id: Dial.h 4910 2006-04-06 19:26:22Z fabien $"
//
// Rotating value control
//
// Copyright 2002 by Bill Spitzak and others.
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

#ifndef fltk_Dial_h
#define fltk_Dial_h

#ifndef fltk_Valuator_h
#include "Valuator.h"
#endif

namespace fltk {

class FL_API Dial : public Valuator {

public:

  enum {NORMAL = 0, LINE, FILL}; // values for type()
  int handle(int);
  Dial(int x,int y,int w,int h, const char *l = 0);
  static NamedStyle* default_style;
  short angle1() const {return a1;}
  void angle1(short a) {a1 = a;}
  short angle2() const {return a2;}
  void angle2(short a) {a2 = a;}
  void angles(short a, short b) {a1 = a; a2 = b;}

protected:

  void draw();

private:

  short a1,a2;

};

}
#endif

//
// End of "$Id: Dial.h 4910 2006-04-06 19:26:22Z fabien $".
//
#endif
// ----- END -------------------------------------------------------------------
//
// End of "$Id$"
//
