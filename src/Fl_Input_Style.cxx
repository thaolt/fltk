//
// "$Id: Fl_Input_Style.cxx,v 1.5 1999/11/05 21:43:51 carl Exp $"
//
// Style of Fl_Input for the Fast Light Tool Kit (FLTK).
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

// The style is defined in a separate file so that the rest of Fl_Input
// does not get always linked in ...

#include <FL/Fl_Input.H>

// Fl_Input, the box, color, and selection color are different:

Fl_Style Fl_Input::default_style;

static void revert(Fl_Style* s) {
  s->box = FL_THIN_DOWN_BOX;
  s->color = FL_WHITE;
  s->selection_color = FL_BLUE_SELECTION_COLOR;
  s->selection_text_color = FL_WHITE;
  s->off_color = FL_BLACK;
}

static Fl_Style_Definer x("input", Fl_Input::default_style, revert);

//
// End of "$Id: Fl_Input_Style.cxx,v 1.5 1999/11/05 21:43:51 carl Exp $".
//
