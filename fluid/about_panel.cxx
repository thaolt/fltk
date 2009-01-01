//
// "$Id$"
//
// About dialog for the Fast Light Tool Kit (FLTK).
//
// Copyright 1998-2009 by Bill Spitzak and others.
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

// generated by Fast Light User Interface Designer (fluid) version 1.0300

#include "about_panel.h"
void show_help(const char *name); 

Fl_Double_Window *about_panel=(Fl_Double_Window *)0;

#include <FL/Fl_Pixmap.H>
static const char *idata_fluid[] = {
"96 96 32 1",
" \tc None",
".\tc #000100",
"+\tc #031F3F",
"@\tc #00366C",
"#\tc #2E302D",
"$\tc #0058AC",
"%\tc #0060BF",
"&\tc #4E504D",
"*\tc #14659F",
"=\tc #006DDC",
"-\tc #2C7087",
";\tc #0080FF",
">\tc #407B74",
",\tc #0F85F9",
"\'\tc #268CCD",
")\tc #7C7E7B",
"!\tc #2D92EC",
"~\tc #4498A9",
"{\tc #2F94FE",
"]\tc #5BA18C",
"^\tc #6BA674",
"/\tc #7DAD62",
"(\tc #93BD53",
"_\tc #A4A6A2",
":\tc #6CB6FF",
"<\tc #ABCC3F",
"[\tc #C4DA2A",
"}\tc #CACCC9",
"|\tc #DCE913",
"1\tc #BBDEFF",
"2\tc #FDFE00",
"3\tc #FDFFFC",
"                                                                             \
                   ",
"                                                                             \
                   ",
"                                                                             \
                   ",
"                                           ...........                       \
                   ",
"                                     ......................                  \
                   ",
"                                    ........................                 \
                   ",
"                                    ........#&#&#&#&##......                 \
                   ",
"                                    ....)__}33333333333}_...                 \
                   ",
"                                    ...&33333333333333333...                 \
                   ",
"                                    ...#33311133333333333...                 \
                   ",
"                                    ...&33!,{,;:333333333...                 \
                   ",
"                                    ...&3:,{{{{,13333333}...                 \
                   ",
"                                    ...&3!{{!{{,13333333}...                 \
                   ",
"                                    ...&3:!{{!{;13333333}...                 \
                   ",
"                                    ...&3{{{{{{;133333333...                 \
                   ",
"                                    ...&31,{{{;,33333333}...                 \
                   ",
"                                    ...&331{{{:133333333}...                 \
                   ",
"                                    ...&3333333333333333_...                 \
                   ",
"                                    ...&3333333333333333}...                 \
                   ",
"                                    ...&3333333333333333_...                 \
                   ",
"                                    ...&3333333333333333}...                 \
                   ",
"                                    ...&3333333333333333_...                 \
                   ",
"                                    ...&3333333333333333}...                 \
                   ",
"                                    ...&3333333333333333_...                 \
                   ",
"                                    ...&3333333331!,,;:3}...                 \
                   ",
"                                    ...&333333333{{{{{;:_...                 \
                   ",
"                                    ...&333333331,{!{!{{}...                 \
                   ",
"                                    ...&333333331{{{{{{,_...                 \
                   ",
"                                    ...)333333331{{!{{{{_...                 \
                   ",
"                                    ...)333333333{{{!{;:_...                 \
                   ",
"                                    ...)3333333331{;;;:3_...                 \
                   ",
"                                    ...)3333333333331333_...                 \
                   ",
"                                    ...)3333333333333333_...                 \
                   ",
"                                    ...)3333333333333333_...                 \
                   ",
"                                    ..._3333333333333333_...                 \
                   ",
"                                    ..._3333333333333333_...                 \
                   ",
"                                    ..._3333333333333333_...                 \
                   ",
"                                    ..._3333333333333333}....                \
                   ",
"                                   ...._33333333333333333#...                \
                   ",
"                                  ....&333333333333333333_....               \
                   ",
"                                 ....&33333333333333333333)....              \
                   ",
"                                 ....333333333333333333333}&....             \
                   ",
"                                ...._33333333333333333333333....             \
                   ",
"                               ....&333333333331:11333333333_....            \
                   ",
"                              ....#33333333333:,,,;:333333333&....           \
                   ",
"                              ....}3333333333:,!{{{;1333333333&....          \
                   ",
"                             ....}33333333333{{{!{{,!3333333333....          \
                   ",
"                            ....)333333333333{{{{!{{{3333333333_....         \
                   ",
"                           ....#3333333333333!{{{{{,:33333333333&....        \
                   ",
"                           ...._33333333333331{{!{,;1333333333333#....       \
                   ",
"                          ...._333333333333333:;,;,13333333333333_....       \
                   ",
"                         ...._333333333333333333113333333333333333_....      \
                   ",
"                        ....&33333333333333333333333333331::1333333&....     \
                   ",
"                        ...._333333333333333333333333333{,{{;{133333#...     \
                   ",
"                       ...._3333333333333333333333333331,{!{{,:33333}....    \
                   ",
"                      ....&3333333333133333333333333333:{{{{{{:333333)....   \
                   ",
"                      ...#333333331{,,;:333333333333333:{!{!{{:3333333&....  \
                   ",
"                     ....}33333333,{{{{;:333333333333331,{!{{;:33333333#...  \
                   ",
"                    ...._333333331,!{!{{,333333333333333{,{{;{1333333333.... \
                   ",
"                   ....&3333333331{{{{{{{3333333333333333::::33333333333)....\
                   ",
"                  ....+!:::::::::{{{{!{{;::::::::::::::::::::::::::!:::::+...\
.                  ",
"                  ...+=;;;;;;;;;;;;{{{{;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;=...\
.                  ",
"                 ....%;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;%..\
..                 ",
"                ....@;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;$.\
...                ",
"                ...+%;;;;;;!!!;;;;;,;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;!=;;;+\
....               ",
"               ....%;;;;;!([<|^~]^([%;;;;;;;;;;;;;;;;;,(<\'=;;;;;;;!^/<[|\'=;\
;=+...               ",
"              ....$;;;;;\'|2>]22<|22[%=;;;;;;;;;;;;;;;;^22[%=;;;;;;!][22|%=;;\
;$....              ",
"             ....@;;;;;;[2[%^2|*[22(%=;;;;;;;;;;;;;;;,/22|$=;;;;;;;;<22<%=;;;\
;$....             ",
"            ....+=;;;;;~22^$%]~$|22>%=;;;;;;;;;;;;;;;;\'||^%=;;;;;;;,[22^$=;;\
;;;+....            ",
"            ....%;;;;;,[22-%===\'22|*==;;;;;;;;;;;;;;;;;;=%=;;;;;;;;\'22|*%=;\
;;;;=+...            ",
"           ....$;;;;;;!22|$%;,;^22<$=;;;;;;;;;;;;;;;;;;===;;;;;;;;;^22|$==;;;\
;;;%....           ",
"          ....@;;;;;\'](22[^]=;;<22^$==!~]/~=;!]]~;;;;{\'~]==;;;;~<<]<22($=;;\
;;;;;;@....          ",
"         ....@;;;;;;]<|22|[<%;!|22-%\'[2222*=;/22(%;~|222(=;;;!<2|^[222>$=;;;\
;;;;;;+....         ",
"         ....=;;;;;;;,[22>$===~22|$==,[22[%=;[22]%=,!|22]%=;![2|*%]22|*==;;;;\
;;;;;%+...         ",
"        ....@;;;;;;;;!|22*$=;;/22($=;,[22/$=\'222*%=;!|22-%;;<22>%=]22[$%;;;;\
;;;;;;;=....        ",
"       ....@;;;;;;;;;~22[*==;;[22>%=;\'22|-%,^22[$=;,~22[$%;]22<$%=(22/$=;;;;\
;;;;;;;;@....       ",
"      ....+;;;;;;;;;;^22<$=;;!222*$=;]22[$==[22/$=;;(22/$=![22]$=;|22-%=;;;;;\
;;;;;;;;+...       ",
"      ....;;;;;;;;;;;<22^%=;;]22[$=;;(22/$=~222-%=;;[22>%=]22|$%;~22|$==;;;;;\
;;;;;;;;;....      ",
"     ....%;;;;;;;;;;;|22-%=;;(22/$=;{|22-%=<22|$%;;\'22|*%;<22<$==(22<$=;=;;;\
;;;;;;;;;;$....     ",
"    ....+;;;;;;;;;;;!222$==;,|22>%=;~22|$=]|22($=;;]22[$%,|22^%=!|22^$=;;;;;;\
;;;;;;;;;;@....    ",
"   ....+=;;;;;;;;;;;~22[$%;;\'22|*-/;]22($*[<22^$^=;(22/$(-222>$=(222->~;;;;;\
;;;;;;;;;;;=+....   ",
"   ...+;;;;;;;;;;;;;(22/$=;;]22|*<\'=(22/*[~[22>(]=;|22>//=|22/$^(|2|-[%=;;;;\
;;;;;;;;;;;;=....   ",
"  ....$;;;;;;;;;;;;;<22>%=;;]222|>==(222|^=|22|<%=;|222<%=(222|<-222|-==;;;;;\
;;;;;;;;;;;;$....  ",
" ....@;;;;;;;;;;;;;!|2|$=;;;\'[2[>%=;\'|2[]%=/2|/$==;^2|(*%=!(2|($%<2[-%=;;;;\
;;;;;;;;;;;;;;;@.... ",
"....@;;;;;;;;;;;;;;\'22($%;;;;=%%==;;;=%%%==;=%%==;;;=%===;;==%%====%%=,;;;;;\
;;;;;;;;;;;;;;;+... ",
"...+=;;;;;;;;;;!\'=,]22-%=;;;;;;==;=;;;===;=;;===;;;;;===;;;;=;=,;;,=;=;;;;;;\
;;;;;;;;;;;;;;;=....",
"...+;;;;;;;;;;;[2^=<2<$==;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;\
;;;;;;;;;;;;;;;+...",
"...+;;;;;;;;;;;22(\'2|*%=;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;\
;;;;;;;;;;;;;;;;+...",
"...+;;;;;;;;;;;^|<[[-%=;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;\
;;;;;;;;;;;;;;;+...",
"...+;;;;;;;;;;;;*~*%===;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;\
;;;;;;;;;;;;;;;@...",
"...+;;;;;;;;;;;;;====;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;\
;;;;;;;;;;;;;;;+...",
"....$=;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;\
;;;;;;;;;;;;;=$....",
" .....+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++\
+++++++++++++..... ",
" ............................................................................\
.................  ",
"  ...........................................................................\
.................  ",
"     ........................................................................\
..............     "
};
static Fl_Pixmap image_fluid(idata_fluid);

