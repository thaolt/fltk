//
// "$Id$"
//
// Fl_Help_Dialog dialog for the Fast Light Tool Kit (FLTK).
//
// Copyright 1998-2010 by Bill Spitzak and others.
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

// generated by Fast Light User Interface Designer (fluid) version 1.0108

#include "../fltk3/Fl_Help_Dialog.H"
#include "flstring.h"
#include <fltk3/fl_ask.H>

void Fl_Help_Dialog::cb_back__i(Fl_Button*, void*) {
  if (index_ > 0)
  index_ --;

if (index_ == 0)
  back_->deactivate();

forward_->activate();

int l = line_[index_];

if (strcmp(view_->filename(), file_[index_]) != 0)
  view_->load(file_[index_]);

view_->topline(l);
}
void Fl_Help_Dialog::cb_back_(Fl_Button* o, void* v) {
  ((Fl_Help_Dialog*)(o->parent()->parent()->user_data()))->cb_back__i(o,v);
}

void Fl_Help_Dialog::cb_forward__i(Fl_Button*, void*) {
  if (index_ < max_)
  index_ ++;

if (index_ >= max_)
  forward_->deactivate();

back_->activate();

int l = view_->topline();

if (strcmp(view_->filename(), file_[index_]) != 0)
  view_->load(file_[index_]);

view_->topline(l);
}
void Fl_Help_Dialog::cb_forward_(Fl_Button* o, void* v) {
  ((Fl_Help_Dialog*)(o->parent()->parent()->user_data()))->cb_forward__i(o,v);
}

void Fl_Help_Dialog::cb_smaller__i(Fl_Button*, void*) {
  if (view_->textsize() > 8)
  view_->textsize(view_->textsize() - 2);

if (view_->textsize() <= 8)
  smaller_->deactivate();
larger_->activate();
}
void Fl_Help_Dialog::cb_smaller_(Fl_Button* o, void* v) {
  ((Fl_Help_Dialog*)(o->parent()->parent()->user_data()))->cb_smaller__i(o,v);
}

void Fl_Help_Dialog::cb_larger__i(Fl_Button*, void*) {
  if (view_->textsize() < 18)
  view_->textsize(view_->textsize() + 2);

if (view_->textsize() >= 18)
  larger_->deactivate();
smaller_->activate();
}
void Fl_Help_Dialog::cb_larger_(Fl_Button* o, void* v) {
  ((Fl_Help_Dialog*)(o->parent()->parent()->user_data()))->cb_larger__i(o,v);
}

void Fl_Help_Dialog::cb_find__i(Fl_Input*, void*) {
  find_pos_ = view_->find(find_->value(), find_pos_);
}
void Fl_Help_Dialog::cb_find_(Fl_Input* o, void* v) {
  ((Fl_Help_Dialog*)(o->parent()->parent()->parent()->user_data()))->cb_find__i(o,v);
}

void Fl_Help_Dialog::cb_view__i(Fl_Help_View*, void*) {
  if (view_->filename())
{
  if (view_->changed())
  {
    index_ ++;

    if (index_ >= 100)
    {
      memmove(line_, line_ + 10, sizeof(line_[0]) * 90);
      memmove(file_, file_ + 10, sizeof(file_[0]) * 90);
      index_ -= 10;
    }

    max_ = index_;

    strlcpy(file_[index_], view_->filename(),sizeof(file_[0]));
    line_[index_] = view_->topline();

    if (index_ > 0)
      back_->activate();
    else
      back_->deactivate();

    forward_->deactivate();
    window_->label(view_->title());
  }
  else // if ! view_->changed()
  {
    strlcpy(file_[index_], view_->filename(), sizeof(file_[0]));
    line_[index_] = view_->topline();
  }
} else { // if ! view_->filename()
  index_ = 0; // hitting an internal page will disable the back/fwd buffer
  file_[index_][0] = 0; // unnamed internal page
  line_[index_] = view_->topline();
  back_->deactivate();
  forward_->deactivate();
};
}
void Fl_Help_Dialog::cb_view_(Fl_Help_View* o, void* v) {
  ((Fl_Help_Dialog*)(o->parent()->user_data()))->cb_view__i(o,v);
}

