//
// "$Id: Fl_Return_Button.h,v 1.2 2002/10/29 00:37:23 easysw Exp $"
//
// Return button header file for the Fast Light Tool Kit (FLTK).
//
// Copyright 1998-1999 by Bill Spitzak and others.
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
// Please report all bugs and problems to "fltk-bugs@easysw.com".
//

#ifndef Fl_Return_Button_H
#define Fl_Return_Button_H
#include "Fl_Button.h"

/**

   The Fl_Return_Button is a subclass of Fl_Button that generates 
   a callback when it is pressed or when the user presses the Enter
   key. A carriage-return symbol is drawn next to the button label.
   
   \image Fl_Return_Button.gif

*/
class FL_API Fl_Return_Button : public Fl_Button {
public:
  /**
   Creates a new Fl_Return_Button widget using the given position, 
   size, and label string. The default boxtype is FL_UP_BOX . 
  */
  Fl_Return_Button(int x,int y,int w,int h,const char *l=0);
  static Fl_Named_Style* default_style;
protected:
  void draw();
};

#endif

//
// End of "$Id: Fl_Return_Button.h,v 1.2 2002/10/29 00:37:23 easysw Exp $".
//
