//
// "$Id: Fl_Value_Slider.cxx,v 1.9 1999/08/16 07:31:22 bill Exp $"
//
// Value slider widget for the Fast Light Tool Kit (FLTK).
//
// Copyright 1998-1999 by Bill Spitzak and others.
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
// Please report all bugs and problems to "fltk-bugs@easysw.com".
//

#include <FL/Fl.H>
#include <FL/Fl_Value_Slider.H>
#include <FL/fl_draw.H>
#include <FL/Fl_Output.H>

Fl_Style Fl_Value_Slider::default_style = {0};

Fl_Value_Slider::Fl_Value_Slider(int x, int y, int w, int h, const char*l)
: Fl_Slider(x, y, w, h, l) {
  if (style(default_style)) default_style.text_size = 10;
  step(1, 100);
}

void Fl_Value_Slider::draw() {
  int sxx = x(), syy = y(), sww = w(), shh = h();
  int bxx = x(), byy = y(), bww = w(), bhh = h();
  if (horizontal()) {
    bww = 35; sxx += 35; sww -= 35;
  } else {
    syy += 25; bhh = 25; shh -= 25;
  }
  Fl_Flags f = active_r() ? FL_NO_FLAGS : FL_INACTIVE;
  box()->draw(sxx, syy, sww, shh, color(), f|FL_FRAME_ONLY);
  Fl_Slider::draw(sxx+box()->dx(),
		  syy+box()->dy(),
		  sww-box()->dw(),
		  shh-box()->dh());
  Fl_Output::default_style.box->draw(bxx, byy, bww, bhh,
				     Fl_Output::default_style.color, f);
  char buf[128];
  format(buf);
  fl_font(textfont(), textsize());
  fl_color(active_r() ? textcolor() : fl_inactive(textcolor()));
  fl_draw(buf, bxx, byy, bww, bhh, FL_ALIGN_CLIP);
}

int Fl_Value_Slider::handle(int event) {
  int sxx = x(), syy = y(), sww = w(), shh = h();
  if (horizontal()) {
    sxx += 35; sww -= 35;
  } else {
    syy += 25; shh -= 25;
  }
  return Fl_Slider::handle(event,
			   sxx+box()->dx(),
			   syy+box()->dy(),
			   sww-box()->dw(),
			   shh-box()->dh());
}

//
// End of "$Id: Fl_Value_Slider.cxx,v 1.9 1999/08/16 07:31:22 bill Exp $".
//
