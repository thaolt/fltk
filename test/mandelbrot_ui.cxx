// generated by Fast Light User Interface Designer (fluid) version 1.0300

#include "mandelbrot_ui.h"
#include <stdlib.h>

void Drawing_Window::cb_x_input_i(Fl_Input* o, void*) {
  d->X = atof(o->value());;
d->new_display();
}
void Drawing_Window::cb_x_input(Fl_Input* o, void* v) {
  ((Drawing_Window*)(o->parent()->user_data()))->cb_x_input_i(o,v);
}

void Drawing_Window::cb_y_input_i(Fl_Input* o, void*) {
  d->Y = atof(o->value());
d->new_display();
}
void Drawing_Window::cb_y_input(Fl_Input* o, void* v) {
  ((Drawing_Window*)(o->parent()->user_data()))->cb_y_input_i(o,v);
}

void Drawing_Window::cb_w_input_i(Fl_Input* o, void*) {
  d->scale = atof(o->value());
d->new_display();
}
void Drawing_Window::cb_w_input(Fl_Input* o, void* v) {
  ((Drawing_Window*)(o->parent()->user_data()))->cb_w_input_i(o,v);
}

void Drawing_Window::cb_brightness_i(Fl_Slider* o, void*) {
  d->brightness = int(o->value());
d->new_display();
}
void Drawing_Window::cb_brightness(Fl_Slider* o, void* v) {
  ((Drawing_Window*)(o->parent()->user_data()))->cb_brightness_i(o,v);
}

void Drawing_Window::cb_iterations_i(Fl_Slider* o, void*) {
  d->iterations = 1<<int(o->value());
d->new_display();
}
void Drawing_Window::cb_iterations(Fl_Slider* o, void* v) {
  ((Drawing_Window*)(o->parent()->user_data()))->cb_iterations_i(o,v);
}

void Drawing_Window::make_window() {
  { Fl_Double_Window* o = window = new Fl_Double_Window(450, 520);
    window->user_data((void*)(this));
    { d = new Drawing_Area(20, 80, 410, 430);
      d->box(FL_DOWN_BOX);
      d->color(FL_FOREGROUND_COLOR);
      d->selection_color(FL_DARK1);
      d->labeltype(FL_NORMAL_LABEL);
      d->labelfont(0);
      d->labelsize(14);
      d->labelcolor(FL_FOREGROUND_COLOR);
      d->user_data((void*)(this));
      d->align(Fl_Align(FL_ALIGN_CENTER));
      d->when(FL_WHEN_RELEASE);
      Fl_Group::current()->resizable(d);
    } // Drawing_Area* d
    { Fl_Input* o = x_input = new Fl_Input(30, 15, 125, 30, "x:");
      x_input->type(1);
      x_input->box(FL_THIN_DOWN_BOX);
      x_input->color(FL_INACTIVE_COLOR);
      x_input->selection_color(FL_BACKGROUND2_COLOR);
      x_input->labelfont(11);
      x_input->labelsize(20);
      x_input->textfont(11);
      x_input->textsize(20);
      x_input->callback((Fl_Callback*)cb_x_input);
      o->when(FL_WHEN_ENTER_KEY|FL_WHEN_RELEASE);
    } // Fl_Input* x_input
    { Fl_Input* o = y_input = new Fl_Input(175, 15, 125, 30, "y:");
      y_input->type(1);
      y_input->box(FL_THIN_DOWN_BOX);
      y_input->color(FL_INACTIVE_COLOR);
      y_input->selection_color(FL_BACKGROUND2_COLOR);
      y_input->labelfont(11);
      y_input->labelsize(20);
      y_input->textfont(11);
      y_input->textsize(20);
      y_input->callback((Fl_Callback*)cb_y_input);
      o->when(FL_WHEN_ENTER_KEY|FL_WHEN_RELEASE);
    } // Fl_Input* y_input
    { Fl_Input* o = w_input = new Fl_Input(325, 15, 105, 30, "w:");
      w_input->type(1);
      w_input->box(FL_THIN_DOWN_BOX);
      w_input->color(FL_INACTIVE_COLOR);
      w_input->selection_color(FL_BACKGROUND2_COLOR);
      w_input->labelfont(11);
      w_input->labelsize(20);
      w_input->textfont(11);
      w_input->textsize(20);
      w_input->callback((Fl_Callback*)cb_w_input);
      o->when(FL_WHEN_ENTER_KEY|FL_WHEN_RELEASE);
    } // Fl_Input* w_input
    { Fl_Slider* o = new Fl_Slider(80, 50, 160, 15, "brightness:");
      o->type(1);
      o->box(FL_THIN_DOWN_BOX);
      o->labelsize(10);
      o->step(1);
      o->slider_size(0.1);
      o->callback((Fl_Callback*)cb_brightness);
      o->align(Fl_Align(FL_ALIGN_LEFT));
      o->bounds(0,d->MAX_BRIGHTNESS);
      o->value(d->DEFAULT_BRIGHTNESS);
      o->slider(FL_UP_BOX);
    } // Fl_Slider* o
    { Fl_Box* o = new Fl_Box(240, 50, 190, 30, 
	    "left: click = zoom out, drag = zoom in\nright click: Julia set, ctrl-P: Print.");
      o->labelsize(10);
      o->align(Fl_Align(FL_ALIGN_RIGHT|FL_ALIGN_INSIDE));
      o->deactivate();
    } // Fl_Box* o
    { Fl_Slider* o = new Fl_Slider(80, 65, 160, 15, "iterations:");
      o->type(1);
      o->box(FL_THIN_DOWN_BOX);
      o->labelsize(10);
      o->step(1);
      o->slider_size(0.1);
      o->callback((Fl_Callback*)cb_iterations);
      o->align(Fl_Align(FL_ALIGN_LEFT));
      o->bounds(1,d->MAX_ITERATIONS);
      o->value(d->DEFAULT_ITERATIONS);
      o->slider(FL_UP_BOX);
    } // Fl_Slider* o
    o->size_range(220,220);
    window->end();
  } // Fl_Double_Window* window
}
