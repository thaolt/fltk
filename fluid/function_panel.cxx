// generated by Fast Light User Interface Designer (fluid) version 0.99

#include "function_panel.H"

Fl_Window *function_panel;

Fl_Light_Button *f_public_button;

Fl_Input *f_name_input;

Fl_Input *f_return_type_input;

Fl_Return_Button *f_panel_ok;

Fl_Button *f_panel_cancel;

Fl_Window *code_panel;

Fl_Input *code_input;

Fl_Return_Button *code_panel_ok;

Fl_Button *code_panel_cancel;

Fl_Window *codeblock_panel;

Fl_Input *code_before_input;

Fl_Input *code_after_input;

Fl_Return_Button *codeblock_panel_ok;

Fl_Button *codeblock_panel_cancel;

Fl_Window *declblock_panel;

Fl_Input *decl_before_input;

Fl_Input *decl_after_input;

Fl_Return_Button *declblock_panel_ok;

Fl_Button *declblock_panel_cancel;

Fl_Window *decl_panel;

Fl_Light_Button *decl_public_button;

Fl_Input *decl_input;

Fl_Return_Button *decl_panel_ok;

Fl_Button *decl_panel_cancel;

Fl_Window *class_panel;

Fl_Light_Button *c_public_button;

Fl_Input *c_name_input;

Fl_Input *c_subclass_input;

Fl_Return_Button *c_panel_ok;

Fl_Button *c_panel_cancel;

Fl_Window* make_function_panel() {
  Fl_Window *w;
  { Fl_Window* o = new Fl_Window(287, 173, "function/method");
    w = function_panel = o;
    w->set_modal();
    { Fl_Light_Button* o = new Fl_Light_Button(10, 15, 65, 25, "public");
      f_public_button = o;
      o->labelsize(10);
      o->when(0);
    }
    { Fl_Input* o = new Fl_Input(10, 60, 270, 25, "name(args): (blank for main())");
      f_name_input = o;
      o->labelsize(12);
      o->align(5);
      o->when(0);
      Fl_Group::current()->resizable(o);
    }
    { Fl_Input* o = new Fl_Input(10, 105, 270, 25, "return type: (blank to return outermost widget)");
      f_return_type_input = o;
      o->labelsize(12);
      o->align(5);
      o->when(0);
    }
    { Fl_Return_Button* o = new Fl_Return_Button(110, 140, 80, 25, "OK");
      f_panel_ok = o;
      w->hotspot(o);
    }
    { Fl_Button* o = new Fl_Button(200, 140, 80, 25, "cancel");
      f_panel_cancel = o;
      o->shortcut(0xff1b);
    }
    w->end();
  }
  return w;
}

Fl_Window* make_code_panel() {
  Fl_Window *w;
  { Fl_Window* o = new Fl_Window(291, 178, "code");
    w = code_panel = o;
    w->set_modal();
    { Fl_Input* o = new Fl_Input(6, 5, 280, 135);
      code_input = o;
      o->type(4);
      o->labelsize(12);
      o->align(0);
      o->when(0);
      Fl_Group::current()->resizable(o);
    }
    { Fl_Return_Button* o = new Fl_Return_Button(115, 145, 80, 25, "OK");
      code_panel_ok = o;
      w->hotspot(o);
    }
    { Fl_Button* o = new Fl_Button(205, 145, 80, 25, "cancel");
      code_panel_cancel = o;
      o->shortcut(0xff1b);
    }
    w->end();
  }
  return w;
}

Fl_Window* make_codeblock_panel() {
  Fl_Window *w;
  { Fl_Window* o = new Fl_Window(293, 134, "codeblock");
    w = codeblock_panel = o;
    w->set_modal();
    { Fl_Input* o = new Fl_Input(10, 5, 275, 25);
      code_before_input = o;
      o->labelsize(12);
      o->align(5);
      o->when(0);
      Fl_Group::current()->resizable(o);
    }
    { Fl_Box* o = new Fl_Box(10, 35, 270, 25, "\"{...child code...}\" is inserted here");
      o->align(20);
    }
    { Fl_Input* o = new Fl_Input(10, 65, 275, 25);
      code_after_input = o;
      o->labelsize(12);
      o->align(5);
      o->when(0);
    }
    { Fl_Return_Button* o = new Fl_Return_Button(115, 100, 80, 25, "OK");
      codeblock_panel_ok = o;
      w->hotspot(o);
    }
    { Fl_Button* o = new Fl_Button(205, 100, 80, 25, "cancel");
      codeblock_panel_cancel = o;
      o->shortcut(0xff1b);
    }
    w->end();
  }
  return w;
}

