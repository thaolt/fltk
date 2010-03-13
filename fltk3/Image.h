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
// "$Id: Fl_Image.H 6614 2009-01-01 16:11:32Z matt $"
//
// Image header file for the Fast Light Tool Kit (FLTK).
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
   Fl_Image, Fl_RGB_Image classes . */

#ifndef Fl_Image_H
#  define Fl_Image_H

#  include "Enumerations.H"

class Fl_Widget;
struct Fl_Menu_Item;
struct Fl_Label;

/**
  Fl_Image is the base class used for caching and
  drawing all kinds of images in FLTK. This class keeps track of
  common image data such as the pixels, colormap, width, height,
  and depth. Virtual methods are used to provide type-specific
  image handling.</P>
  
  <P>Since the Fl_Image class does not support image
  drawing by itself, calling the draw() method results in
  a box with an X in it being drawn instead.
*/
class FL_EXPORT Fl_Image {
  int w_, h_, d_, ld_, count_;
  const char * const *data_;

  // Forbid use of copy contructor and assign operator
  Fl_Image & operator=(const Fl_Image &);
  Fl_Image(const Fl_Image &);

  protected:

  /**
    The first form of the w() method returns the current
    image width in pixels.</P>
    
    <P>The second form is a protected method that sets the current
    image width.
  */
  void w(int W) {w_ = W;}
  /**
    The first form of the h() method returns the current
    image height in pixels.</P>
    
    <P>The second form is a protected method that sets the current
    image height.
  */
  void h(int H) {h_ = H;}
  /**
    The first form of the d() method returns the current
    image depth. The return value will be 0 for bitmaps, 1 for
    pixmaps, and 1 to 4 for color images.</P>
    
    <P>The second form is a protected method that sets the current
    image depth.
  */
  void d(int D) {d_ = D;}
  /**    See int ld()  */
  void ld(int LD) {ld_ = LD;}
  /**    See const char * const *data()  */
  void data(const char * const *p, int c) {data_ = p; count_ = c;}
  void draw_empty(int X, int Y);

  static void labeltype(const Fl_Label *lo, int lx, int ly, int lw, int lh, Fl_Align la);
  static void measure(const Fl_Label *lo, int &lw, int &lh);

  public:

  /** See void Fl_Image::w(int) */
  int w() const {return w_;}
  /** See void Fl_Image::h(int) */
  int h() const {return h_;}
  /**
    The first form of the d() method returns the current
    image depth. The return value will be 0 for bitmaps, 1 for
    pixmaps, and 1 to 4 for color images.</P>
    
    <P>The second form is a protected method that sets the current
    image depth.
  */
  int d() const {return d_;}
  /**
    The first form of the ld() method returns the current
    line data size in bytes. Line data is extra data that is included
    after each line of color image data and is normally not present.</P>
    
    <P>The second form is a protected method that sets the current
    line data size in bytes.
  */
  int ld() const {return ld_;}
  /**
    The count() method returns the number of data values
    associated with the image. The value will be 0 for images with
    no associated data, 1 for bitmap and color images, and greater
    than 2 for pixmap images.
  */
  int count() const {return count_;}
  /**
    The first form of the data() method returns a
    pointer to the current image data array. Use the
    count() method to find the size of the data array.</P>
    
    <P>The second form is a protected method that sets the current
    array pointer and count of pointers in the array.
  */
  const char * const *data() const {return data_;}
  
  /**
    The constructor creates an empty image with the specified
    width, height, and depth. The width and height are in pixels.
    The depth is 0 for bitmaps, 1 for pixmap (colormap) images, and
    1 to 4 for color images.
  */
  Fl_Image(int W, int H, int D) {w_ = W; h_ = H; d_ = D; ld_ = 0; count_ = 0; data_ = 0;}
  virtual ~Fl_Image();
  virtual Fl_Image *copy(int W, int H);
  /**
    The copy() method creates a copy of the specified
    image. If the width and height are provided, the image is
    resized to the specified size. The image should be deleted (or in
    the case of Fl_Shared_Image, released) when you are done
    with it.
  */
  Fl_Image *copy() { return copy(w(), h()); }
  virtual void color_average(Fl_Color c, float i);
  /**
    The inactive() method calls
    color_average(FL_BACKGROUND_COLOR, 0.33f) to produce 
    an image that appears grayed out. <I>This method does not 
    alter the original image data.</I>
  */
  void inactive() { color_average(FL_GRAY, .33f); }
  virtual void desaturate();
  virtual void label(Fl_Widget*w);
  virtual void label(Fl_Menu_Item*m);
  /**
    The draw() methods draw the image. This form specifies
    a bounding box for the image, with the origin
    (upper-lefthand corner) of the image offset by the cx
    and cy arguments.
  */
  virtual void draw(int X, int Y, int W, int H, int cx=0, int cy=0); // platform dependent
  /**
    The draw() methods draw the image. This form
    specifies the upper-lefthand corner of the image
  */
  void draw(int X, int Y) {draw(X, Y, w(), h(), 0, 0);} // platform dependent
  virtual void uncache();
};

