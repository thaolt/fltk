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
// "$Id: Fl_JPEG_Image.H 7092 2010-02-18 11:38:42Z matt $"
//
// JPEG image header file for the Fast Light Tool Kit (FLTK).
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
   Fl_JPEG_Image class . */

#ifndef Fl_JPEG_Image_H
#define Fl_JPEG_Image_H
#  include "Image.h"

/**
  The Fl_JPEG_Image class supports loading, caching,
  and drawing of Joint Photographic Experts Group (JPEG) File
  Interchange Format (JFIF) images. The class supports grayscale
  and color (RGB) JPEG image files.
*/
class FL_EXPORT Fl_JPEG_Image : public Fl_RGB_Image {

public:

  Fl_JPEG_Image(const char *filename);
  Fl_JPEG_Image(const char *name, const unsigned char *data);
};

#endif

//
// End of "$Id: Fl_JPEG_Image.H 7092 2010-02-18 11:38:42Z matt $".
//

/* suggested twin class
// This is the Twin Class to fltk::jpegImage
class Fl_JPEG_Image : public fltk::jpegImage {
public:
  Fl_JPEG_Image(int x, int t, int w, int h, const char *label=0)
  : fltk::jpegImage(x, y, w, h, label), compat_(FLTK1) { }
};
*/

// ----- FLTK1 -----------------------------------------------------------------
#if 0
//
// "$Id: Fl_JPEG_Image.H 7092 2010-02-18 11:38:42Z matt $"
//
// JPEG image header file for the Fast Light Tool Kit (FLTK).
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
   Fl_JPEG_Image class . */

#ifndef Fl_JPEG_Image_H
#define Fl_JPEG_Image_H
#  include "Fl_Image.H"

/**
  The Fl_JPEG_Image class supports loading, caching,
  and drawing of Joint Photographic Experts Group (JPEG) File
  Interchange Format (JFIF) images. The class supports grayscale
  and color (RGB) JPEG image files.
*/
class FL_EXPORT Fl_JPEG_Image : public Fl_RGB_Image {

public:

  Fl_JPEG_Image(const char *filename);
  Fl_JPEG_Image(const char *name, const unsigned char *data);
};

#endif

//
// End of "$Id: Fl_JPEG_Image.H 7092 2010-02-18 11:38:42Z matt $".
//
#endif
// ----- FLTK2 -----------------------------------------------------------------
#if 0
#endif
// ----- END -------------------------------------------------------------------
//
// End of "$Id$"
//
