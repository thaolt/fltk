//
// "$Id: fl_glyph.cxx,v 1.42 2004/08/01 22:28:23 spitzak Exp $"
//
// Copyright 1998-2003 by Bill Spitzak and others.
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

#include <fltk/Widget.h>
#include <fltk/Box.h>
#include <fltk/draw.h>
using namespace fltk;

/*! \typedef fltk::GlyphStyle

  This type of function that is placed into Style::glyph().  A
  Widget::draw() method would call this to draw various portions of
  itself. A \ref themes(theme) can modify the glyph function to change
  the appearance of those parts of the widget.

  The arguments are exactly the same as for a Symbol, with an added
  index number to say which glyph to draw. Ideally you should just
  call the correct Symbol or Image with the same arguments.
*/

/*! This is the glyph() function put into the default_style. See
  \ref glyphs for what it does. */
void Widget::default_glyph(int glyph, int x,int y,int w,int h, const Style* style, Flags flags)
{
  Color bg, fg; style->boxcolors(flags, bg, fg);
  Box* box = 0;

  // handle special glyphs that don't draw the box:
  switch (glyph) {
  case GLYPH_UP:
  case GLYPH_DOWN:
  case GLYPH_LEFT:
  case GLYPH_RIGHT:
    // these glyphs do not have a box
    break;
  default: {
    box = style->buttonbox();
    box->draw(x,y,w,h, style, flags);
    box->inset(x,y,w,h);
    }
  }

  if (w > h) {
    x += (w-h)/2;
    w = h;
  }
  // to draw the shape inactive, draw it twice to get the engraved look:
  int i = 0;
  if (flags & INACTIVE) {
    i = 1;
    fg = inactive(fg);
  }
  for ( /*i*/ ; i >= 0; i--) {
    Color color = i ? Color(GRAY99) : fg;
    setcolor(color);

    int w1 = (w+2)/3; int x1,y1;
    switch(glyph) {

    case GLYPH_UP_BUTTON:
    case GLYPH_UP:
      x1 = x+(w-1)/2-w1+i;
      y1 = y+(h-w1-1)/2+i;
      addvertex(x1, y1+w1);
      addvertex(x1+2*w1, y1+w1);
      addvertex(x1+w1, y1);
      fillstrokepath(color);
      break;

    case GLYPH_DOWN_BUTTON:
    case GLYPH_DOWN:
      x1 = x+(w-1)/2-w1+i;
      y1 = y+(h-w1)/2+i;
      addvertex(x1, y1);
      addvertex(x1+w1, y1+w1);
      addvertex(x1+2*w1, y1);
      fillstrokepath(color);
      break;

    case GLYPH_LEFT_BUTTON:
    case GLYPH_LEFT:
      x1 = x+(w-w1-1)/2+i;
      y1 = y+(h-1)/2-w1+i;
      addvertex(x1, y1+w1);
      addvertex(x1+w1, y1+2*w1);
      addvertex(x1+w1, y1);
      fillstrokepath(color);
      break;

    case GLYPH_RIGHT_BUTTON:
    case GLYPH_RIGHT:
      x1 = x+(w-w1)/2+i;
      y1 = y+(h-1)/2-w1+i;
      addvertex(x1, y1);
      addvertex(x1+w1, y1+w1);
      addvertex(x1, y1+2*w1);
      fillstrokepath(color);
      break;

    }
  }
  if (box) style->focusbox()->draw(x,y,w,h, style, flags);
}

//
// End of "$Id: fl_glyph.cxx,v 1.42 2004/08/01 22:28:23 spitzak Exp $".
//