/**
  The Fl_RGB_Image class supports caching and drawing
  of full-color images with 1 to 4 channels of color information.
  Images with an even number of channels are assumed to contain
  alpha information, which is used to blend the image with the
  contents of the screen.</P>
  
  <P>Fl_RGB_Image is defined in
  &lt;FL/Fl_Image.H&gt;, however for compatibility reasons
  &lt;FL/Fl_RGB_Image.H&gt; should be included.
*/
class FL_EXPORT Fl_RGB_Image : public Fl_Image {
  public:

  const uchar *array;
  int alloc_array; // Non-zero if array was allocated

#if defined(__APPLE__) || defined(WIN32)
  void *id; // for internal use
  void *mask; // for internal use (mask bitmap)
#else
  unsigned id; // for internal use
  unsigned mask; // for internal use (mask bitmap)
#endif // __APPLE__ || WIN32
/**  The constructor creates a new image from the specified data. */
  Fl_RGB_Image(const uchar *bits, int W, int H, int D=3, int LD=0) :
    Fl_Image(W,H,D), array(bits), alloc_array(0), id(0), mask(0) {data((const char **)&array, 1); ld(LD);}
  virtual ~Fl_RGB_Image();
  virtual Fl_Image *copy(int W, int H);
  Fl_Image *copy() { return copy(w(), h()); }
  virtual void color_average(Fl_Color c, float i);
  virtual void desaturate();
  virtual void draw(int X, int Y, int W, int H, int cx=0, int cy=0);
  void draw(int X, int Y) {draw(X, Y, w(), h(), 0, 0);}
  virtual void label(Fl_Widget*w);
  virtual void label(Fl_Menu_Item*m);
  virtual void uncache();
};

#endif // !Fl_Image_H

//
// End of "$Id: Fl_Image.H 6614 2009-01-01 16:11:32Z matt $".
//

/* suggested twin class
// This is the Twin Class to fltk::Image
class Fl_Image : public fltk::Image {
public:
  Fl_Image(int x, int t, int w, int h, const char *label=0)
  : fltk::Image(x, y, w, h, label), compat_(FLTK1) { }
};
*/

// ----- FLTK1 -----------------------------------------------------------------
#if 0
//
// "$Id: Fl_Image.H 6614 2009-01-01 16:11:32Z matt $"
//
// Image header file for the Fast Light Tool Kit (FLTK).
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
   Fl_Image, Fl_RGB_Image classes . */

#ifndef Fl_Image_H
#  define Fl_Image_H

#  include "Enumerations.H"

class Fl_Widget;
struct Fl_Menu_Item;
struct Fl_Label;

/**
  Fl_Image is the base class used for caching and
  drawing all kinds of images in FLTK. This class keeps track of
  common image data such as the pixels, colormap, width, height,
  and depth. Virtual methods are used to provide type-specific
  image handling.</P>
  
  <P>Since the Fl_Image class does not support image
  drawing by itself, calling the draw() method results in
  a box with an X in it being drawn instead.
*/
class FL_EXPORT Fl_Image {
  int w_, h_, d_, ld_, count_;
  const char * const *data_;

  // Forbid use of copy contructor and assign operator
  Fl_Image & operator=(const Fl_Image &);
  Fl_Image(const Fl_Image &);

  protected:

  /**
    The first form of the w() method returns the current
    image width in pixels.</P>
    
    <P>The second form is a protected method that sets the current
    image width.
  */
  void w(int W) {w_ = W;}
  /**
    The first form of the h() method returns the current
    image height in pixels.</P>
    
    <P>The second form is a protected method that sets the current
    image height.
  */
  void h(int H) {h_ = H;}
  /**
    The first form of the d() method returns the current
    image depth. The return value will be 0 for bitmaps, 1 for
    pixmaps, and 1 to 4 for color images.</P>
    
    <P>The second form is a protected method that sets the current
    image depth.
  */
  void d(int D) {d_ = D;}
  /**    See int ld()  */
  void ld(int LD) {ld_ = LD;}
  /**    See const char * const *data()  */
  void data(const char * const *p, int c) {data_ = p; count_ = c;}
  void draw_empty(int X, int Y);

