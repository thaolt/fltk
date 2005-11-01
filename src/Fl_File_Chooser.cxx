//
// "$Id$"
//
// Fl_File_Chooser dialog for the Fast Light Tool Kit (FLTK).
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

#include "../FL/Fl_File_Chooser.H"
#include <FL/fl_draw.H>

void Fl_File_Chooser::cb_window_i(Fl_Double_Window*, void*) {
  fileName->value("");
fileList->deselect();
Fl::remove_timeout((Fl_Timeout_Handler)previewCB, this);
window->hide();
}
void Fl_File_Chooser::cb_window(Fl_Double_Window* o, void* v) {
  ((Fl_File_Chooser*)(o->user_data()))->cb_window_i(o,v);
}

void Fl_File_Chooser::cb_showChoice_i(Fl_Choice*, void*) {
  showChoiceCB();
}
void Fl_File_Chooser::cb_showChoice(Fl_Choice* o, void* v) {
  ((Fl_File_Chooser*)(o->parent()->parent()->user_data()))->cb_showChoice_i(o,v);
}

void Fl_File_Chooser::cb_favoritesButton_i(Fl_Menu_Button*, void*) {
  favoritesButtonCB();
}
void Fl_File_Chooser::cb_favoritesButton(Fl_Menu_Button* o, void* v) {
  ((Fl_File_Chooser*)(o->parent()->parent()->user_data()))->cb_favoritesButton_i(o,v);
}

void Fl_File_Chooser::cb_newButton_i(Fl_Button*, void*) {
  newdir();
}
void Fl_File_Chooser::cb_newButton(Fl_Button* o, void* v) {
  ((Fl_File_Chooser*)(o->parent()->parent()->user_data()))->cb_newButton_i(o,v);
}

#include <FL/Fl_Bitmap.H>
static unsigned char idata_new[] =
{0,0,120,0,132,0,2,1,1,254,1,128,49,128,49,128,253,128,253,128,49,128,49,
128,1,128,1,128,255,255,0,0};
static Fl_Bitmap image_new(idata_new, 16, 16);

void Fl_File_Chooser::cb__i(Fl_Tile*, void*) {
  update_preview();
}
void Fl_File_Chooser::cb_(Fl_Tile* o, void* v) {
  ((Fl_File_Chooser*)(o->parent()->user_data()))->cb__i(o,v);
}

void Fl_File_Chooser::cb_fileList_i(Fl_File_Browser*, void*) {
  fileListCB();
}
void Fl_File_Chooser::cb_fileList(Fl_File_Browser* o, void* v) {
  ((Fl_File_Chooser*)(o->parent()->parent()->user_data()))->cb_fileList_i(o,v);
}

void Fl_File_Chooser::cb_previewButton_i(Fl_Check_Button*, void*) {
  preview(previewButton->value());
}
void Fl_File_Chooser::cb_previewButton(Fl_Check_Button* o, void* v) {
  ((Fl_File_Chooser*)(o->parent()->parent()->parent()->user_data()))->cb_previewButton_i(o,v);
}

void Fl_File_Chooser::cb_fileName_i(Fl_File_Input*, void*) {
  fileNameCB();
}
void Fl_File_Chooser::cb_fileName(Fl_File_Input* o, void* v) {
  ((Fl_File_Chooser*)(o->parent()->parent()->user_data()))->cb_fileName_i(o,v);
}

void Fl_File_Chooser::cb_okButton_i(Fl_Return_Button*, void*) {
  // Do any callback that is registered...
if (callback_)
  (*callback_)(this, data_);

window->hide();
}
void Fl_File_Chooser::cb_okButton(Fl_Return_Button* o, void* v) {
  ((Fl_File_Chooser*)(o->parent()->parent()->parent()->user_data()))->cb_okButton_i(o,v);
}

