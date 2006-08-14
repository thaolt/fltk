//
// "$Id: draw.d 4975 2006-04-18 13:07:42Z matt $"
//
// Portable drawing function header file for the Fast Light Tool Kit (FLTK).
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
// Please report all bugs and problems on the following page:
//
//     http://www.fltk.org/str.php
//

module fl.draw;

public import fl.enumerations;
public import fl.rect;
public import fl.color_mac;
public import fl.font;
public import fl.line_style;
public import fl.boxtype;
public import fl.font_mac;
public import fl.image;
public import fl.draw;
public import fl.vertex;
public import fl.arc;

private import std.stdio;
private import std.string;
private import std.c.string;
private import std.c.math;

// Label flags...
byte fl_draw_shortcut;

/+-
// Colors:
FL_EXPORT void	fl_color(Fl_Color); // select indexed color
inline void fl_color(int c) {fl_color((Fl_Color)c);} // for back compatability
FL_EXPORT void	fl_color(uchar, uchar, uchar); // select actual color
extern FL_EXPORT Fl_Color fl_color_;
inline Fl_Color fl_color() {return fl_color_;}

// clip:
FL_EXPORT void fl_push_clip(int x, int y, int w, int h);
#define fl_clip fl_push_clip
FL_EXPORT void fl_push_no_clip();
FL_EXPORT void fl_pop_clip();
FL_EXPORT int fl_not_clipped(int x, int y, int w, int h);
FL_EXPORT int fl_clip_box(int, int, int, int, int& x, int& y, int& w, int& h);

// points:
FL_EXPORT void fl_point(int x, int y);

// line type:
FL_EXPORT void fl_line_style(int style, int width=0, char* dashes=0);
-+/
enum {
  FL_SOLID	= 0,
  FL_DASH	= 1,
  FL_DOT	= 2,
  FL_DASHDOT	= 3,
  FL_DASHDOTDOT	= 4,

  FL_CAP_FLAT	= 0x100,
  FL_CAP_ROUND	= 0x200,
  FL_CAP_SQUARE	= 0x300,

  FL_JOIN_MITER	= 0x1000,
  FL_JOIN_ROUND	= 0x2000,
  FL_JOIN_BEVEL	= 0x3000
};
/+-
// rectangles tweaked to exactly fill the pixel rectangle:
FL_EXPORT void fl_rect(int x, int y, int w, int h);
inline void fl_rect(int x, int y, int w, int h, Fl_Color c) {fl_color(c); fl_rect(x,y,w,h);}
FL_EXPORT void fl_rectf(int x, int y, int w, int h);
inline void fl_rectf(int x, int y, int w, int h, Fl_Color c) {fl_color(c); fl_rectf(x,y,w,h);}

// line segments:
FL_EXPORT void fl_line(int,int, int,int);
FL_EXPORT void fl_line(int,int, int,int, int,int);

// closed line segments:
FL_EXPORT void fl_loop(int,int, int,int, int,int);
FL_EXPORT void fl_loop(int,int, int,int, int,int, int,int);

// filled polygons
FL_EXPORT void fl_polygon(int,int, int,int, int,int);
FL_EXPORT void fl_polygon(int,int, int,int, int,int, int,int);

// draw rectilinear lines, horizontal segment first:
FL_EXPORT void fl_xyline(int x, int y, int x1);
FL_EXPORT void fl_xyline(int x, int y, int x1, int y2);
FL_EXPORT void fl_xyline(int x, int y, int x1, int y2, int x3);

// draw rectilinear lines, vertical segment first:
FL_EXPORT void fl_yxline(int x, int y, int y1);
FL_EXPORT void fl_yxline(int x, int y, int y1, int x2);
FL_EXPORT void fl_yxline(int x, int y, int y1, int x2, int y3);

// circular lines and pie slices (code in fl_arci.C):
FL_EXPORT void fl_arc(int x, int y, int w, int h, double a1, double a2);
FL_EXPORT void fl_pie(int x, int y, int w, int h, double a1, double a2);
FL_EXPORT void fl_chord(int x, int y, int w, int h, double a1, double a2); // nyi