Fl_Window* make_declblock_panel() {
  Fl_Window *w;
  { Fl_Window* o = new Fl_Window(293, 134, "declaration block");
    w = declblock_panel = o;
    w->set_modal();
    { Fl_Input* o = new Fl_Input(15, 10, 275, 25);
      decl_before_input = o;
      o->labelsize(12);
      o->align(5);
      o->when(0);
      Fl_Group::current()->resizable(o);
    }
    { Fl_Box* o = new Fl_Box(15, 40, 270, 25, "\"\\n...child code...\\n\" is inserted here");
      o->align(20);
    }
    { Fl_Input* o = new Fl_Input(15, 70, 275, 25);
      decl_after_input = o;
      o->labelsize(12);
      o->align(5);
      o->when(0);
    }
    { Fl_Return_Button* o = new Fl_Return_Button(120, 105, 80, 25, "OK");
      declblock_panel_ok = o;
      w->hotspot(o);
    }
    { Fl_Button* o = new Fl_Button(210, 105, 80, 25, "cancel");
      declblock_panel_cancel = o;
      o->shortcut(0xff1b);
    }
    w->end();
  }
  return w;
}

Fl_Window* make_decl_panel() {
  Fl_Window *w;
  { Fl_Window* o = new Fl_Window(290, 176, "declaration");
    w = decl_panel = o;
    { Fl_Light_Button* o = new Fl_Light_Button(10, 15, 65, 25, "public");
      decl_public_button = o;
      o->labelsize(10);
      o->when(0);
    }
    { Fl_Input* o = new Fl_Input(10, 50, 270, 25, "can be any declartion, like \"int x;\",\nan external symbol like \"extern \
int foo();\",\na #directive like \"#include <foo.h>\",\nor a comment like \"\
//foo\" or \"/*foo*/\"");
      decl_input = o;
      o->labelsize(12);
      o->align(6);
      o->when(0);
      Fl_Group::current()->resizable(o);
    }
    { Fl_Return_Button* o = new Fl_Return_Button(115, 145, 80, 25, "OK");
      decl_panel_ok = o;
      w->hotspot(o);
    }
    { Fl_Button* o = new Fl_Button(205, 145, 80, 25, "cancel");
      decl_panel_cancel = o;
      o->shortcut(0xff1b);
    }
    w->end();
  }
  return w;
}

Fl_Window* make_class_panel() {
  Fl_Window *w;
  { Fl_Window* o = new Fl_Window(287, 173, "class");
    w = class_panel = o;
    w->set_modal();
    { Fl_Light_Button* o = new Fl_Light_Button(10, 10, 65, 25, "public");
      c_public_button = o;
      o->labelsize(10);
      o->when(0);
    }
    { Fl_Input* o = new Fl_Input(10, 55, 270, 25, "name:");
      c_name_input = o;
      o->labelsize(12);
      o->align(5);
      o->when(0);
      Fl_Group::current()->resizable(o);
    }
    { Fl_Input* o = new Fl_Input(10, 100, 270, 25, "subclass of (text between : and {)");
      c_subclass_input = o;
      o->labelsize(12);
      o->align(5);
      o->when(0);
    }
    { Fl_Return_Button* o = new Fl_Return_Button(110, 135, 80, 25, "OK");
      c_panel_ok = o;
      w->hotspot(o);
    }
    { Fl_Button* o = new Fl_Button(200, 135, 80, 25, "cancel");
      c_panel_cancel = o;
      o->shortcut(0xff1b);
    }
    w->end();
  }
  return w;
}
