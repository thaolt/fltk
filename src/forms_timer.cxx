/
// "$Id$
/
// Forms timer object for the Fast Light Tool Kit (FLTK)
/
// Copyright 1998-2004 by Bill Spitzak and others
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

// Emulate the Forms Timer objec
// You don't want to use this if you just want a timeout, cal
// Fl::add_timeout directly

#include <FL/Fl.H
#include <FL/Fl_Timer.H
#include <FL/fl_draw.H
#ifdef WIN3
#  ifdef __MWERKS_
#    include <time.h
#  els
#    include <sys/types.h>
#    include <sys/timeb.h
#  endi
#els
#  include <time.h
#  include <sys/time.h
#endi
#include <stdio.h

#define FL_TIMER_BLINKRATE	0.

void fl_gettime(long* sec, long* usec) 
#ifdef WIN3
# ifdef __MWERKS_
  time_t localTime = time(NULL)
  struct tm *now = localtime(&localTime)
  *sec = now->tm_sec + 60*now->tm_min + 3600*now->tm_hour + 24*3600*now->tm_yday
  *usec = 0
# els
  struct timeb tp
  ftime(&tp)
  *sec = tp.time
  *usec = tp.millitm * 1000
# endi
#els
  struct timeval tp
  struct timezone tzp
  gettimeofday(&tp, &tzp)
  *sec = tp.tv_sec
  *usec = tp.tv_usec
#endi


void Fl_Timer::draw() 
  int tt
  Fl_Color col
  char str[32]
  if (!on || delay>0.0
    col = color()
  else if ((int) (delay / FL_TIMER_BLINKRATE) % 2
    col = color()
  els
    col = selection_color()
  draw_box(box(), col)
  if (type() == FL_VALUE_TIMER && delay>0.0) 
    double d = direction_ ? total-delay : delay
    if (d < 60.0
      sprintf(str, "%.1f", d)
    else 
      tt = (int) ((d+0.05) / 60.0)
      sprintf(str, "%d:%04.1f", tt, d - 60.0 * tt)
    
    fl_font(labelfont(), labelsize())
    fl_color(labelcolor())
    fl_draw(str, x(), y(), w(), h(), FL_ALIGN_CENTER)
  } els
    draw_label()


void Fl_Timer::stepcb(void* v) 
  ((Fl_Timer*)v)->step()


void Fl_Timer::step() 
  if (!on) return
  double lastdelay = delay
  long sec, usec; fl_gettime(&sec, &usec)
  delay -= (double) (sec - lastsec) + (double) (usec - lastusec) / 1000000.0
  lastsec = sec; lastusec = usec
  if (lastdelay > 0.0 && delay <= 0.0) 
    if (type() == FL_HIDDEN_TIMER) 
      on = 0
      delay = 0
    } else 
      redraw()
      Fl::add_timeout(FL_TIMER_BLINKRATE, stepcb, this)
    
    set_changed()
    do_callback()
  } else 
    if (type() == FL_VALUE_TIMER) redraw()
    Fl::add_timeout(FL_TIMER_BLINKRATE, stepcb, this)
  


int Fl_Timer::handle(int event) 
  if (event == FL_RELEASE && delay <= 0) value(0.0)
  return 0


Fl_Timer::~Fl_Timer() 
  Fl::remove_timeout(stepcb, this)


Fl_Timer::Fl_Timer(uchar t, int X, int Y, int W, int H, const char* l
: Fl_Widget(X, Y, W, H, l) 
  box(FL_DOWN_BOX)
  selection_color(FL_RED)
  delay = 0
  on = 0
  direction_ = 0
  type(t)
  if (t == FL_HIDDEN_TIMER) clear_visible()
  if (t == FL_VALUE_TIMER) align(FL_ALIGN_LEFT)


void Fl_Timer::value(double d) 
  delay = total = d
  on = (d > 0.0)
  fl_gettime(&(lastsec), &(lastusec))
  if (type() != FL_HIDDEN_TIMER) redraw()
  Fl::remove_timeout(stepcb, this)
  if (on) Fl::add_timeout(FL_TIMER_BLINKRATE, stepcb, this)


void Fl_Timer::suspended(char d) 
  if (!d) 
    if (on) return
    on = (delay > 0.0)
    fl_gettime(&(lastsec), &(lastusec))
    if (on) Fl::add_timeout(FL_TIMER_BLINKRATE, stepcb, this)
  } else 
    if (!on) return
    on = 0
    Fl::remove_timeout(stepcb, this)
  


/
// End of "$Id$"
/