void Fl_File_Chooser::cb_cancelButton_i(Fl_Button*, void*) {
  fileName->value("");
fileList->deselect();
Fl::remove_timeout((Fl_Timeout_Handler)previewCB, this);
window->hide();
}
void Fl_File_Chooser::cb_cancelButton(Fl_Button* o, void* v) {
  ((Fl_File_Chooser*)(o->parent()->parent()->parent()->user_data()))->cb_cancelButton_i(o,v);
}

void Fl_File_Chooser::cb_favList_i(Fl_File_Browser*, void*) {
  favoritesCB(favList);
}
void Fl_File_Chooser::cb_favList(Fl_File_Browser* o, void* v) {
  ((Fl_File_Chooser*)(o->parent()->user_data()))->cb_favList_i(o,v);
}

void Fl_File_Chooser::cb_favUpButton_i(Fl_Button*, void*) {
  favoritesCB(favUpButton);
}
void Fl_File_Chooser::cb_favUpButton(Fl_Button* o, void* v) {
  ((Fl_File_Chooser*)(o->parent()->parent()->user_data()))->cb_favUpButton_i(o,v);
}

void Fl_File_Chooser::cb_favDeleteButton_i(Fl_Button*, void*) {
  favoritesCB(favDeleteButton);
}
void Fl_File_Chooser::cb_favDeleteButton(Fl_Button* o, void* v) {
  ((Fl_File_Chooser*)(o->parent()->parent()->user_data()))->cb_favDeleteButton_i(o,v);
}

void Fl_File_Chooser::cb_favDownButton_i(Fl_Button*, void*) {
  favoritesCB(favDownButton);
}
void Fl_File_Chooser::cb_favDownButton(Fl_Button* o, void* v) {
  ((Fl_File_Chooser*)(o->parent()->parent()->user_data()))->cb_favDownButton_i(o,v);
}

void Fl_File_Chooser::cb_favCancelButton_i(Fl_Button*, void*) {
  favWindow->hide();
}
void Fl_File_Chooser::cb_favCancelButton(Fl_Button* o, void* v) {
  ((Fl_File_Chooser*)(o->parent()->parent()->user_data()))->cb_favCancelButton_i(o,v);
}

void Fl_File_Chooser::cb_favOkButton_i(Fl_Return_Button*, void*) {
  favoritesCB(favOkButton);
}
void Fl_File_Chooser::cb_favOkButton(Fl_Return_Button* o, void* v) {
  ((Fl_File_Chooser*)(o->parent()->parent()->user_data()))->cb_favOkButton_i(o,v);
}

