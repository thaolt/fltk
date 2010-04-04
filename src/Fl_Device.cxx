//
// "$Id$"
//
// implementation of fltk3::Device class for the Fast Light Tool Kit (FLTK).
//
// Copyright 2010 by Bill Spitzak and others.
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
// Please report all bugs and problems to:
//
//     http://www.fltk.org/str.php
//

#include <fltk3/run.h>
#include <fltk3/Device.h>
//#include <fltk3/draw.h>
#include <fltk3/Image.h>

/** \brief Draws an fltk3::RGBImage object to the device. 
 *
 Specifies a bounding box for the image, with the origin (upper left-hand corner) of 
 the image offset by the cx and cy arguments.
 */
void fltk3::Device::draw(Fl_Pixmap *pxm,int XP, int YP, int WP, int HP, int cx, int cy)
{
  pxm->draw(XP, YP, WP, HP, cx, cy);
}

/** \brief Draws an Fl_Bitmap object to the device. 
 *
 Specifies a bounding box for the image, with the origin (upper left-hand corner) of 
 the image offset by the cx and cy arguments.
 */
void fltk3::Device::draw(Fl_Bitmap *bm,int XP, int YP, int WP, int HP, int cx, int cy)
{
  bm->draw(XP, YP, WP, HP, cx, cy);
}

/** \brief Draws an Fl_Pixmap object to the device. 
 *
 Specifies a bounding box for the image, with the origin (upper left-hand corner) of 
 the image offset by the cx and cy arguments.
 */
void fltk3::Device::draw(fltk3::RGBImage *rgb,int XP, int YP, int WP, int HP, int cx, int cy)
{
  rgb->draw(XP, YP, WP, HP, cx, cy);
}

/**
 @brief Sets this device (display, printer, local file) as the target of future graphics calls.
 *
 @return  The current target device of graphics calls.
 */
fltk3::Device *fltk3::Device::set_current(void)
{
  fltk3::Device *current = fl_device;
  fl_device = this;
  return current;
}

/**
 @brief    Returns the current target device of graphics calls.
 */
fltk3::Device *fltk3::Device::current(void)
{
  return fl_device;
}

//
// End of "$Id$".
//