// scalable drawing code (code in fl_vertex.C and fl_arc.C):
FL_EXPORT void fl_push_matrix();
FL_EXPORT void fl_pop_matrix();
FL_EXPORT void fl_scale(double x, double y);
FL_EXPORT void fl_scale(double x);
FL_EXPORT void fl_translate(double x, double y);
FL_EXPORT void fl_rotate(double d);
FL_EXPORT void fl_mult_matrix(double a, double b, double c, double d, double x,double y);
FL_EXPORT void fl_begin_points();
FL_EXPORT void fl_begin_line();
FL_EXPORT void fl_begin_loop();
FL_EXPORT void fl_begin_polygon();
FL_EXPORT void fl_vertex(double x, double y);
FL_EXPORT void fl_curve(double, double, double, double, double, double, double, double);
FL_EXPORT void fl_arc(double x, double y, double r, double start, double a);
FL_EXPORT void fl_circle(double x, double y, double r);
FL_EXPORT void fl_end_points();
FL_EXPORT void fl_end_line();
FL_EXPORT void fl_end_loop();
FL_EXPORT void fl_end_polygon();
FL_EXPORT void fl_begin_complex_polygon();
FL_EXPORT void fl_gap();
FL_EXPORT void fl_end_complex_polygon();
// get and use transformed positions:
FL_EXPORT double fl_transform_x(double x, double y);
FL_EXPORT double fl_transform_y(double x, double y);
FL_EXPORT double fl_transform_dx(double x, double y);
FL_EXPORT double fl_transform_dy(double x, double y);
FL_EXPORT void fl_transformed_vertex(double x, double y);

// current font:
FL_EXPORT void fl_font(int face, int size);
extern FL_EXPORT int fl_font_;
inline int fl_font() {return fl_font_;}
extern FL_EXPORT int fl_size_;
inline int fl_size() {return fl_size_;}

// information you can get about the current font:
FL_EXPORT int   fl_height();	// using "size" should work ok
inline int fl_height(int, int size) {return size;}
FL_EXPORT int   fl_descent();
FL_EXPORT double fl_width(const char*);
FL_EXPORT double fl_width(const char*, int n);
FL_EXPORT double fl_width(uchar);

// draw using current font:
FL_EXPORT void fl_draw(const char*, int x, int y);
FL_EXPORT void fl_draw(const char*, int n, int x, int y);
FL_EXPORT void fl_measure(const char*, int& x, int& y, int draw_symbols = 1);
FL_EXPORT void fl_draw(const char*, int,int,int,int, Fl_Align, Fl_Image* img=0,
                       int draw_symbols = 1);
FL_EXPORT void fl_draw(const char*, int,int,int,int, Fl_Align,
	               void (*callthis)(const char *, int n, int x, int y),
		       Fl_Image* img=0, int draw_symbols = 1);

// font encoding:
FL_EXPORT const char *fl_latin1_to_local(const char *, int n=-1);
FL_EXPORT const char *fl_local_to_latin1(const char *, int n=-1);
FL_EXPORT const char *fl_mac_roman_to_local(const char *, int n=-1);
FL_EXPORT const char *fl_local_to_mac_roman(const char *, int n=-1);

// boxtypes:
FL_EXPORT void fl_frame(const char* s, int x, int y, int w, int h);
FL_EXPORT void fl_frame2(const char* s, int x, int y, int w, int h);
FL_EXPORT void fl_draw_box(Fl_Boxtype, int x, int y, int w, int h, Fl_Color);

// images:
FL_EXPORT void fl_draw_image(const uchar*, int,int,int,int, int delta=3, int ldelta=0);
FL_EXPORT void fl_draw_image_mono(const uchar*, int,int,int,int, int delta=1, int ld=0);
typedef void (*Fl_Draw_Image_Cb)(void*,int,int,int,uchar*);
FL_EXPORT void fl_draw_image(Fl_Draw_Image_Cb, void*, int,int,int,int, int delta=3);
FL_EXPORT void fl_draw_image_mono(Fl_Draw_Image_Cb, void*, int,int,int,int, int delta=1);
FL_EXPORT void fl_rectf(int x, int y, int w, int h, uchar r, uchar g, uchar b);

FL_EXPORT uchar *fl_read_image(uchar *p, int x,int y, int w, int h, int alpha=0);

// pixmaps:
FL_EXPORT int fl_draw_pixmap(/*const*/ char* const* data, int x,int y,Fl_Color=FL_GRAY);
FL_EXPORT int fl_measure_pixmap(/*const*/ char* const* data, int &w, int &h);
FL_EXPORT int fl_draw_pixmap(const char* const* data, int x,int y,Fl_Color=FL_GRAY);
FL_EXPORT int fl_measure_pixmap(const char* const* data, int &w, int &h);

// other:
FL_EXPORT void fl_scroll(int X, int Y, int W, int H, int dx, int dy,
                         void (*draw_area)(void*, int,int,int,int), void* data);
