/
// "$Id$
/
// Xlib color functions for the Fast Light Tool Kit (FLTK)
/
// Copyright 1998-2003 by Bill Spitzak and others
/
// This library is free software; you can redistribute it and/o
// modify it under the terms of the GNU Library General Publi
// License as published by the Free Software Foundation; eithe
// version 2 of the License, or (at your option) any later version
/
// This library is distributed in the hope that it will be useful
// but WITHOUT ANY WARRANTY; without even the implied warranty o
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GN
// Library General Public License for more details
/
// You should have received a copy of the GNU Library General Publi
// License along with this library; if not, write to the Free Softwar
// Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-130
// USA
/
// Please report all bugs and problems to "fltk-bugs@fltk.org"
/

// Implementation of color(i), color(r,g,b)


// Also code to look at the X visual and figure out the best way to tur
// a color into a pixel value

// SGI compiler seems to have problems with unsigned char argument
// being used to index arrays.  So I always copy them to an intege
// before use

#  include "../Fl_XColor.H
#  include <FL/Fl.H
#  include <FL/x.H
#  include <FL/fl_draw.H
#  include "Fl_Xlib_Display.H

///////////////////////////////////////////////////////////////
// figure_out_visual() calculates masks & shifts for generatin
// pixels in true-color visuals

uchar fl_redmask, fl_greenmask, fl_bluemask
int fl_redshift, fl_greenshift, fl_blueshift, fl_extrashift
static uchar beenhere

static void figure_out_visual() 
  beenhere = 1
  if (!fl_visual->red_mask || !fl_visual->green_mask || !fl_visual->blue_mask)
#  if USE_COLORMA
    fl_redmask = 0
    return
#  els
    Fl::fatal("Requires true color visual")
#  endi
  

  // get the bit masks into a more useful form
  int i,j,m

  for (i = 0, m = 1; m; i++, m<<=1) if (fl_visual->red_mask & m) break
  for (j = i; m; j++, m<<=1) if (!(fl_visual->red_mask & m)) break
  fl_redshift = j-8
  fl_redmask = (j-i >= 8) ? 0xFF : 0xFF-(255>>(j-i))

  for (i = 0, m = 1; m; i++, m<<=1) if (fl_visual->green_mask & m) break
  for (j = i; m; j++, m<<=1) if (!(fl_visual->green_mask & m)) break
  fl_greenshift = j-8
  fl_greenmask = (j-i >= 8) ? 0xFF : 0xFF-(255>>(j-i))

  for (i = 0, m = 1; m; i++, m<<=1) if (fl_visual->blue_mask & m) break
  for (j = i; m; j++, m<<=1) if (!(fl_visual->blue_mask & m)) break
  fl_blueshift = j-8
  fl_bluemask = (j-i >= 8) ? 0xFF : 0xFF-(255>>(j-i))

  i = fl_redshift
  if (fl_greenshift < i) i = fl_greenshift
  if (fl_blueshift < i) i = fl_blueshift
  if (i < 0) 
    fl_extrashift = -i
    fl_redshift -= i; fl_greenshift -= i; fl_blueshift -= i
  } els
    fl_extrashift = 0




#  if HAVE_OVERLA
Fl_XColor fl_xmap[2][256]
uchar fl_overlay
Colormap fl_overlay_colormap
XVisualInfo* fl_overlay_visual
ulong fl_transparent_pixel
#  els
Fl_XColor fl_xmap[1][256]
#    define fl_overlay 
#  endi

///////////////////////////////////////////////////////////////
// Get an rgb color.  This is easy for a truecolor visual.  Fo
// colormapped it picks the closest color out of the cube in th
// fltk colormap.  However if this color cube entry has bee
// requested before, you will get the earlier requested color, an
// even this may be approximated if the X colormap was full

ulong fl_xpixel(uchar r,uchar g,uchar b) 
  if (!beenhere) figure_out_visual()
