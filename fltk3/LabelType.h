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


/* suggested twin class
// This is the Twin Class to fltk::LabelType
class Fl_Label_Type : public fltk::LabelType {
public:
  Fl_Label_Type(int x, int t, int w, int h, const char *label=0)
  : fltk::LabelType(x, y, w, h, label), compat_(FLTK1) { }
};
*/

// ----- FLTK1 -----------------------------------------------------------------
#if 0
#endif
// ----- FLTK2 -----------------------------------------------------------------
#if 0
//
// "$Id: LabelType.h 5770 2007-04-10 10:42:07Z spitzak $"
//
// A LabelType determines how to draw the text of the label. This
// is not used very much, it can be used to draw engraved or shadowed
// labels. You could also put in code that interprets the text of
// the label and draws anything you want with it.
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

#ifndef fltk_LabelType_h
#define fltk_LabelType_h

#include "Flags.h"
#include "Rectangle.h"

namespace fltk {

class Style;

class FL_API LabelType {
public:
  virtual void draw(const char*, const Rectangle&, Flags) const;
  const char* name;
  LabelType* next;
  static LabelType* first;
  LabelType(const char* n) : name(n), next(first) {first = this;}
  static LabelType* find(const char* name);
  virtual ~LabelType(); // virtual to shut up C++ warnings
};

// You can use this to draw overlapping patterns
class FL_API EngravedLabel : public LabelType {
  const int* data;
public:
  void draw(const char*, const Rectangle&, Flags) const;
  EngravedLabel(const char * n, const int p[][3])
    : LabelType(n), data((const int*)p) {}
};

}

#endif
#endif
// ----- END -------------------------------------------------------------------
//
// End of "$Id$"
//
