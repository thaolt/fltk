//
// "$Id: Fl_Adjuster.cxx,v 1.54 2005/01/25 09:49:10 spitzak Exp $"
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

#include <fltk/Adjuster.h>
#include <fltk/Box.h>
#include <fltk/events.h>
#include <fltk/damage.h>
#include <fltk/draw.h>
#include <fltk/xbmImage.h>
using namespace fltk;

/*! \class fltk::Adjuster

  Valuator widget that displays three buttons. The user pushes down
  the button and drags left/right to adjust, or clicks the button to
  step, or shift-clicks to step backwards. One button moves in the
  step() values, the next in 10*step(), and the third in 100*step().
  Holding down shift makes the buttons move in the opposite way.
  Depreciated.

  \image html adjuster1.gif
*/

#include "fastarrow.h"
static xbmImage fastarrow(fastarrow_bits, fastarrow_width, fastarrow_height);
#include "mediumarrow.h"
static xbmImage mediumarrow(mediumarrow_bits, mediumarrow_width, mediumarrow_height);
#include "slowarrow.h"
static xbmImage slowarrow(slowarrow_bits, slowarrow_width, slowarrow_height);

static xbmImage* arrows[3] = {&fastarrow,&mediumarrow,&slowarrow};

enum {
  GLYPH_FASTARROW,
  GLYPH_MEDIUMARROW,
  GLYPH_SLOWARROW
};

static void glyph(int t, const Rectangle& r, const Style* s, Flags flags)
{
  s->buttonbox()->draw(r,s,flags);
  xbmImage* b = arrows[t-GLYPH_FASTARROW];
  b->draw(Rectangle(r, b->width(), b->height()), s, flags);
}

// changing the value does not change the appearance:
void Adjuster::value_damage() {}

void Adjuster::draw() {
  int dx, dy, W, H;
  if (w()>=h()) {
    dx = W = w()/3;
    dy = 0; H = h();
  } else {
    dx = 0; W = w();
    dy = H = h()/3;
  }

  Flags flags = current_flags();
  Flags f[4];
  for (int i = 1; i < 4; i++) {
    f[i] = flags;
    if (drag == i) f[i] |= VALUE|PUSHED;
    else if (highlight == i) f[i] |= HIGHLIGHT;
  }

  Rectangle r(W,H);
  if (damage()&DAMAGE_ALL || last == 1 || highlight == 1) {
    r.y(2*dy); draw_glyph(GLYPH_FASTARROW, r, f[1]);}
  if (damage()&DAMAGE_ALL || last == 2 || highlight == 2) {
    r.x(dx); r.y(dy); draw_glyph(GLYPH_MEDIUMARROW, r, f[2]);}
  if (damage()&DAMAGE_ALL || last == 3 || highlight == 3) {
    r.x(2*dx); r.y(0); draw_glyph(GLYPH_SLOWARROW, r, f[3]);}

  last = highlight;
}

int Adjuster::handle(int event) {
  int delta;
  int mx = event_x();

  int which_button;
  if (w()>=h())
    which_button = 3*mx/w() + 1;
  else
    which_button = 3-3*(event_y()-1)/h();
  if (which_button > 3) which_button = 3;
  else if (which_button < 1) which_button = 1;

  switch (event) {

  case PUSH:
    handle_push();
    ix = mx;
    drag = highlight = which_button;
    redraw();
    return 1;

  case DRAG:
    if (w() >= h()) {
      delta = (drag-1)*w()/3;	// left edge of button
      if (mx < delta)
	delta = mx-delta;
      else if (mx > (delta+w()/3)) // right edge of button
	delta = mx-delta-w()/3;
      else
	delta = 0;
    } else {
      if (mx < 0)
	delta = mx;
      else if (mx > w())
	delta = mx-w();
      else
	delta = 0;
    }
    if (drag == 1) delta *= 100; else if (drag == 2) delta *= 10;
    handle_drag(previous_value() + (step() ? step() : .01f) * delta);
    return 1;

  case RELEASE:
    if (pushed()) return 1;
    if (event_is_click()) { // detect click but no drag
      if (drag == 1) delta = 1000; else if (drag == 2) delta = 100;
      else delta = 10;
      if (event_state()& (SHIFT|CAPSLOCK|CTRL|ALT)) 
	delta = -delta;
      handle_drag(previous_value() + (step() ? step() : .01f) * delta);
    }
    drag = 0;
    redraw();
    handle_release();
    return 1;

  case LEAVE:
    which_button = 0;
  case ENTER:
  case MOVE:
    highlight = which_button;
    if (last != highlight) redraw();
    return 1;

  case FOCUS:
  case UNFOCUS:
    redraw();
  default:
    return Valuator::handle(event);
  }
}

static void revert(Style* s) {
  s->box_ = NO_BOX; // for compatability if in the future it draws the box
  s->glyph_ = glyph;
}
static NamedStyle style("Adjuster", revert, &Adjuster::default_style);

NamedStyle* Adjuster::default_style = &::style;

Adjuster::Adjuster(int x,int y,int w,int h,const char *l) : Valuator(x,y,w,h,l) {
  style(default_style);
  step(1.0/10000);
  drag = highlight = 0;
  soft_ = 1;
  //  set_click_to_focus();
}

//
// End of "$Id: Fl_Adjuster.cxx,v 1.54 2005/01/25 09:49:10 spitzak Exp $".
//
