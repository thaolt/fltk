//
// "$Id$"
//
// Hello, World! program for the Fast Light Tool Kit (FLTK).
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

#include <fltk3/run.h>
#include <fltk3/Window.h>
#include <fltk3/Box.h>

int main(int argc, char **argv) {
  Fl_Window *window = new Fl_Window(340,180);
  fltk3::Box *box = new fltk3::Box(20,40,300,100,"Hello, World!");
  box->box(fltk3::UP_BOX);
  box->labelfont(fltk3::BOLD+fltk3::ITALIC);
  box->labelsize(36);
  box->labeltype(fltk3::shadowLabel);
  window->end();
  window->show(argc, argv);
  return Fl::run();
}

//
// End of "$Id$".
//

