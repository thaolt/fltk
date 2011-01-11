//
// "$Id$"
//
// Numericing point input header file for the Fast Light Tool Kit (FLTK).
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
   fltk3::NumericInput widget . */


#ifndef fltk3_NumericInput_H
#define fltk3_NumericInput_H

#include "Input.h"

namespace fltk3 {
  class NumericInput;
}

/**
  The fltk3::NumericInput class is a subclass of fltk3::Input
  that only allows the user to type floating point numbers (sign,
  digits, decimal point, more digits, 'E' or 'e', sign, digits).
*/
class fltk3::NumericInput : public fltk3::Input { // don't use FL_EXPORT here !
public:
  /**
      Creates a new fltk3::NumericInput widget using the given position,
    size, and label string. The default boxtype is fltk3::DOWN_BOX.
  <P> Inherited destructor destroys the widget and any value associated with it
  */
  NumericInput(int X,int Y,int W,int H,const char *l = 0)
    : fltk3::Input(X,Y,W,H,l) {type(FL_FLOAT_INPUT);}
};

#endif

//
// End of "$Id$".
//
