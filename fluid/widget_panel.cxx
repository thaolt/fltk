// generated by Fast Light User Interface Designer (fluid) version 2.1000

#include "widget_panel.h"
#include <fltk/xpmImage.h>
#include "FluidType.h"
#include "fluid_img.h"
#include "undo.h"

fltk::Window *widgetbin_panel=(fltk::Window *)0;

fltk::Window* make_widgetbin() {
  fltk::Window* w;
   {fltk::Window* o = widgetbin_panel = new fltk::Window(520, 85, "Widget Bin");
    w = o;
    o->shortcut(0xff1b);
    o->begin();
     {fltk::Group* o = new fltk::Group(3, 3, 79, 79);
      o->box(fltk::THIN_DOWN_BOX);
      o->begin();
       {fltk::Button* o = new fltk::Button(2, 2, 25, 25);
        o->box(fltk::THIN_UP_BOX);
        o->callback((fltk::Callback*)type_make_cb, (void*)("Function"));
        o->tooltip("Function");
        o->image(fluid_pixmap[7]);
      }
       {fltk::Button* o = new fltk::Button(27, 2, 25, 25);
        o->box(fltk::THIN_UP_BOX);
        o->callback((fltk::Callback*)type_make_cb, (void*)("class"));
        o->tooltip("Class");
        o->image(fluid_pixmap[12]);
      }
       {fltk::Button* o = new fltk::Button(52, 2, 25, 25);
        o->box(fltk::THIN_UP_BOX);
        o->callback((fltk::Callback*)type_make_cb, (void*)("comment"));
        o->tooltip("Comment");
        o->image(fluid_pixmap[46]);
      }
       {fltk::Button* o = new fltk::Button(2, 27, 25, 25);
        o->box(fltk::THIN_UP_BOX);
        o->callback((fltk::Callback*)type_make_cb, (void*)("code"));
        o->tooltip("Code");
        o->image(fluid_pixmap[8]);
      }
       {fltk::Button* o = new fltk::Button(27, 27, 25, 25);
        o->box(fltk::THIN_UP_BOX);
        o->callback((fltk::Callback*)type_make_cb, (void*)("codeblock"));
        o->tooltip("Code Block");
        o->image(fluid_pixmap[9]);
      }
       {fltk::Button* o = new fltk::Button(52, 27, 25, 25);
        o->box(fltk::THIN_UP_BOX);
        o->callback((fltk::Callback*)type_make_cb, (void*)("namespace"));
        o->tooltip("Namespace");
        o->image(fluid_pixmap[49]);
      }
       {fltk::Button* o = new fltk::Button(2, 52, 25, 25);
        o->box(fltk::THIN_UP_BOX);
        o->callback((fltk::Callback*)type_make_cb, (void*)("decl"));
        o->tooltip("Declaration");
        o->image(fluid_pixmap[10]);
      }
       {fltk::Button* o = new fltk::Button(27, 52, 25, 25);
        o->box(fltk::THIN_UP_BOX);
        o->callback((fltk::Callback*)type_make_cb, (void*)("declblock"));
        o->tooltip("Declaration Block");
        o->image(fluid_pixmap[11]);
      }
       {fltk::Button* o = new fltk::Button(52, 52, 25, 25);
        o->box(fltk::THIN_UP_BOX);
        o->callback((fltk::Callback*)type_make_cb, (void*)("WidgetClass"));
        o->tooltip("Namespace");
        o->image(fluid_pixmap[48]);
      }
      o->end();
    }
     {fltk::Group* o = new fltk::Group(83, 3, 79, 79);
      o->box(fltk::THIN_DOWN_BOX);
      o->begin();
       {fltk::Button* o = new fltk::Button(2, 2, 25, 25);
        o->box(fltk::THIN_UP_BOX);
        o->callback((fltk::Callback*)type_make_cb, (void*)("fltk::Window"));
        o->tooltip("Window");
        o->image(fluid_pixmap[1]);
      }
       {fltk::Button* o = new fltk::Button(27, 2, 25, 25);
        o->box(fltk::THIN_UP_BOX);
        o->callback((fltk::Callback*)type_make_cb, (void*)("fltk::Group"));
        o->tooltip("Group");
        o->image(fluid_pixmap[6]);
      }
       {fltk::Button* o = new fltk::Button(52, 2, 25, 25);
        o->box(fltk::THIN_UP_BOX);
        o->callback((fltk::Callback*)type_make_cb, (void*)("fltk::PackedGroup"));
        o->tooltip("Pack");
        o->image(fluid_pixmap[22]);
      }
       {fltk::Button* o = new fltk::Button(2, 27, 25, 25);
        o->box(fltk::THIN_UP_BOX);
        o->callback((fltk::Callback*)type_make_cb, (void*)("fltk::TabGroup"));
        o->tooltip("Tabs");
        o->image(fluid_pixmap[13]);
      }
       {fltk::Button* o = new fltk::Button(27, 27, 25, 25);
        o->box(fltk::THIN_UP_BOX);
        o->callback((fltk::Callback*)type_make_cb, (void*)("fltk::ScrollGroup"));
        o->tooltip("Scroll");
        o->image(fluid_pixmap[19]);
      }
       {fltk::Button* o = new fltk::Button(2, 52, 25, 25);
        o->box(fltk::THIN_UP_BOX);
        o->callback((fltk::Callback*)type_make_cb, (void*)("fltk::TiledGroup"));
        o->tooltip("Tile");
        o->image(fluid_pixmap[20]);
      }
       {fltk::Button* o = new fltk::Button(27, 52, 25, 25);
        o->box(fltk::THIN_UP_BOX);
        o->callback((fltk::Callback*)type_make_cb, (void*)("fltk::WizardGroup"));
        o->tooltip("Wizard");
        o->image(fluid_pixmap[21]);
      }
       {fltk::Button* o = new fltk::Button(52, 27, 25, 25);
        o->box(fltk::THIN_UP_BOX);
        o->callback((fltk::Callback*)type_make_cb, (void*)("fltk::StatusBarGroup"));
        o->tooltip("StatusBarGroup");
        o->image(fluid_pixmap[5]);
      }
      o->end();
    }
     {fltk::Group* o = new fltk::Group(163, 3, 54, 79);
      o->set_vertical();
      o->box(fltk::THIN_DOWN_BOX);
      o->begin();
       {fltk::Button* o = new fltk::Button(2, 2, 25, 25);
        o->box(fltk::THIN_UP_BOX);
        o->callback((fltk::Callback*)type_make_cb, (void*)("fltk::Button"));
        o->tooltip("Button");
        o->image(fluid_pixmap[2]);
      }
       {fltk::Button* o = new fltk::Button(27, 2, 25, 25);
        o->box(fltk::THIN_UP_BOX);
        o->callback((fltk::Callback*)type_make_cb, (void*)("fltk::ReturnButton"));
        o->tooltip("Return Button");
        o->image(fluid_pixmap[23]);
      }
       {fltk::Button* o = new fltk::Button(2, 27, 25, 25);
        o->box(fltk::THIN_UP_BOX);
        o->callback((fltk::Callback*)type_make_cb, (void*)("fltk::LightButton"));
        o->tooltip("Light Button");
        o->image(fluid_pixmap[24]);
      }
       {fltk::Button* o = new fltk::Button(27, 27, 25, 25);
        o->box(fltk::THIN_UP_BOX);
        o->callback((fltk::Callback*)type_make_cb, (void*)("fltk::RepeatButton"));
        o->tooltip("Repeat Button");
        o->image(fluid_pixmap[25]);
      }
       {fltk::Button* o = new fltk::Button(2, 52, 25, 25);
        o->box(fltk::THIN_UP_BOX);
        o->callback((fltk::Callback*)type_make_cb, (void*)("fltk::CheckButton"));
        o->tooltip("Check Button");
        o->image(fluid_pixmap[3]);
      }
       {fltk::Button* o = new fltk::Button(27, 52, 25, 25);
        o->box(fltk::THIN_UP_BOX);
        o->callback((fltk::Callback*)type_make_cb, (void*)("fltk::RadioButton"));
        o->tooltip("Round Button");
        o->image(fluid_pixmap[4]);
      }
      o->end();
    }
     {fltk::Group* o = new fltk::Group(218, 3, 104, 79);
      o->box(fltk::THIN_DOWN_BOX);
      o->begin();
       {fltk::Button* o = new fltk::Button(2, 2, 25, 25);
        o->box(fltk::THIN_UP_BOX);
        o->callback((fltk::Callback*)type_make_cb, (void*)("fltk::Slider"));
        o->tooltip("Slider");
        o->image(fluid_pixmap[37]);
      }
       {fltk::Button* o = new fltk::Button(27, 2, 25, 25);
        o->box(fltk::THIN_UP_BOX);
        o->callback((fltk::Callback*)type_make_cb, (void*)("fltk::Scrollbar"));
        o->tooltip("Scroll Bar");
        o->image(fluid_pixmap[38]);
      }
       {fltk::Button* o = new fltk::Button(52, 2, 25, 25);
        o->box(fltk::THIN_UP_BOX);
        o->callback((fltk::Callback*)type_make_cb, (void*)("fltk::ValueSlider"));
        o->tooltip("Value Slider");
        o->image(fluid_pixmap[39]);
      }
       {fltk::Button* o = new fltk::Button(77, 2, 25, 25);
        o->box(fltk::THIN_UP_BOX);
        o->callback((fltk::Callback*)type_make_cb, (void*)("fltk::ValueOutput"));
        o->tooltip("Value Output");
        o->image(fluid_pixmap[45]);
      }
       {fltk::Button* o = new fltk::Button(2, 27, 25, 25);
        o->box(fltk::THIN_UP_BOX);
        o->callback((fltk::Callback*)type_make_cb, (void*)("fltk::Adjuster"));
        o->tooltip("Adjuster");
        o->image(fluid_pixmap[40]);
      }
       {fltk::Button* o = new fltk::Button(27, 27, 25, 25);
        o->box(fltk::THIN_UP_BOX);
        o->callback((fltk::Callback*)type_make_cb, (void*)("fltk::ValueInput"));
        o->tooltip("Counter");
        o->image(fluid_pixmap[41]);
      }
       {fltk::Button* o = new fltk::Button(52, 27, 25, 25);
        o->box(fltk::THIN_UP_BOX);
        o->callback((fltk::Callback*)type_make_cb, (void*)("fltk::Dial"));
        o->tooltip("Dial");
        o->image(fluid_pixmap[42]);
      }
       {fltk::Button* o = new fltk::Button(2, 52, 25, 25);
        o->box(fltk::THIN_UP_BOX);
        o->callback((fltk::Callback*)type_make_cb, (void*)("fltk::ThumbWheel"));
        o->tooltip("ThumbWheel");
        o->image(fluid_pixmap[43]);
      }
       {fltk::Button* o = new fltk::Button(27, 52, 25, 25);
        o->box(fltk::THIN_UP_BOX);
        o->callback((fltk::Callback*)type_make_cb, (void*)("fltk::ValueInput"));
        o->tooltip("Spinner");
        o->image(fluid_pixmap[47]);
      }
       {fltk::Button* o = new fltk::Button(52, 52, 25, 25);
        o->box(fltk::THIN_UP_BOX);
        o->callback((fltk::Callback*)type_make_cb, (void*)("fltk::ValueInput"));
        o->tooltip("Value Input");
        o->image(fluid_pixmap[44]);
      }
      o->end();
    }
     {fltk::Group* o = new fltk::Group(323, 3, 54, 79);
      o->set_vertical();
      o->box(fltk::THIN_DOWN_BOX);
      o->begin();
       {fltk::Button* o = new fltk::Button(2, 2, 25, 25);
        o->box(fltk::THIN_UP_BOX);
        o->callback((fltk::Callback*)type_make_cb, (void*)("fltk::Input"));
        o->tooltip("Input");
        o->image(fluid_pixmap[14]);
      }
       {fltk::Button* o = new fltk::Button(27, 2, 25, 25);
        o->box(fltk::THIN_UP_BOX);
        o->callback((fltk::Callback*)type_make_cb, (void*)("fltk::Output"));
        o->tooltip("Output");
        o->image(fluid_pixmap[27]);
      }
       {fltk::Button* o = new fltk::Button(2, 27, 25, 25);
        o->box(fltk::THIN_UP_BOX);
        o->callback((fltk::Callback*)type_make_cb, (void*)("fltk::TextEditor"));
        o->tooltip("Text Edit");
        o->image(fluid_pixmap[29]);
      }
       {fltk::Button* o = new fltk::Button(27, 27, 25, 25);
        o->box(fltk::THIN_UP_BOX);
        o->callback((fltk::Callback*)type_make_cb, (void*)("fltk::TextDisplay"));
        o->tooltip("Text Display");
        o->image(fluid_pixmap[28]);
      }
       {fltk::Button* o = new fltk::Button(2, 52, 25, 25);
        o->box(fltk::THIN_UP_BOX);
        o->callback((fltk::Callback*)type_make_cb, (void*)("fltk::FileInput"));
        o->tooltip("File Input");
        o->image(fluid_pixmap[30]);
      }
      o->end();
    }
     {fltk::Group* o = new fltk::Group(378, 3, 54, 79);
      o->set_vertical();
      o->box(fltk::THIN_DOWN_BOX);
      o->begin();
       {fltk::Button* o = new fltk::Button(2, 2, 25, 25);
        o->box(fltk::THIN_UP_BOX);
        o->callback((fltk::Callback*)type_make_cb, (void*)("fltk::MenuBar"));
        o->tooltip("Menu Bar");
        o->image(fluid_pixmap[17]);
      }
       {fltk::Button* o = new fltk::Button(27, 2, 25, 25);
        o->box(fltk::THIN_UP_BOX);
        o->callback((fltk::Callback*)type_make_cb, (void*)("fltk::InputBrowser"));
        o->tooltip("Input Browser");
        o->image(fluid_pixmap[15]);
      }
       {fltk::Button* o = new fltk::Button(2, 27, 25, 25);
        o->box(fltk::THIN_UP_BOX);
        o->callback((fltk::Callback*)type_make_cb, (void*)("fltk::PopupMenu"));
        o->tooltip("Menu Button");
        o->image(fluid_pixmap[26]);
      }
       {fltk::Button* o = new fltk::Button(27, 27, 25, 25);
        o->box(fltk::THIN_UP_BOX);
        o->callback((fltk::Callback*)type_make_cb, (void*)("fltk::Item"));
        o->tooltip("Menu Item");
        o->image(fluid_pixmap[16]);
      }
       {fltk::Button* o = new fltk::Button(2, 52, 25, 25);
        o->box(fltk::THIN_UP_BOX);
        o->callback((fltk::Callback*)type_make_cb, (void*)("fltk::Choice"));
        o->tooltip("Choice");
        o->image(fluid_pixmap[15]);
      }
       {fltk::Button* o = new fltk::Button(27, 52, 25, 25);
        o->box(fltk::THIN_UP_BOX);
        o->callback((fltk::Callback*)type_make_cb, (void*)("fltk::ItemGroup"));
        o->tooltip("Sub Menu");
        o->image(fluid_pixmap[18]);
      }
      o->end();
    }
     {fltk::Group* o = new fltk::Group(433, 3, 29, 79);
      o->set_vertical();
      o->box(fltk::THIN_DOWN_BOX);
      o->begin();
       {fltk::Button* o = new fltk::Button(2, 2, 25, 25);
        o->box(fltk::THIN_UP_BOX);
        o->callback((fltk::Callback*)type_make_cb, (void*)("fltk::Browser"));
        o->tooltip("Browser");
        o->image(fluid_pixmap[31]);
      }
       {fltk::Button* o = new fltk::Button(2, 27, 25, 25);
        o->box(fltk::THIN_UP_BOX);
        o->callback((fltk::Callback*)type_make_cb, (void*)("fltk::CheckBrowser"));
        o->tooltip("Check Browser");
        o->image(fluid_pixmap[32]);
      }
       {fltk::Button* o = new fltk::Button(2, 52, 25, 25);
        o->box(fltk::THIN_UP_BOX);
        o->callback((fltk::Callback*)type_make_cb, (void*)("fltk::FileBrowser"));
        o->tooltip("File Browser");
        o->image(fluid_pixmap[33]);
      }
      o->end();
    }
     {fltk::Group* o = new fltk::Group(463, 3, 54, 79);
      o->set_vertical();
      o->box(fltk::THIN_DOWN_BOX);
      o->begin();
       {fltk::Button* o = new fltk::Button(2, 2, 25, 25);
        o->box(fltk::THIN_UP_BOX);
        o->callback((fltk::Callback*)type_make_cb, (void*)("fltk::InvisibleBox"));
        o->tooltip("Box");
        o->image(fluid_pixmap[5]);
      }
       {fltk::Button* o = new fltk::Button(27, 2, 25, 25);
        o->box(fltk::THIN_UP_BOX);
        o->callback((fltk::Callback*)type_make_cb, (void*)("fltk::Clock"));
        o->tooltip("Clock");
        o->image(fluid_pixmap[34]);
      }
       {fltk::Button* o = new fltk::Button(2, 27, 25, 25);
        o->box(fltk::THIN_UP_BOX);
        o->callback((fltk::Callback*)type_make_cb, (void*)("fltk::HelpView"));
        o->tooltip("Help View");
        o->image(fluid_pixmap[35]);
      }
       {fltk::Button* o = new fltk::Button(2, 52, 25, 25);
        o->box(fltk::THIN_UP_BOX);
        o->callback((fltk::Callback*)type_make_cb, (void*)("fltk::ProgressBar"));
        o->tooltip("Progress");
        o->image(fluid_pixmap[36]);
      }
      o->end();
    }
    o->end();
    o->set_non_modal();
    o->resizable(o);
  }
  return  w;
}