  static void labeltype(const Fl_Label *lo, int lx, int ly, int lw, int lh, Fl_Align la);
  static void measure(const Fl_Label *lo, int &lw, int &lh);

  public:

  /** See void Fl_Image::w(int) */
  int w() const {return w_;}
  /** See void Fl_Image::h(int) */
  int h() const {return h_;}
  /**
    The first form of the d() method returns the current
    image depth. The return value will be 0 for bitmaps, 1 for
    pixmaps, and 1 to 4 for color images.</P>
    
    <P>The second form is a protected method that sets the current
    image depth.
  */
  int d() const {return d_;}
  /**
    The first form of the ld() method returns the current
    line data size in bytes. Line data is extra data that is included
    after each line of color image data and is normally not present.</P>
    
    <P>The second form is a protected method that sets the current
    line data size in bytes.
  */
  int ld() const {return ld_;}
  /**
    The count() method returns the number of data values
    associated with the image. The value will be 0 for images with
    no associated data, 1 for bitmap and color images, and greater
    than 2 for pixmap images.
  */
  int count() const {return count_;}
  /**
    The first form of the data() method returns a
    pointer to the current image data array. Use the
    count() method to find the size of the data array.</P>
    
    <P>The second form is a protected method that sets the current
    array pointer and count of pointers in the array.
  */
  const char * const *data() const {return data_;}
  
  /**
    The constructor creates an empty image with the specified
    width, height, and depth. The width and height are in pixels.
    The depth is 0 for bitmaps, 1 for pixmap (colormap) images, and
    1 to 4 for color images.
  */
  Fl_Image(int W, int H, int D) {w_ = W; h_ = H; d_ = D; ld_ = 0; count_ = 0; data_ = 0;}
  virtual ~Fl_Image();
  virtual Fl_Image *copy(int W, int H);
  /**
    The copy() method creates a copy of the specified
    image. If the width and height are provided, the image is
    resized to the specified size. The image should be deleted (or in
    the case of Fl_Shared_Image, released) when you are done
    with it.
  */
  Fl_Image *copy() { return copy(w(), h()); }
  virtual void color_average(Fl_Color c, float i);
  /**
    The inactive() method calls
    color_average(FL_BACKGROUND_COLOR, 0.33f) to produce 
    an image that appears grayed out. <I>This method does not 
    alter the original image data.</I>
  */
  void inactive() { color_average(FL_GRAY, .33f); }
  virtual void desaturate();
  virtual void label(Fl_Widget*w);
  virtual void label(Fl_Menu_Item*m);
  /**
    The draw() methods draw the image. This form specifies
    a bounding box for the image, with the origin
    (upper-lefthand corner) of the image offset by the cx
    and cy arguments.
  */
  virtual void draw(int X, int Y, int W, int H, int cx=0, int cy=0); // platform dependent
  /**
    The draw() methods draw the image. This form
    specifies the upper-lefthand corner of the image
  */
  void draw(int X, int Y) {draw(X, Y, w(), h(), 0, 0);} // platform dependent
  virtual void uncache();
};

/**
  The Fl_RGB_Image class supports caching and drawing
  of full-color images with 1 to 4 channels of color information.
  Images with an even number of channels are assumed to contain
  alpha information, which is used to blend the image with the
  contents of the screen.</P>
  
  <P>Fl_RGB_Image is defined in
  &lt;FL/Fl_Image.H&gt;, however for compatibility reasons
  &lt;FL/Fl_RGB_Image.H&gt; should be included.
*/
class FL_EXPORT Fl_RGB_Image : public Fl_Image {
  public:

  const uchar *array;
  int alloc_array; // Non-zero if array was allocated

#if defined(__APPLE__) || defined(WIN32)
  void *id; // for internal use
  void *mask; // for internal use (mask bitmap)
#else
  unsigned id; // for internal use
  unsigned mask; // for internal use (mask bitmap)
#endif // __APPLE__ || WIN32
/**  The constructor creates a new image from the specified data. */
  Fl_RGB_Image(const uchar *bits, int W, int H, int D=3, int LD=0) :
    Fl_Image(W,H,D), array(bits), alloc_array(0), id(0), mask(0) {data((const char **)&array, 1); ld(LD);}
  virtual ~Fl_RGB_Image();
  virtual Fl_Image *copy(int W, int H);
  Fl_Image *copy() { return copy(w(), h()); }
  virtual void color_average(Fl_Color c, float i);
  virtual void desaturate();
  virtual void draw(int X, int Y, int W, int H, int cx=0, int cy=0);
  void draw(int X, int Y) {draw(X, Y, w(), h(), 0, 0);}
  virtual void label(Fl_Widget*w);
  virtual void label(Fl_Menu_Item*m);
  virtual void uncache();
};

#endif // !Fl_Image_H

//
// End of "$Id: Fl_Image.H 6614 2009-01-01 16:11:32Z matt $".
//
#endif
// ----- FLTK2 -----------------------------------------------------------------
#if 0
// "$Id: Image.h 5768 2007-04-08 19:58:56Z spitzak $"
//
// Copyright 1998-2005 by Bill Spitzak and others.
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

#ifndef fltk_Image_h
#define fltk_Image_h

#include "Symbol.h"
# undef OPAQUE // fix for windows.h

namespace fltk {

class FL_API Widget;
struct Picture; // secret internal system-specific data

class FL_API Image : public Symbol {

  PixelType pixeltype_; int w_, h_;
  Picture* picture;
  int flags; enum {COPIED=1, FETCHED=2, FORCEARGB32=4, MEASUREFETCH=8};

  static unsigned long memused_;

public:

  Image(const char* name=0) :
    Symbol(name), pixeltype_(fltk::RGB32), w_(12), h_(12),
    picture(0), flags(MEASUREFETCH) {}
  Image(int w, int h, const char* name=0) :
    Symbol(name), pixeltype_(fltk::RGB32), w_(w), h_(h),
    picture(0), flags(0) {}
  Image(PixelType p, int w, int h, const char* name=0) :
    Symbol(name), pixeltype_(p), w_(w), h_(h),
    picture(0), flags(0) {}
  Image(const uchar* d, PixelType p, int w, int h) :
    Symbol(), picture(0) {setimage(d,p,w,h);}
  Image(const uchar* d, PixelType p, int w, int h, int linedelta) :
    Symbol(), picture(0) {setimage(d,p,w,h,linedelta);}
  ~Image();

  PixelType pixeltype() const {return pixeltype_;}
  int depth() const {return fltk::depth(pixeltype_);}
  int w() const {return w_;}
  int width() const {return w_;}
  int h() const {return h_;}
  int height() const {return h_;}

  void setpixeltype(PixelType);
  void setsize(int w, int h);
  void setpixels(const uchar* d, const Rectangle&, int linedelta);
  void setpixels(const uchar* d, const Rectangle& r) {setpixels(d,r,depth()*r.w());}
  void setpixels(const uchar* d, int y);
  uchar* linebuffer(int y);

  void setimage(const uchar* d, PixelType p, int w, int h, int linedelta);
  void setimage(const uchar* d, PixelType p, int w, int h) {setimage(d,p,w,h,fltk::depth(p)*w);}

  uchar* buffer();
  const uchar* buffer() const;
  void set_forceARGB32();
  void clear_forceARGB32();
  bool forceARGB32() const {return (flags&FORCEARGB32) != 0;}
  PixelType buffer_pixeltype() const;
  int buffer_depth() const;
  int buffer_width() const;
  int buffer_height() const;
  int buffer_linedelta() const;
  void buffer_changed() {flags &= ~COPIED;}
  void destroy();

  void draw(int x, int y) const;
  void draw(const Rectangle& r) const {_draw(r);}
  void draw(const Rectangle& from, const Rectangle& to) const;

  void _draw(const Rectangle&) const; // Symbol virtual method
  void _measure(int& W, int& H) const; // Symbol virtual method
  bool fills_rectangle() const; // Symbol virtual method
  virtual bool fetch(); // for image file reading subclasses
  void fetch_if_needed() const;
  void refetch() {flags &= ~FETCHED;}

  unsigned long mem_used() const;
  static unsigned long total_mem_used() {return memused_;}

  // for back compatability with fltk1 only:
  void label(Widget* o);

  // see also: GSave
  void make_current();

};

}

#endif

//
// End of "$Id: Image.h 5768 2007-04-08 19:58:56Z spitzak $".
//
#endif
// ----- END -------------------------------------------------------------------
//
// End of "$Id$"
//