static void cb_View(Fl_Button*, void*) {
  show_help("license.html");
}

static void cb_Close(Fl_Return_Button* o, void*) {
  ((Fl_Window*)(o->parent()))->hide();
}

Fl_Double_Window* make_about_panel() {
  { about_panel = new Fl_Double_Window(315, 175, "About FLUID");
    about_panel->color(FL_LIGHT1);
    about_panel->selection_color(FL_DARK1);
    about_panel->hotspot(about_panel);
    { Fl_Box* o = new Fl_Box(10, 10, 115, 120);
      o->image(image_fluid);
    } // Fl_Box* o
    { Fl_Box* o = new Fl_Box(135, 10, 170, 69, "FLTK User\nInterface Designer\nVersion 1.3.0");
      o->color((Fl_Color)12);
      o->selection_color(FL_DARK1);
      o->labelfont(1);
      o->labelsize(18);
      o->align(FL_ALIGN_TOP_LEFT|FL_ALIGN_INSIDE);
    } // Fl_Box* o
    { Fl_Box* o = new Fl_Box(135, 89, 170, 42, "Copyright 1998-2009 by\nBill Spitzak and others");
      o->align(132|FL_ALIGN_INSIDE);
    } // Fl_Box* o
    { Fl_Button* o = new Fl_Button(89, 141, 123, 25, "View License...");
      o->labelcolor(FL_DARK_BLUE);
      o->callback((Fl_Callback*)cb_View);
    } // Fl_Button* o
    { Fl_Return_Button* o = new Fl_Return_Button(222, 141, 83, 25, "Close");
      o->callback((Fl_Callback*)cb_Close);
    } // Fl_Return_Button* o
    about_panel->set_non_modal();
    about_panel->end();
  } // Fl_Double_Window* about_panel
  return about_panel;
}

//
// End of "$Id$".
//