#  if USE_COLORMA
  if (!fl_redmask) 
    // find closest entry in the colormap
    Fl_Color i 
      fl_color_cube(r*FL_NUM_RED/256,g*FL_NUM_GREEN/256,b*FL_NUM_BLUE/256)
    Fl_XColor &xmap = fl_xmap[fl_overlay][i]
    if (xmap.mapped) return xmap.pixel
    // if not black or white, change the entry to be an exact match
    if (i != FL_COLOR_CUBE && i != 0xFF
      fl_cmap[i] = (r<<24)|(g<<16)|(b<<8)
    return fl_xpixel(i); // allocate an X colo
  
#  endi
  retur
    (((r&fl_redmask) << fl_redshift)
     ((g&fl_greenmask)<<fl_greenshift)
     ((b&fl_bluemask)<< fl_blueshift
     ) >> fl_extrashift


void Fl_Xlib_Display::color(uchar r,uchar g,uchar b) 
  fl_color_ = fl_rgb_color(r, g, b)
  XSetForeground(fl_display, fl_gc, fl_xpixel(r,g,b))


///////////////////////////////////////////////////////////////
// Get a color out of the the fltk colormap.  Again for truecolo
// visuals this is easy.  For colormap this actually tries to allocat
// an X color, and does a least-squares match to find the closes
// color if X cannot allocate that color

// calculate what color is actually on the screen for a mask
static inline uchar realcolor(uchar color, uchar mask) 
#  if 
  // accurate version if the display has linear gamma, but fl_draw_imag
  // works better with the simpler version on most screens..
  uchar m = mask
  uchar result = color&m
  for (;;) 
    while (m&mask) {m>>=1; color>>=1;
    if (!m) break
    mask = m
    result |= color&m
  
  return result
#  els
  return (color&mask) | (~mask)&(mask>>1)
#  endi


ulong fl_xpixel(Fl_Color i) 
  if (i & 0xffffff00) 
    return fl_xpixel((i >> 24) & 255, (i >> 16) & 255, (i >> 8) & 255)
  

  Fl_XColor &xmap = fl_xmap[fl_overlay][i]
  if (xmap.mapped) return xmap.pixel

  if (!beenhere) figure_out_visual()

  uchar r,g,b
  {unsigned c = fl_cmap[i]; r=uchar(c>>24); g=uchar(c>>16); b=uchar(c>>8);

#  if USE_COLORMA
  Colormap colormap = fl_colormap
#    if HAVE_OVERLA
  if (fl_overlay) colormap = fl_overlay_colormap; els
#    endi
  if (fl_redmask) 
#  endi
    // return color for a truecolor visual
    xmap.mapped = 2; // 2 prevents XFreeColor from being calle
    xmap.r = realcolor(r, fl_redmask)
    xmap.g = realcolor(g, fl_greenmask)
    xmap.b = realcolor(b, fl_bluemask)
    return xmap.pixel =
      (((r&fl_redmask) << fl_redshift)
       ((g&fl_greenmask)<<fl_greenshift)
       ((b&fl_bluemask)<< fl_blueshift
       ) >> fl_extrashift
#  if USE_COLORMA
  
#    if HAVE_OVERLA
  static XColor* ac[2]
  XColor*& allcolors = ac[fl_overlay]
  static int nc[2]
  int& numcolors = nc[fl_overlay]
#    els
  static XColor *allcolors
  static int numcolors
#    endi

  // I don't try to allocate colors with XAllocColor once it fail
  // with any color.  It is possible that it will work, since a colo
  // may have been freed, but some servers are extremely slow and thi
  // avoids one round trip
  if (!numcolors) { // don't try after a failur
    XColor xcol
    xcol.red = r<<8; xcol.green = g<<8; xcol.blue = b<<8
    if (XAllocColor(fl_display, colormap, &xcol)) 
      xmap.mapped = 1
      xmap.r = xcol.red>>8
      xmap.g = xcol.green>>8
      xmap.b = xcol.blue>>8
      return xmap.pixel = xcol.pixel
    

    // I only read the colormap once.  Again this is due to the slownes
    // of round-trips to the X server, even though other programs may alte
    // the colormap after this and make decisions here wrong
#    if HAVE_OVERLA
    if (fl_overlay) numcolors = fl_overlay_visual->colormap_size; els
#    endi
      numcolors = fl_visual->colormap_size
    if (!allcolors) allcolors = new XColor[numcolors]
    for (int p = numcolors; p--;) allcolors[p].pixel = p
    XQueryColors(fl_display, colormap, allcolors, numcolors)
  

  // find least-squares match
  int mindist = 0x7FFFFFFF
  unsigned int bestmatch = 0
  for (unsigned int n = numcolors; n--;) 
#    if HAVE_OVERLA
    if (fl_overlay && n == fl_transparent_pixel) continue
#    endi
    XColor &a = allcolors[n]
    int d, t
    t = int(r)-int(a.red>>8); d = t*t
    t = int(g)-int(a.green>>8); d += t*t
    t = int(b)-int(a.blue>>8); d += t*t
    if (d <= mindist) {bestmatch = n; mindist = d;
  
  XColor &p = allcolors[bestmatch]

  // It appears to "work" to not call this XAllocColor, which wil
  // avoid another round-trip to the server.  But then X does no
  // know that this program "owns" this value, and can (and will
  // change it when the program that did allocate it exits
  if (XAllocColor(fl_display, colormap, &p)) 
    xmap.mapped = 1
    xmap.pixel = p.pixel
  } else 
    // However, if that XAllocColor fails, I have to give up an
    // assumme the pixel is ok for the duration of the program.  Thi
    // is due to bugs (?) in the Solaris X and some X terminal
    // where XAllocColor *always* fails when the colormap is full
    // even if we ask for a color already in it..
    xmap.mapped = 2; // 2 prevents XFreeColor from being calle
    xmap.pixel = bestmatch
  
  xmap.r = p.red>>8
  xmap.g = p.green>>8
  xmap.b = p.blue>>8
  return xmap.pixel
#  endi


Fl_Color fl_color_

void Fl_Xlib_Display::color(Fl_Color i) 
  if (i & 0xffffff00) 
    unsigned rgb = (unsigned)i
    fl_color((uchar)(rgb >> 24), (uchar)(rgb >> 16), (uchar)(rgb >> 8))
  } else 
    fl_color_ = i
    XSetForeground(fl_display, fl_gc, fl_xpixel(i))
  


void Fl::free_color(Fl_Color i, int overlay) 
#  if HAVE_OVERLA
#  els
  if (overlay) return
#  endi
  if (fl_xmap[overlay][i].mapped) 
#  if USE_COLORMA
#    if HAVE_OVERLA
    Colormap colormap = overlay ? fl_overlay_colormap : fl_colormap
#    els
    Colormap colormap = fl_colormap
#    endi
    if (fl_xmap[overlay][i].mapped == 1
      XFreeColors(fl_display, colormap, &(fl_xmap[overlay][i].pixel), 1, 0)
#  endi
    fl_xmap[overlay][i].mapped = 0
  


void Fl::set_color(Fl_Color i, unsigned c) 
  if (fl_cmap[i] != c) 
    free_color(i,0)
#  if HAVE_OVERLA
    free_color(i,1)
#  endi
    fl_cmap[i] = c
  



/
// End of "$Id$"
/
