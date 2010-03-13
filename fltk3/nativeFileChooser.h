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
// "$Id: Fl_Native_File_Chooser.H 7003 2010-01-14 20:47:59Z greg.ercolano $"
//
// FLTK native OS file chooser widget
//
// Copyright 1998-2009 by Bill Spitzak and others.
// Copyright 2004 Greg Ercolano.
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

#ifndef FL_NATIVE_FILE_CHOOSER_H
#define FL_NATIVE_FILE_CHOOSER_H

// Use Windows' chooser
#ifdef WIN32
#include <FL/Fl_Native_File_Chooser_WIN32.H>
#endif

// Use Apple's chooser
#ifdef __APPLE__
#include <FL/Fl_Native_File_Chooser_MAC.H>
#endif

// All else falls back to FLTK's own chooser
#if ! defined(__APPLE__) && !defined(WIN32)
#include <FL/Fl_Native_File_Chooser_FLTK.H>
#endif

#endif /*FL_NATIVE_FILE_CHOOSER_H*/

//
// End of "$Id: Fl_Native_File_Chooser.H 7003 2010-01-14 20:47:59Z greg.ercolano $".
//

/* suggested twin class
// This is the Twin Class to fltk::nativeFileChooser
class Fl_Native_File_Chooser : public fltk::nativeFileChooser {
public:
  Fl_Native_File_Chooser(int x, int t, int w, int h, const char *label=0)
  : fltk::nativeFileChooser(x, y, w, h, label), compat_(FLTK1) { }
};
*/

// ----- FLTK1 -----------------------------------------------------------------
#if 0
//
// "$Id: Fl_Native_File_Chooser.H 7003 2010-01-14 20:47:59Z greg.ercolano $"
//
// FLTK native OS file chooser widget
//
// Copyright 1998-2009 by Bill Spitzak and others.
// Copyright 2004 Greg Ercolano.
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

#ifndef FL_NATIVE_FILE_CHOOSER_H
#define FL_NATIVE_FILE_CHOOSER_H

// Use Windows' chooser
#ifdef WIN32
#include <FL/Fl_Native_File_Chooser_WIN32.H>
#endif

// Use Apple's chooser
#ifdef __APPLE__
#include <FL/Fl_Native_File_Chooser_MAC.H>
#endif

// All else falls back to FLTK's own chooser
#if ! defined(__APPLE__) && !defined(WIN32)
#include <FL/Fl_Native_File_Chooser_FLTK.H>
#endif

#endif /*FL_NATIVE_FILE_CHOOSER_H*/

//
// End of "$Id: Fl_Native_File_Chooser.H 7003 2010-01-14 20:47:59Z greg.ercolano $".
//
#endif
// ----- FLTK2 -----------------------------------------------------------------
#if 0
#endif
// ----- END -------------------------------------------------------------------
//
// End of "$Id$"
//