Fl_File_Chooser::Fl_File_Chooser(const char *d, const char *p, int t, const char *title) {
  Fl_Double_Window* w;
  { Fl_Double_Window* o = window = new Fl_Double_Window(490, 380, "Choose File");
    w = o;
    o->callback((Fl_Callback*)cb_window, (void*)(this));
    { Fl_Group* o = new Fl_Group(10, 10, 470, 25);
      { Fl_Choice* o = showChoice = new Fl_Choice(65, 10, 215, 25, "Show:");
        o->down_box(FL_BORDER_BOX);
        o->labelfont(1);
        o->callback((Fl_Callback*)cb_showChoice);
        Fl_Group::current()->resizable(o);
        showChoice->label(show_label);
      }
      { Fl_Menu_Button* o = favoritesButton = new Fl_Menu_Button(290, 10, 155, 25, "Favorites");
        o->down_box(FL_BORDER_BOX);
        o->callback((Fl_Callback*)cb_favoritesButton);
        o->align(FL_ALIGN_LEFT|FL_ALIGN_INSIDE);
        favoritesButton->label(favorites_label);
      }
      { Fl_Button* o = newButton = new Fl_Button(455, 10, 25, 25);
        o->image(image_new);
        o->labelsize(8);
        o->callback((Fl_Callback*)cb_newButton);
        o->tooltip(new_directory_tooltip);
      }
      o->end();
    }
    { Fl_Tile* o = new Fl_Tile(10, 45, 470, 225);
      o->callback((Fl_Callback*)cb_);
      { Fl_File_Browser* o = fileList = new Fl_File_Browser(10, 45, 295, 225);
        o->type(2);
        o->callback((Fl_Callback*)cb_fileList);
        w->hotspot(o);
      }
      { Fl_Box* o = previewBox = new Fl_Box(305, 45, 175, 225, "?");
        o->box(FL_DOWN_BOX);
        o->labelsize(100);
        o->align(FL_ALIGN_CLIP|FL_ALIGN_INSIDE);
      }
      o->end();
      Fl_Group::current()->resizable(o);
    }
    { Fl_Group* o = new Fl_Group(10, 275, 470, 95);
      { Fl_Group* o = new Fl_Group(10, 275, 470, 20);
        { Fl_Check_Button* o = previewButton = new Fl_Check_Button(10, 275, 170, 20, "Preview");
          o->down_box(FL_DOWN_BOX);
          o->value(1);
          o->shortcut(0x80070);
          o->callback((Fl_Callback*)cb_previewButton);
          previewButton->label(preview_label);
        }
        { Fl_Box* o = new Fl_Box(10, 275, 395, 20);
          Fl_Group::current()->resizable(o);
        }
        o->end();
      }
      { Fl_File_Input* o = fileName = new Fl_File_Input(115, 300, 365, 35);
        o->labelfont(1);
        o->callback((Fl_Callback*)cb_fileName);
        o->when(FL_WHEN_ENTER_KEY);
        Fl_Group::current()->resizable(o);
        fileName->when(FL_WHEN_CHANGED | FL_WHEN_ENTER_KEY_ALWAYS);
      }
      { Fl_Box* o = new Fl_Box(10, 310, 105, 25, "Filename:");
        o->labelfont(1);
        o->align(FL_ALIGN_RIGHT|FL_ALIGN_INSIDE);
        o->label(filename_label);
      }
      { Fl_Group* o = new Fl_Group(10, 345, 470, 25);
        { Fl_Return_Button* o = okButton = new Fl_Return_Button(313, 345, 85, 25, "OK");
          o->callback((Fl_Callback*)cb_okButton);
          okButton->label(fl_ok);
        }
        { Fl_Button* o = cancelButton = new Fl_Button(408, 345, 72, 25, "Cancel");
          o->callback((Fl_Callback*)cb_cancelButton);
          o->label(fl_cancel);
        }
        { Fl_Box* o = new Fl_Box(10, 345, 30, 25);
          Fl_Group::current()->resizable(o);
        }
        o->end();
      }
      o->end();
    }
    if (title) window->label(title);
    o->set_modal();
    o->end();
  }
  { Fl_Double_Window* o = favWindow = new Fl_Double_Window(355, 150, "Manage Favorites");
    w = o;
    o->user_data((void*)(this));
    { Fl_File_Browser* o = favList = new Fl_File_Browser(10, 10, 300, 95);
      o->type(2);
      o->callback((Fl_Callback*)cb_favList);
      Fl_Group::current()->resizable(o);
    }
    { Fl_Group* o = new Fl_Group(320, 10, 25, 95);
      { Fl_Button* o = favUpButton = new Fl_Button(320, 10, 25, 25, "@8>");
        o->callback((Fl_Callback*)cb_favUpButton);
      }
      { Fl_Button* o = favDeleteButton = new Fl_Button(320, 45, 25, 25, "X");
        o->labelfont(1);
        o->callback((Fl_Callback*)cb_favDeleteButton);
        Fl_Group::current()->resizable(o);
      }
      { Fl_Button* o = favDownButton = new Fl_Button(320, 80, 25, 25, "@2>");
        o->callback((Fl_Callback*)cb_favDownButton);
      }
      o->end();
    }
    { Fl_Group* o = new Fl_Group(10, 113, 335, 29);
      { Fl_Button* o = favCancelButton = new Fl_Button(273, 115, 72, 25, "Cancel");
        o->callback((Fl_Callback*)cb_favCancelButton);
        favCancelButton->label(fl_cancel);
      }
      { Fl_Return_Button* o = favOkButton = new Fl_Return_Button(181, 115, 79, 25, "Save");
        o->callback((Fl_Callback*)cb_favOkButton);
        favOkButton->label(save_label);
      }
      { Fl_Box* o = new Fl_Box(10, 115, 161, 25);
        Fl_Group::current()->resizable(o);
      }
      o->end();
    }
    favWindow->label(manage_favorites_label);
    o->set_modal();
    o->size_range(181, 150);
    o->end();
  }
  callback_ = 0;
data_ = 0;
directory_[0] = 0;
window->size_range(window->w(), window->h(), Fl::w(), Fl::h());
type(t);
filter(p);
update_favorites();
value(d);
type(t);
int e;
prefs_.get("preview", e, 1);
preview(e);
}