void type_make_cb(fltk::Widget*w,void*d) {
  FluidType *t = FluidType::make((char*)d);
    if (t) {
      Undo::checkpoint();
      select_only(t);
      modflag = 1;
      t->open();
    }
}

fltk::TabGroup *panel_tabs=(fltk::TabGroup *)0;

fltk::Group *gInput=(fltk::Group *)0;

static fltk::Input *i_class_name=(fltk::Input *)0;

static fltk::Choice *m_subtype=(fltk::Choice *)0;

static fltk::Input *i_label=(fltk::Input *)0;

fltk::Group *gAlignment=(fltk::Group *)0;

fltk::CheckButton *include_image_button=(fltk::CheckButton *)0;

fltk::Widget *image_label=(fltk::Widget *)0;

fltk::Button *image_button=(fltk::Button *)0;

fltk::Group *gDimensions=(fltk::Group *)0;

fltk::ValueInput *widget_x=(fltk::ValueInput *)0;

fltk::ValueInput *widget_y=(fltk::ValueInput *)0;

fltk::ValueInput *widget_w=(fltk::ValueInput *)0;

fltk::ValueInput *widget_h=(fltk::ValueInput *)0;

fltk::CheckButton *set_xy=(fltk::CheckButton *)0;

fltk::Group *gValues=(fltk::Group *)0;