FL_EXPORT const char* fl_shortcut_label(int);
FL_EXPORT void fl_overlay_rect(int,int,int,int);
FL_EXPORT void fl_overlay_clear();
FL_EXPORT void fl_cursor(Fl_Cursor, Fl_Color=FL_BLACK, Fl_Color=FL_WHITE);

// XForms symbols:
FL_EXPORT int fl_draw_symbol(const char* label,int x,int y,int w,int h, Fl_Color);
FL_EXPORT int fl_add_symbol(const char* name, void (*drawit)(Fl_Color), int scalable);

#endif

//
// End of "$Id: fl_draw.H 4975 2006-04-18 13:07:42Z matt $".
//
    End of automatic import -+/
/+- This file was imported from C++ using a script
//
// "$Id: fl_draw.cxx 5190 2006-06-09 16:16:34Z mike $"
//
// Label drawing code for the Fast Light Tool Kit (FLTK).
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
// Please report all bugs and problems on the following page:
//
//     http://www.fltk.org/str.php
//

// Implementation of fl_draw(const char*,int,int,int,int,Fl_Align)
// Used to draw all the labels and text, this routine:
// Word wraps the labels to fit into their bounding box.
// Breaks them into lines at the newlines.
// Expands all unprintable characters to ^X or \nnn notation
// Aligns them against the inside of the box.

#define min(a,b) ((a)<(b)?(a):(b))
#include <FL/fl_draw.H>
#include <FL/Fl_Image.H>

#include "flstring.h"
#include <ctype.h>
#include <math.h>
-+/
const uint MAXBUF = 1024;

static char* underline_at;

version (Apple) {
  static const char nbsp = 0xca;
} else {
  static const char nbsp = 0xa0;
}

// Copy p to buf, replacing unprintable characters with ^X and \nnn
// Stop at a newline or if MAXBUF characters written to buffer.
// Also word-wrap if width exceeds maxw.
// Returns a pointer to the start of the next line of caharcters.
// Sets n to the number of characters put into the buffer.
// Sets width to the width of the string in the current font.

static char*  expand(
    char* from, char* buf, double maxw, out int n, 
    out double width, int wrap, int draw_symbols) 
{
  char* o = buf;
  char* e = buf+(MAXBUF-4);
  underline_at = null;
  char* word_end = o;
  char* word_start = from;
  double w = 0;

  char* p = from;
  for (;; p++) {

    int c = *p & 255;

    if (!c || c == ' ' || c == '\n') {
      // test for word-wrap:
      if (word_start < p && wrap) {
	double newwidth = w + fl_width(word_end, o-word_end);
	if (word_end > buf && newwidth > maxw) { // break before this word
	  o = word_end;
	  p = word_start;
	  break;
	}
	word_end = o;
	w = newwidth;
      }
      if (!c) break;
      else if (c == '\n') {p++; break;}
      word_start = p+1;
    }

    if (o > e) break; // don't overflow buffer

    if (c == '\t') {
      for (c = (o-buf)%8; c<8 && o<e; c++) *o++ = ' ';
    } else if (c == '&' && fl_draw_shortcut && *(p+1)) {
      if (*(p+1) == '&') {p++; *o++ = '&';}
      else if (fl_draw_shortcut != 2) underline_at = o;
    } else if (c < ' ' || c == 127) { // ^X
      *o++ = '^';
      *o++ = c ^ 0x40;
    } else if (c == nbsp) { // non-breaking space in MacRoman
      *o++ = ' ';
    } else if (c == '@' && draw_symbols) { // Symbol???
      if (p[1] && p[1] != '@')  break;
      *o++ = c;
      if (p[1]) p++;
    } else {
      *o++ = c;
    }
  }

  width = w + fl_width(word_end, o-word_end);
  *o = 0;
  n = o-buf;
  return p;
}

void fl_draw(char[] str, int x, int y) {
  OSStatus err;
    // convert to UTF-16 first 
  UniChar[] uniStr = fl_macToUtf16(str);
    // now collect our ATSU resources
  ATSUTextLayout layout = fl_fontsize.layout;

  ByteCount iSize = CGContextRef.sizeof;
  ATSUAttributeTag iTag = kATSUCGContextTag;
  ATSUAttributeValuePtr iValuePtr=&fl_gc;
  ATSUSetLayoutControls(layout, 1, &iTag, &iSize, &iValuePtr);

  uint n = uniStr.length;
  err = ATSUSetTextPointerLocation(layout, uniStr.ptr, kATSUFromTextBeginning, n, n);
  err = ATSUDrawText(layout, kATSUFromTextBeginning, n, FloatToFixed(x), FloatToFixed(y));
}