Fl_File_Chooser::~Fl_File_Chooser() {
  Fl::remove_timeout((Fl_Timeout_Handler)previewCB, this);
delete window;
delete favWindow;
}

void Fl_File_Chooser::callback(void (*cb)(Fl_File_Chooser *, void *), void *d ) {
  callback_ = cb;
data_     = d;
}

void Fl_File_Chooser::color(Fl_Color c) {
  fileList->color(c);
}

Fl_Color Fl_File_Chooser::color() {
  return (fileList->color());
}

char * Fl_File_Chooser::directory() {
  return directory_;
}

const char * Fl_File_Chooser::filter() {
  return (fileList->filter());
}

int Fl_File_Chooser::filter_value() {
  return showChoice->value();
}

void Fl_File_Chooser::filter_value(int f) {
  showChoice->value(f);
showChoiceCB();
}

void Fl_File_Chooser::hide() {
  window->hide();
}

void Fl_File_Chooser::iconsize(uchar s) {
  fileList->iconsize(s);
}

uchar Fl_File_Chooser::iconsize() {
  return (fileList->iconsize());
}

void Fl_File_Chooser::label(const char *l) {
  window->label(l);
}

const char * Fl_File_Chooser::label() {
  return (window->label());
}

void Fl_File_Chooser::ok_label(const char *l) {
  okButton->label(l);
int w, h;
okButton->measure_label(w, h);
okButton->resize(cancelButton->x() - 50 - w, cancelButton->y(),
                 w + 40, 25);
okButton->parent()->init_sizes();
}

const char * Fl_File_Chooser::ok_label() {
  return (okButton->label());
}

void Fl_File_Chooser::show() {
  window->hotspot(fileList);
window->show();
Fl::flush();
fl_cursor(FL_CURSOR_WAIT);
rescan();
fl_cursor(FL_CURSOR_DEFAULT);
fileName->take_focus();
}

int Fl_File_Chooser::shown() {
  return window->shown();
}

void Fl_File_Chooser::textcolor(Fl_Color c) {
  fileList->textcolor(c);
}

Fl_Color Fl_File_Chooser::textcolor() {
  return (fileList->textcolor());
}

void Fl_File_Chooser::textfont(uchar f) {
  fileList->textfont(f);
}

uchar Fl_File_Chooser::textfont() {
  return (fileList->textfont());
}

void Fl_File_Chooser::textsize(uchar s) {
  fileList->textsize(s);
}

uchar Fl_File_Chooser::textsize() {
  return (fileList->textsize());
}

void Fl_File_Chooser::type(int t) {
  type_ = t;
if (t & MULTI)
  fileList->type(FL_MULTI_BROWSER);
else
  fileList->type(FL_HOLD_BROWSER);
if (t & CREATE)
  newButton->activate();
else
  newButton->deactivate();
if (t & DIRECTORY)
  fileList->filetype(Fl_File_Browser::DIRECTORIES);
else
  fileList->filetype(Fl_File_Browser::FILES);
}

int Fl_File_Chooser::type() {
  return (type_);
}

void * Fl_File_Chooser::user_data() const {
  return (data_);
}

void Fl_File_Chooser::user_data(void *d) {
  data_ = d;
}

int Fl_File_Chooser::visible() {
  return window->visible();
}

//
// End of "$Id$".
//