fltk::Group *gAttributes=(fltk::Group *)0;

static fltk::Group *BoxColor=(fltk::Group *)0;

static fltk::Group *ButtonBox=(fltk::Group *)0;

static fltk::Group *Labels=(fltk::Group *)0;

fltk::MultiLineInput *extra_code_input=(fltk::MultiLineInput *)0;

fltk::CheckButton *overlaybutton=(fltk::CheckButton *)0;

fltk::LightButton *wLiveMode=(fltk::LightButton *)0;

fltk::Window* make_widget_panel() {
  fltk::Window* w;
   {fltk::Window* o = new fltk::Window(380, 380);
    w = o;
    o->shortcut(0xff1b);
    ((fltk::Window*)(o))->hotspot(o);
    o->begin();
     {fltk::TabGroup* o = panel_tabs = new fltk::TabGroup(0, 0, 380, 340);
      o->callback((fltk::Callback*)propagate_tabs);
      o->begin();
       {fltk::Group* o = new fltk::Group(0, 20, 380, 320, "GUI");
        o->color((fltk::Color)0x14aef700);
        o->callback((fltk::Callback*)propagate_group);
        o->begin();
         {fltk::Group* o = gInput = new fltk::Group(80, 9, 290, 44);
          o->callback((fltk::Callback*)propagate_group);
          o->begin();
           {fltk::Input* o = i_class_name = new fltk::Input(0, 0, 170, 22, "Class");
            o->callback((fltk::Callback*)user_class_cb, (void*)(4));
            o->when(fltk::WHEN_CHANGED);
            o->tooltip("This allows you to name a user-defined class that this widget is an instance \
of, rather than an fltk built-in class. You will need to add a #include declar\
ation so that the definition of your class is included in the fluid output.");
          }
           {fltk::Choice* o = m_subtype = new fltk::Choice(170, 0, 120, 22);
            o->callback((fltk::Callback*)subtype_cb);
            o->tooltip("Selects a value for type() for this widget");
          }
           {fltk::Input* o = i_label = new fltk::Input(0, 22, 290, 22, "Label");
            o->callback((fltk::Callback*)label_cb);
            o->when(fltk::WHEN_CHANGED);
            o->tooltip("Text displayed on or next to the widget");
            o->take_focus();
          }
          o->end();
        }
         {fltk::Group* o = gAlignment = new fltk::Group(80, 54, 293, 22, "Alignment");
          o->callback((fltk::Callback*)propagate_group);
          o->align(fltk::ALIGN_LEFT);
          o->begin();
           {fltk::CheckButton* o = include_image_button = new fltk::CheckButton(272, 0, 20, 22, "inline");
            o->set_vertical();
            o->callback((fltk::Callback*)image_inlined_cb);
            o->align(fltk::ALIGN_LEFT|fltk::ALIGN_CENTER|fltk::ALIGN_WRAP);
            o->tooltip("The image data is inserted as inline data into the output C++ code, rather th\
an generating code to read the image file.");
          }
           {fltk::Widget* o = new fltk::Widget(1, 0, 70, 22, "Alignment");
            o->box(fltk::NO_BOX);
            o->align(fltk::ALIGN_RIGHT|fltk::ALIGN_CENTER|fltk::ALIGN_INSIDE);
            o->hide();
          }
           {fltk::Button* o = new fltk::Button(0, 2, 20, 20, "@4->");
            o->type(fltk::Button::TOGGLE);
            o->labelsize(11);
            o->textsize(11);
            o->callback((fltk::Callback*)align_cb, (void*)(fltk::ALIGN_LEFT));
            o->tooltip("Places label on the left of the widget");
          }
           {fltk::Button* o = new fltk::Button(20, 2, 20, 20, "@6->");
            o->type(fltk::Button::TOGGLE);
            o->labelsize(11);
            o->textsize(11);
            o->callback((fltk::Callback*)align_cb, (void*)(fltk::ALIGN_RIGHT));
            o->tooltip("Places label on the right of the widget");
          }
           {fltk::Button* o = new fltk::Button(40, 2, 20, 20, "@8->");
            o->type(fltk::Button::TOGGLE);
            o->labelsize(11);
            o->textsize(11);
            o->callback((fltk::Callback*)align_cb, (void*)(fltk::ALIGN_TOP));
            o->tooltip("Places label on the top of the widget");
          }
           {fltk::Button* o = new fltk::Button(60, 2, 20, 20, "@2->");
            o->type(fltk::Button::TOGGLE);
            o->labelsize(11);
            o->textsize(11);
            o->callback((fltk::Callback*)align_cb, (void*)(fltk::ALIGN_BOTTOM));
            o->tooltip("Places label on the bottom of the widget");
          }
           {fltk::Button* o = new fltk::Button(91, 2, 40, 20, "inside");
            o->type(fltk::Button::TOGGLE);
            o->callback((fltk::Callback*)align_cb, (void*)(fltk::ALIGN_INSIDE));
            o->tooltip("Places label inside the widget");
          }
           {fltk::Button* o = new fltk::Button(131, 2, 40, 20, "clip");
            o->type(fltk::Button::TOGGLE);
            o->callback((fltk::Callback*)align_cb, (void*)(fltk::ALIGN_CLIP));
            o->tooltip("Turn on clipping to the widget's area when drawing label.  This is slower so \
it should be left off if label will fit");
          }
           {fltk::Button* o = new fltk::Button(171, 2, 40, 20, "wrap");
            o->type(fltk::Button::TOGGLE);
            o->callback((fltk::Callback*)align_cb, (void*)(fltk::ALIGN_WRAP));
            o->tooltip("Word-wrap the label");
          }
          o->end();
        }
         {fltk::Widget* o = image_label = new fltk::Widget(5, 79, 78, 22, "Image");
          o->box(fltk::NO_BOX);
          o->align(fltk::ALIGN_RIGHT|fltk::ALIGN_CENTER|fltk::ALIGN_INSIDE);
        }
         {fltk::Button* o = image_button = new fltk::Button(80, 79, 290, 22);
          o->color((fltk::Color)7);
          o->callback((fltk::Callback*)image_cb, (void*)(1));
          o->align(fltk::ALIGN_LEFT|fltk::ALIGN_CENTER|fltk::ALIGN_INSIDE|fltk::ALIGN_CLIP);
          o->tooltip("Select an image to label the widget");
        }
         {fltk::Group* o = gDimensions = new fltk::Group(80, 112, 290, 23, "Dimensions");
          o->callback((fltk::Callback*)propagate_group);
          o->align(fltk::ALIGN_LEFT);
          o->begin();
           {fltk::ValueInput* o = widget_x = new fltk::ValueInput(0, 0, 55, 22, "x");
            o->labelsize(11);
            o->maximum(2000);
            o->step(1);
            o->linesize(1);
            o->value(10);
            o->callback((fltk::Callback*)x_cb);
            o->align(fltk::ALIGN_TOP|fltk::ALIGN_LEFT|fltk::ALIGN_CENTER);
            o->when(fltk::WHEN_ENTER_KEY);
            o->tooltip("The x coordinate of the widget.");
          }
           {fltk::ValueInput* o = widget_y = new fltk::ValueInput(55, 0, 55, 22, "y");
            o->labelsize(11);
            o->maximum(2000);
            o->step(1);
            o->linesize(1);
            o->value(10);
            o->callback((fltk::Callback*)y_cb);
            o->align(fltk::ALIGN_TOP|fltk::ALIGN_LEFT|fltk::ALIGN_CENTER);
            o->when(fltk::WHEN_ENTER_KEY);
            o->tooltip("The y coordinate of the widget.");
          }
           {fltk::ValueInput* o = widget_w = new fltk::ValueInput(110, 0, 55, 22, "w");
            o->labelsize(11);
            o->maximum(2000);
            o->step(1);
            o->linesize(1);
            o->value(10);
            o->callback((fltk::Callback*)width_cb);
            o->align(fltk::ALIGN_TOP|fltk::ALIGN_LEFT|fltk::ALIGN_CENTER);
            o->when(fltk::WHEN_ENTER_KEY);
            o->tooltip("The width of the widget.");
          }
           {fltk::ValueInput* o = widget_h = new fltk::ValueInput(165, 0, 55, 22, "h");
            o->labelsize(11);
            o->maximum(2000);
            o->step(1);
            o->linesize(1);
            o->value(10);
            o->callback((fltk::Callback*)height_cb);
            o->align(fltk::ALIGN_TOP|fltk::ALIGN_LEFT|fltk::ALIGN_CENTER);
            o->when(fltk::WHEN_ENTER_KEY);
            o->tooltip("The height of the widget.");
          }
           {fltk::CheckButton* o = set_xy = new fltk::CheckButton(225, 0, 25, 22, "xy");
            o->labelsize(11);
            o->callback((fltk::Callback*)set_xy_cb);
            o->align(fltk::ALIGN_TOP|fltk::ALIGN_LEFT);
            o->tooltip("Window will use this x,y rather than being positioned by the operating system\
.");
          }
           {fltk::ValueInput* o = new fltk::ValueInput(245, 0, 45, 22, "slider size");
            o->labelsize(11);
            o->linesize(1.20259e+09);
            o->callback((fltk::Callback*)slider_size_cb);
            o->align(fltk::ALIGN_TOP|fltk::ALIGN_CENTER);
            o->when(fltk::WHEN_ENTER_KEY);
            o->tooltip("The size of the scroller");
          }
          o->end();
        }
         {fltk::Group* o = gValues = new fltk::Group(80, 147, 290, 23, "Values");
          o->callback((fltk::Callback*)propagate_group);
          o->align(fltk::ALIGN_LEFT);
          o->begin();
           {fltk::ValueInput* o = new fltk::ValueInput(0, 0, 55, 22, "Value");
            o->linesize(1.20259e+09);
            o->callback((fltk::Callback*)value_cb);
            o->align(fltk::ALIGN_TOP|fltk::ALIGN_LEFT);
            o->when(fltk::WHEN_ENTER_KEY);
            o->tooltip("The initial value of this widget");
          }
           {fltk::ValueInput* o = new fltk::ValueInput(55, 0, 55, 22, "min");
            o->labelsize(11);
            o->linesize(1.20259e+09);
            o->callback((fltk::Callback*)min_cb);
            o->align(fltk::ALIGN_TOP|fltk::ALIGN_LEFT|fltk::ALIGN_CENTER);
            o->when(fltk::WHEN_ENTER_KEY);
            o->tooltip("The minimum value for this valuator");
          }
           {fltk::ValueInput* o = new fltk::ValueInput(110, 0, 55, 23, "max");
            o->labelsize(11);
            o->linesize(1.20259e+09);
            o->callback((fltk::Callback*)max_cb);
            o->align(fltk::ALIGN_TOP|fltk::ALIGN_LEFT|fltk::ALIGN_CENTER);
            o->when(fltk::WHEN_ENTER_KEY);
            o->tooltip("The maximum value for this valuator");
          }
           {fltk::ValueInput* o = new fltk::ValueInput(165, 0, 55, 22, "step");
            o->labelsize(11);
            o->linesize(1.20259e+09);
            o->callback((fltk::Callback*)step_cb);
            o->align(fltk::ALIGN_TOP|fltk::ALIGN_LEFT|fltk::ALIGN_CENTER);
            o->when(fltk::WHEN_ENTER_KEY);
            o->tooltip("step:\nRound all movements to multiples of this.\n");
          }
           {fltk::ValueInput* o = new fltk::ValueInput(245, 0, 45, 22, "line");
            o->labelsize(11);
            o->minimum(1);
            o->step(1);
            o->linesize(1);
            o->callback((fltk::Callback*)line_cb);
            o->align(fltk::ALIGN_TOP|fltk::ALIGN_LEFT|fltk::ALIGN_CENTER);
            o->when(fltk::WHEN_ENTER_KEY);
            o->tooltip("linesize:\nIncrement/decrement for arrow keys.");
          }
          o->end();
        }
         {fltk::Group* o = gAttributes = new fltk::Group(80, 171, 280, 44, "Attributes");
          o->callback((fltk::Callback*)propagate_group);
          o->align(fltk::ALIGN_LEFT);
          o->begin();
           {fltk::CheckButton* o = new fltk::CheckButton(0, 0, 65, 22, "Visible");
            o->callback((fltk::Callback*)visible_cb);
            o->tooltip("If unchecked the widget is initially invisible.");
          }
           {fltk::CheckButton* o = new fltk::CheckButton(65, 0, 65, 22, "Active");
            o->callback((fltk::Callback*)active_cb);
            o->tooltip("If unchecked the widget is initially inactive (disabled, grayed out).");
          }
           {fltk::CheckButton* o = new fltk::CheckButton(130, 0, 80, 22, "Resizable");
            o->callback((fltk::Callback*)resizable_cb);
            o->tooltip("If on, this widget and all its parents are resizable.  When the parent resize\
s it moves/resizes all its children so that this widget's edges remain the sam\
e distance from all four sides of the parent.  If this is off this widget will\
 not resize, unless it overlaps a resizable sibling.");
          }
           {fltk::CheckButton* o = new fltk::CheckButton(210, 0, 70, 22, "Hotspot");
            o->callback((fltk::Callback*)hotspot_cb);
            o->tooltip("Positions the window so this widget is under the mouse.  This is done when sh\
ow() is called.");
          }
           {fltk::CheckButton* o = new fltk::CheckButton(0, 20, 65, 22, "Border");
            o->callback((fltk::Callback*)border_cb);
            o->tooltip("Enable the window manager border");
          }
           {fltk::CheckButton* o = new fltk::CheckButton(65, 20, 65, 22, "Modal");
            o->callback((fltk::Callback*)modal_cb);
            o->tooltip("This window will stay on top of others in the application and will block even\
ts from going to other windows until it is hidden or closed.");
          }
           {fltk::CheckButton* o = new fltk::CheckButton(130, 20, 65, 22, "Child");
            o->callback((fltk::Callback*)non_modal_cb);
            o->tooltip("This window will stay on top of others in the application.");
          }
          o->end();
        }
         {fltk::InvisibleBox* o = new fltk::InvisibleBox(25, 215, 55, 25, "Shortcut");
          o->align(fltk::ALIGN_RIGHT|fltk::ALIGN_INSIDE);
        }
         {Shortcut_Button* o = new Shortcut_Button(80, 216, 290, 22);
          o->color((fltk::Color)7);
          o->callback((fltk::Callback*)shortcut_in_cb);
          o->align(fltk::ALIGN_LEFT|fltk::ALIGN_INSIDE);
          o->tooltip("To set a shortcut:\n   Click here, then type the key combination you want.\nT\
o delete the shortcut:\n   Click here, then type backspace.\nTo get out of sho\
rtcut-setting mode:\n   Click the mouse on this again, or on some other field.");
        }
         {fltk::WordwrapInput* o = new fltk::WordwrapInput(80, 240, 290, 70, "Tooltip");
          o->type(5);
          o->box(fltk::BORDER_BOX);
          o->color((fltk::Color)0xffffe100);
          o->callback((fltk::Callback*)tooltip_cb);
          fltk::Group::current()->resizable(o);
          o->tooltip("The pop up tooltip which should be used for the widget.");
        }
        o->end();
      }
       {fltk::Group* o = new fltk::Group(0, 20, 380, 320, "Style");
        o->color((fltk::Color)0xd4b38d00);
        o->callback((fltk::Callback*)propagate_group);
        o->hide();
        o->begin();
         {fltk::Group* o = BoxColor = new fltk::Group(85, 9, 270, 66);
          o->callback((fltk::Callback*)propagate_group);
          o->begin();
           {fltk::Choice* o = new fltk::Choice(0, 0, 270, 22, "Box");
            o->callback((fltk::Callback*)box_cb);
            o->tooltip("Type of box to draw around the contents of the widget.");
          }
           {fltk::LightButton* o = new fltk::LightButton(0, 22, 135, 22, "Color");
            o->labelsize(11);
            o->textsize(11);
            o->callback((fltk::Callback*)color_cb);
            o->tooltip("Color of the contents area.");
            o->type(0);
          }
           {fltk::LightButton* o = new fltk::LightButton(135, 22, 135, 22, "Text Color");
            o->labelsize(11);
            o->textsize(11);
            o->callback((fltk::Callback*)text_color_cb);
            o->tooltip("Color of text drawn in the widget.");
            o->type(0);
          }
           {fltk::LightButton* o = new fltk::LightButton(0, 44, 135, 22, "Selection Color");
            o->labelsize(11);
            o->textsize(11);
            o->callback((fltk::Callback*)selection_color_cb);
            o->tooltip("Color to draw behind selected text");
            o->type(0);
          }
           {fltk::LightButton* o = new fltk::LightButton(135, 44, 135, 22, "Selected Text Color");
            o->labelsize(11);
            o->textsize(11);
            o->callback((fltk::Callback*)selected_text_color_cb);
            o->tooltip("Color to draw selected text");
            o->type(0);
          }
          o->end();
        }
         {fltk::Group* o = ButtonBox = new fltk::Group(85, 88, 270, 66);
          o->callback((fltk::Callback*)propagate_group);
          o->begin();
           {fltk::Choice* o = new fltk::Choice(0, 0, 270, 22, "Button box");
            o->callback((fltk::Callback*)button_box_cb);
            o->tooltip("Type of box to draw around buttons");
          }
           {fltk::LightButton* o = new fltk::LightButton(0, 22, 135, 22, "Button Color");
            o->labelsize(11);
            o->textsize(11);
            o->callback((fltk::Callback*)button_color_cb);
            o->tooltip("Color to draw buttons inside the widget.");
            o->type(0);
          }
           {fltk::LightButton* o = new fltk::LightButton(135, 22, 135, 22, "Label Color");
            o->labelsize(11);
            o->textsize(11);
            o->callback((fltk::Callback*)label_color_cb);
            o->tooltip("Color to draw the labels on buttons, and color to draw the label.");
            o->type(0);
          }
           {fltk::LightButton* o = new fltk::LightButton(0, 44, 135, 22, "Highlight Color");
            o->labelsize(11);
            o->textsize(11);
            o->callback((fltk::Callback*)highlight_color_cb);
            o->tooltip("Color to use to draw buttons when they are highlighted.  Use color zero (the \
black top-left chip in the color chooser) to disable highlighting.");
            o->type(0);
          }
           {fltk::LightButton* o = new fltk::LightButton(135, 44, 135, 22, "Highlight Label Color");
            o->labelsize(11);
            o->textsize(11);
            o->callback((fltk::Callback*)highlight_label_color_cb);
            o->tooltip("Color to draw the button labels when the buttons are highlighted.  Use color \
zero (the black top-left chip in the color chooser) to leave the label colors \
unchanged.");
            o->type(0);
          }
          o->end();
        }
         {fltk::Group* o = Labels = new fltk::Group(85, 165, 270, 80);
          o->callback((fltk::Callback*)propagate_group);
          o->begin();
           {fltk::Choice* o = new fltk::Choice(0, 0, 270, 22, "Label Style");
            o->callback((fltk::Callback*)label_style_cb);
            o->tooltip("How to draw the label.");
          }
           {fltk::Choice* o = new fltk::Choice(0, 22, 215, 22, "Label Font");
            o->callback((fltk::Callback*)label_font_cb);
            o->tooltip("Font to use for the label");
          }
           {fltk::ValueInput* o = new fltk::ValueInput(215, 22, 55, 22);
            o->maximum(100);
            o->step(0.1);
            o->linesize(1);
            o->value(14);
            o->callback((fltk::Callback*)label_size_cb);
            o->when(fltk::WHEN_ENTER_KEY);
            o->tooltip("Size of the font to use for the label");
          }
           {fltk::Choice* o = new fltk::Choice(0, 55, 215, 22, "Text Font");
            o->callback((fltk::Callback*)text_font_cb);
            o->tooltip("Font to use for text displayed inside the widget");
          }
           {fltk::ValueInput* o = new fltk::ValueInput(215, 55, 55, 22);
            o->maximum(100);
            o->step(0.1);
            o->linesize(1);
            o->value(14);
            o->callback((fltk::Callback*)text_size_cb);
            o->when(fltk::WHEN_ENTER_KEY);
            o->tooltip("Size of the font to use for text displayed inside the widget");
          }
           {fltk::Widget* o = new fltk::Widget(0, 77, 270, 3, "resizable");
            o->align(fltk::ALIGN_BOTTOM);
            o->hide();
            o->deactivate();
          }
          o->end();
        }
         {fltk::Button* o = new fltk::Button(85, 258, 124, 22, "Reset to default");
          o->callback((fltk::Callback*)default_cb);
          o->tooltip("Reset all the above items to the default values for this widget class.");
        }
         {fltk::InvisibleBox* o = new fltk::InvisibleBox(85, 280, 270, 25);
          fltk::Group::current()->resizable(o);
        }
        o->end();
      }
       {fltk::Group* o = new fltk::Group(0, 20, 380, 320, "C++");
        o->color((fltk::Color)0x93d49c00);
        o->callback((fltk::Callback*)propagate_group);
        o->hide();
        o->begin();
         {fltk::Input* o = new fltk::Input(80, 9, 230, 22, "Name");
          o->callback((fltk::Callback*)name_cb);
          o->when(fltk::WHEN_CHANGED);
          o->tooltip("The variable or member name in which to store a pointer to this widget.");
        }
         {fltk::CheckButton* o = new fltk::CheckButton(315, 9, 50, 22, "public");
          o->callback((fltk::Callback*)name_public_cb);
          o->tooltip("Make the variable public");
        }
         {fltk::MultiLineInput* o = extra_code_input = new fltk::MultiLineInput(80, 37, 285, 99, "Extra Code");
          o->type(4);
          o->callback((fltk::Callback*)extra_code_input_cb, (void*)(0));
          o->tooltip("Extra code to be exectuted after the widget is created. The variable \"o\" po\
ints at the widget.");
        }
         {fltk::MultiLineInput* o = new fltk::MultiLineInput(80, 143, 285, 99, "Callback");
          o->type(4);
          o->callback((fltk::Callback*)callback_cb);
          o->tooltip("The name of the callback function, or code body of the callback function");
        }
         {fltk::Widget* o = new fltk::Widget(80, 154, 165, 65, "resizable");
          o->hide();
          o->deactivate();
          fltk::Group::current()->resizable(o);
        }
         {fltk::Input* o = new fltk::Input(80, 242, 145, 22, "User Data");
          o->callback((fltk::Callback*)user_data_cb);
          o->tooltip("Value passed as the second argument to the callback.  This must be of the typ\
e given below.");
        }
         {fltk::Choice* o = new fltk::Choice(265, 242, 100, 22, "When");
          o->callback((fltk::Callback*)when_cb);
          o->when(fltk::WHEN_NEVER);
          o->tooltip("What actions cause the callback to be called.");
        }
         {fltk::Input* o = new fltk::Input(80, 264, 145, 22, "Type");
          o->callback((fltk::Callback*)user_data_type_cb);
          o->tooltip("Type of User Data. This must be \"long\" or a pointer.");
        }
        o->end();
        fltk::Group::current()->resizable(o);
      }
      o->end();
      fltk::Group::current()->resizable(o);
    }
     {fltk::Group* o = new fltk::Group(0, 350, 380, 24);
      o->begin();
       {fltk::CheckButton* o = overlaybutton = new fltk::CheckButton(20, 0, 120, 24, "&Overlays");
        o->callback((fltk::Callback*)overlay_cb);
        fltk::Group::current()->resizable(o);
        o->tooltip("Turns the overlays (red outlines) off so you can see the edges better.");
        o->value(!overlays_invisible);
      }
       {fltk::ReturnButton* o = new fltk::ReturnButton(235, 1, 65, 23, "OK");
        o->shortcut(0xff0d);
        o->callback((fltk::Callback*)ok_cb);
        o->tooltip("Closes this attribute window");
      }
       {fltk::Button* o = new fltk::Button(310, 1, 65, 23, "Cancel");
        o->callback((fltk::Callback*)cancel_cb);
        o->tooltip("Sorry, cancel does not really work yet.");
      }
       {fltk::LightButton* o = wLiveMode = new fltk::LightButton(95, 2, 90, 22, "LiveMode!");
        o->callback((fltk::Callback*)live_mode_cb);
      }
      o->end();
    }
    o->end();
  }
  return  w;
}