void fl_draw(
    char str[],	// the (multi-line) string
    int x, int y, int w, int h,	// bounding box
    Fl_Align alignment,
    void function(char[] str, int x, int y) callthis,
    Fl_Image img=null, int draw_symbols=1) 
{
  if (str[$-1]!=0) str~=0;
  char* p;
  char* e;
  char buf[MAXBUF];
  int buflen;
  char symbol[2][255];
  char* symptr;
  int symwidth[2];
  int symoffset, symtotal;

  // count how many lines and put the last one into the buffer:
  int lines;
  double width;

  symbol[0][0] = '\0';
  symwidth[0]  = 0;

  symbol[1][0] = '\0';
  symwidth[1]  = 0;
/+=
  if (draw_symbols) {
    if (str && str[0] == '@' && str[1] && str[1] != '@') {
      // Start with a symbol...
      for (symptr = symbol[0];
           *str && !isspace(*str) && symptr < (symbol[0] + sizeof(symbol[0]) - 1);
           *symptr++ = *str++);
      *symptr = '\0';
      if (isspace(*str)) str++;
      symwidth[0] = min(w,h);
    }

    if (str && (p = strrchr(str, '@')) != NULL && p > (str + 1) && p[-1] != '@') {
      strlcpy(symbol[1], p, sizeof(symbol[1]));
      symwidth[1] = min(w,h);
    }
  }
=+/
  symtotal = symwidth[0] + symwidth[1];

  if (str) {
    for (p = str, lines=0; p;) {
      e = expand(p, buf, w - symtotal, buflen, width, alignment&FL_ALIGN_WRAP,
                 draw_symbols);
      lines++;
      if (!*e || (*e == '@' && e[1] != '@' && draw_symbols)) break;
      p = e;
    }
  } else lines = 0;

  if ((symwidth[0] || symwidth[1]) && lines) {
    if (symwidth[0]) symwidth[0] = lines * fl_height();
    if (symwidth[1]) symwidth[1] = lines * fl_height();
  }

  symtotal = symwidth[0] + symwidth[1];

  // figure out vertical position of the first line:
  int xpos;
  int ypos;
  int height = fl_height();
  int imgh = img ? img.h() : 0;

  symoffset = 0;

  if (alignment & FL_ALIGN_BOTTOM) ypos = y+h-(lines-1)*height-imgh;
  else if (alignment & FL_ALIGN_TOP) ypos = y+height;
  else ypos = y+(h-lines*height-imgh)/2+height;

  // draw the image unless the "text over image" alignment flag is set...
  if (img && !(alignment & FL_ALIGN_TEXT_OVER_IMAGE)) {
    if (img.w() > symoffset) symoffset = img.w();

    if (alignment & FL_ALIGN_LEFT) xpos = x + symwidth[0];
    else if (alignment & FL_ALIGN_RIGHT) xpos = x + w - img.w() - symwidth[1];
    else xpos = x + (w - img.w() - symtotal) / 2 + symwidth[0];

    img.draw(xpos, ypos - height);
    ypos += img.h();
  }

  // now draw all the lines:
  if (str) {
    int desc = fl_descent();
    for (p=str; ; ypos += height) {
      if (lines>1) e = expand(p, buf, w - symtotal, buflen, width,
                              alignment&FL_ALIGN_WRAP, draw_symbols);
      else e = "";

      if (width > symoffset) symoffset = cast(int)(width + 0.5);

      if (alignment & FL_ALIGN_LEFT) xpos = x + symwidth[0];
      else if (alignment & FL_ALIGN_RIGHT) xpos = x + w - cast(int)(width + .5) - symwidth[1];
      else xpos = x + (w - cast(int)(width + .5) - symtotal) / 2 + symwidth[0];

      char[] dstr = buf[0..buflen];
      callthis(dstr, xpos, ypos-desc);

      if (underline_at && underline_at >= buf && underline_at < (buf.ptr + buflen))
	callthis("_", xpos+cast(int)( fl_width(buf,underline_at-buf.ptr) ), ypos-desc);

      if (!*e || (*e == '@' && e[1] != '@')) break;
      p = e;
    }
  }

  // draw the image if the "text over image" alignment flag is set...
  if (img && (alignment & FL_ALIGN_TEXT_OVER_IMAGE)) {
    if (img.w() > symoffset) symoffset = img.w();

    if (alignment & FL_ALIGN_LEFT) xpos = x + symwidth[0];
    else if (alignment & FL_ALIGN_RIGHT) xpos = x + w - img.w() - symwidth[1];
    else xpos = x + (w - img.w() - symtotal) / 2 + symwidth[0];

    img.draw(xpos, ypos);
  }
/+=
  // draw the symbols, if any...
  if (symwidth[0]) {
    // draw to the left
    if (align & FL_ALIGN_LEFT) xpos = x;
    else if (align & FL_ALIGN_RIGHT) xpos = x + w - symtotal - symoffset;
    else xpos = x + (w - symoffset - symtotal) / 2;

    if (align & FL_ALIGN_BOTTOM) ypos = y + h - symwidth[0];
    else if (align & FL_ALIGN_TOP) ypos = y;
    else ypos = y + (h - symwidth[0]) / 2;

    fl_draw_symbol(symbol[0], xpos, ypos, symwidth[0], symwidth[0], fl_color());
  }

  if (symwidth[1]) {
    // draw to the right
    if (align & FL_ALIGN_LEFT) xpos = x + symoffset + symwidth[0];
    else if (align & FL_ALIGN_RIGHT) xpos = x + w - symwidth[1];
    else xpos = x + (w - symoffset - symtotal) / 2 + symoffset + symwidth[0];

    if (align & FL_ALIGN_BOTTOM) ypos = y + h - symwidth[1];
    else if (align & FL_ALIGN_TOP) ypos = y;
    else ypos = y + (h - symwidth[1]) / 2;

    fl_draw_symbol(symbol[1], xpos, ypos, symwidth[1], symwidth[1], fl_color());
  }
=+/
}

