//
// "$Id$"
//
// Fl_Help_Dialog dialog for the Fast Light Tool Kit (FLTK).
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

// generated by Fast Light User Interface Designer (fluid) version 1.0107

#include "../FL/Fl_Help_Dialog.H"
#include "flstring.h"
#include <FL/fl_ask.H>

void Fl_Help_Dialog::cb_view__i(Fl_Help_View*, void*) {
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
else if (view_->filename())
{
  strlcpy(file_[index_], view_->filename(), sizeof(file_[0]));
  line_[index_] = view_->topline();
};
}
void Fl_Help_Dialog::cb_view_(Fl_Help_View* o, void* v) {
  ((Fl_Help_Dialog*)(o->parent()->user_data()))->cb_view__i(o,v);
}

void Fl_Help_Dialog::cb_Close_i(Fl_Button*, void*) {
  window_->hide();
}
void Fl_Help_Dialog::cb_Close(Fl_Button* o, void* v) {
  ((Fl_Help_Dialog*)(o->parent()->parent()->user_data()))->cb_Close_i(o,v);
}

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

Fl_Help_Dialog::Fl_Help_Dialog() {
  Fl_Double_Window* w;
  { Fl_Double_Window* o = window_ = new Fl_Double_Window(530, 385, "Help Dialog");
    w = o;
    o->user_data((void*)(this));
    { Fl_Help_View* o = view_ = new Fl_Help_View(10, 10, 510, 330);
      o->box(FL_DOWN_BOX);
      o->color(FL_BACKGROUND_COLOR);
      o->selection_color(FL_SELECTION_COLOR);
      o->labeltype(FL_NORMAL_LABEL);
      o->labelfont(0);
      o->labelsize(14);
      o->labelcolor(FL_BLACK);
      o->callback((Fl_Callback*)cb_view_);
      o->align(FL_ALIGN_TOP);
      o->when(FL_WHEN_RELEASE);
      o->end();
      Fl_Group::current()->resizable(o);
    }
    { Fl_Group* o = new Fl_Group(10, 348, 510, 27);
      { Fl_Button* o = new Fl_Button(456, 350, 64, 25, "Close");
        o->callback((Fl_Callback*)cb_Close);
        o->label(fl_close);
      }
      { Fl_Button* o = back_ = new Fl_Button(386, 350, 25, 25, "@<-");
        o->tooltip("Show the previous help page.");
        o->shortcut(0xff51);
        o->labelcolor((Fl_Color)2);
        o->callback((Fl_Callback*)cb_back_);
      }
      { Fl_Button* o = forward_ = new Fl_Button(421, 350, 25, 25, "@->");
        o->tooltip("Show the next help page.");
        o->shortcut(0xff53);
        o->labelcolor((Fl_Color)2);
        o->callback((Fl_Callback*)cb_forward_);
      }
      { Fl_Button* o = smaller_ = new Fl_Button(316, 350, 25, 25, "F");
        o->tooltip("Make the help text smaller.");
        o->labelfont(1);
        o->labelsize(10);
        o->callback((Fl_Callback*)cb_smaller_);
      }
      { Fl_Button* o = larger_ = new Fl_Button(351, 350, 25, 25, "F");
        o->tooltip("Make the help text larger.");
        o->labelfont(1);
        o->labelsize(16);
        o->callback((Fl_Callback*)cb_larger_);
      }
      { Fl_Group* o = new Fl_Group(10, 350, 296, 25);
        o->box(FL_DOWN_BOX);
        o->color(FL_BACKGROUND2_COLOR);
        { Fl_Input* o = find_ = new Fl_Input(35, 352, 268, 21, "@search");
          o->tooltip("find text in document");
          o->box(FL_FLAT_BOX);
          o->labelsize(13);
          o->callback((Fl_Callback*)cb_find_);
          o->when(FL_WHEN_ENTER_KEY_ALWAYS);
          Fl_Group::current()->resizable(o);
        }
        o->end();
        Fl_Group::current()->resizable(o);
      }
      o->end();
    }
    o->end();
  }
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

void Fl_Help_Dialog::textsize(uchar s) {
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

uchar Fl_Help_Dialog::textsize() {
  return (view_->textsize());
}

void Fl_Help_Dialog::topline(const char *n) {
  view_->topline(n);
}

void Fl_Help_Dialog::topline(int n) {
  view_->topline(n);
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