Fl_Help_Dialog::Fl_Help_Dialog() {
  { window_ = new Fl_Double_Window(530, 385, "Help Dialog");
    window_->user_data((void*)(this));
    { Fl_Group* o = new Fl_Group(10, 10, 511, 25);
      { back_ = new Fl_Button(10, 10, 25, 25, "@<-");
        back_->tooltip("Show the previous help page.");
        back_->shortcut(0xff51);
        back_->labelcolor((Fl_Color)2);
        back_->callback((Fl_Callback*)cb_back_);
      } // Fl_Button* back_
      { forward_ = new Fl_Button(45, 10, 25, 25, "@->");
        forward_->tooltip("Show the next help page.");
        forward_->shortcut(0xff53);
        forward_->labelcolor((Fl_Color)2);
        forward_->callback((Fl_Callback*)cb_forward_);
      } // Fl_Button* forward_
      { smaller_ = new Fl_Button(80, 10, 25, 25, "F");
        smaller_->tooltip("Make the help text smaller.");
        smaller_->labelfont(1);
        smaller_->labelsize(10);
        smaller_->callback((Fl_Callback*)cb_smaller_);
      } // Fl_Button* smaller_
      { larger_ = new Fl_Button(115, 10, 25, 25, "F");
        larger_->tooltip("Make the help text larger.");
        larger_->labelfont(1);
        larger_->labelsize(16);
        larger_->callback((Fl_Callback*)cb_larger_);
      } // Fl_Button* larger_
      { Fl_Group* o = new Fl_Group(350, 10, 171, 25);
        o->box(FL_DOWN_BOX);
        o->color(FL_BACKGROUND2_COLOR);
        { find_ = new Fl_Input(375, 12, 143, 21, "@search");
          find_->tooltip("find text in document");
          find_->box(FL_FLAT_BOX);
          find_->labelsize(13);
          find_->textfont(4);
          find_->callback((Fl_Callback*)cb_find_);
          find_->when(FL_WHEN_ENTER_KEY_ALWAYS);
        } // Fl_Input* find_
        o->end();
      } // Fl_Group* o
      { Fl_Box* o = new Fl_Box(150, 10, 190, 25);
        Fl_Group::current()->resizable(o);
      } // Fl_Box* o
      o->end();
    } // Fl_Group* o
    { view_ = new Fl_Help_View(10, 45, 510, 330);
      view_->box(FL_DOWN_BOX);
      view_->callback((Fl_Callback*)cb_view_);
      Fl_Group::current()->resizable(view_);
    } // Fl_Help_View* view_
    window_->size_range(260, 150);
    window_->end();
  } // Fl_Double_Window* window_
  back_->deactivate();
forward_->deactivate();

index_    = -1;
max_      = 0;
find_pos_ = 0;

fl_register_images();
}

Fl_Help_Dialog::~Fl_Help_Dialog() {
  delete window_;
}

int Fl_Help_Dialog::h() {
  return (window_->h());
}

void Fl_Help_Dialog::hide() {
  window_->hide();
}

void Fl_Help_Dialog::load(const char *f) {
  view_->set_changed();
view_->load(f);
window_->label(view_->title());
}

void Fl_Help_Dialog::position(int xx, int yy) {
  window_->position(xx, yy);
}

void Fl_Help_Dialog::resize(int xx, int yy, int ww, int hh) {
  window_->resize(xx, yy, ww, hh);
}

void Fl_Help_Dialog::show() {
  window_->show();
}

void Fl_Help_Dialog::show(int argc, char **argv) {
  window_->show(argc, argv);
}

void Fl_Help_Dialog::textsize(Fl_Fontsize s) {
  view_->textsize(s);

if (s <= 8)
  smaller_->deactivate();
else
  smaller_->activate();

if (s >= 18)
  larger_->deactivate();
else
  larger_->activate();
}

Fl_Fontsize Fl_Help_Dialog::textsize() {
  return (view_->textsize());
}

void Fl_Help_Dialog::topline(const char *n) {
  view_->topline(n);
}

void Fl_Help_Dialog::topline(int n) {
  view_->topline(n);
}

void Fl_Help_Dialog::value(const char *f) {
  view_->set_changed();
view_->value(f);
window_->label(view_->title());
}

const char * Fl_Help_Dialog::value() const {
  return view_->value();
}

int Fl_Help_Dialog::visible() {
  return (window_->visible());
}

int Fl_Help_Dialog::w() {
  return (window_->w());
}

int Fl_Help_Dialog::x() {
  return (window_->x());
}

int Fl_Help_Dialog::y() {
  return (window_->y());
}

//
// End of "$Id$".
//