void fl_draw(
  char[] str,	// the (multi-line) string
  int x, int y, int w, int h,	// bounding box
  Fl_Align alignment,
  Fl_Image img=null,
  int draw_symbols=1) {
  if ((!str || !str.length) && !img) return;
  if (w && h && !fl_not_clipped(x, y, w, h) && (alignment & FL_ALIGN_INSIDE)) return;
  if (alignment & FL_ALIGN_CLIP) fl_push_clip(x, y, w, h);
  fl_draw(str, x, y, w, h, alignment, &fl_draw, img, draw_symbols);
  if (alignment & FL_ALIGN_CLIP) fl_pop_clip();
  //fl.font_mac.fl_draw(str, x, y);
}

void fl_measure(char[] str, inout int w, inout int h, int draw_symbols=1) {
  if (!str || !str.length) {
    w = 0; 
    h = 0; 
    return;
  }
  if (str[$-1]!=0) str~=0;
  h = fl_height();
  char* p;
  char* e;
  char buf[MAXBUF];
  int buflen;
  int lines;
  double width;
  int W = 0;
  char symbol[2][255];
  char* symptr;
  int symwidth[2];
  int  symtotal;

  // count how many lines and put the last one into the buffer:
  symbol[0][0] = '\0';
  symwidth[0]  = 0;

  symbol[1][0] = '\0';
  symwidth[1]  = 0;

  if (str && str[0] == '@' && str[1] && str[1] != '@') {
    // Start with a symbol...
    /+=
    for (symptr = symbol[0];
         *str && !isspace(*str) && symptr < (symbol[0] + symbol[0].sizeof - 1);
         *symptr++ = *str++) { }
    *symptr = '\0';
    if (isspace(*str)) str++;
    symwidth[0] = h;
    =+/
  }
  /+=
  if (str) {
    p = strrchr(str, '@');
    if (p && p>str+1) {
      strlcpy(symbol[1], p, sizeof(symbol[1]));
      symwidth[1] = h;
    }
  }
  =+/

  symtotal = symwidth[0] + symwidth[1];
  
  for (p = str, lines=0; p;) {
    e = expand(p, buf, w - symtotal, buflen, width, w != 0, draw_symbols);
    if (cast(int)ceilf(width) > W) W = cast(int)ceilf(width);
    lines++;
    if (!*e || (*e == '@' && draw_symbols)) break;
    p = e;
  }

  if ((symwidth[0] || symwidth[1]) && lines) {
    if (symwidth[0]) symwidth[0] = lines * fl_height();
    if (symwidth[1]) symwidth[1] = lines * fl_height();
  }

  symtotal = symwidth[0] + symwidth[1];
  
  w = W + symtotal;
  h = lines*h;
}

//
// End of "$Id: fl_draw.cxx 5190 2006-06-09 16:16:34Z mike $".
//
