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
// This is the Twin Class to fltk::visual
class visual : public fltk::visual {
public:
  visual(int x, int t, int w, int h, const char *label=0)
  : fltk::visual(x, y, w, h, label), compat_(FLTK1) { }
};
*/

// ----- FLTK1 -----------------------------------------------------------------
#if 0
#endif
// ----- FLTK2 -----------------------------------------------------------------
#if 0
// "$Id: visual.h 6233 2008-09-14 07:54:06Z spitzak $"
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

#ifndef fltk_visual_h
#define fltk_visual_h

#include "FL_API.h"

namespace fltk {

/// \name fltk/visual.h
//@{

enum {
  RGB_COLOR	= 0,
  INDEXED_COLOR	= 1,
  SINGLE_BUFFER	= 0,
  DOUBLE_BUFFER	= 2,
  ACCUM_BUFFER	= 4,
  ALPHA_BUFFER	= 8,
  DEPTH_BUFFER	= 16,
  STENCIL_BUFFER= 32,
  RGB24_COLOR	= 64,
  MULTISAMPLE	= 128,
  STEREO	= 256
};

extern FL_API bool visual(int);

extern FL_GL_API bool glVisual(int);

extern FL_API void own_colormap();

//@}

}

#endif
#endif
// ----- END -------------------------------------------------------------------
//
// End of "$Id$"
//
