//
// "$Id$"
//
// Keyboard state routines for the Fast Light Tool Kit (FLTK).
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

#include <config.h>

#ifdef USE_X11

// Return the current state of a key.  This is the X version.  I identify
// keys (mostly) by the X keysym.  So this turns the keysym into a keycode
// and looks it up in the X key bit vector, which Fl_x.cxx keeps track of.

#  include <fltk3/run.h>
#  include <fltk3/x.h>

extern char fl_key_vector[32]; // in Fl_x.cxx

int fltk3::event_key(unsigned int k) {
  if (k > fltk3::MouseButton && k <= fltk3::MouseButton+8)
    return fltk3::event_state(8<<(k-fltk3::MouseButton));
  int i;
#  ifdef __sgi
  // get some missing PC keyboard keys:
  if (k == fltk3::MetaLKey) i = 147;
  else if (k == fltk3::MetaRKey) i = 148;
  else if (k == fltk3::MenuKey) i = 149;
  else
#  endif
    i = XKeysymToKeycode(fl_display, k);
  if (i==0) return 0;
  return fl_key_vector[i/8] & (1 << (i%8));
}

int fltk3::get_key(unsigned int k) {
  fl_open_display();
  XQueryKeymap(fl_display, fl_key_vector);
  return event_key(k);
}

#endif

//
// End of "$Id$".
//