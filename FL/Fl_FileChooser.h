// generated by Fast Light User Interface Designer (fluid) version 1.00

#ifndef Fl_FileChooser_h
#define Fl_FileChooser_h
#include "Fl_FileBrowser.h"
#include "Fl_FileInput.h"
#include <FL/Fl.H>
#include <FL/Fl_Button.H>
#include <FL/Fl_Choice.H>
#include <FL/Fl_Return_Button.H>
#include <FL/Fl_Window.H>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

class Fl_FileChooser {
public:
  enum { SINGLE, MULTI, CREATE };
  Fl_FileChooser(const char *d, const char *p, int t, const char *title);
private:
  Fl_Window *window;
  inline void cb_window_i(Fl_Window*, void*);
  static void cb_window(Fl_Window*, void*);
  Fl_FileBrowser *fileList;
  inline void cb_fileList_i(Fl_FileBrowser*, void*);
  static void cb_fileList(Fl_FileBrowser*, void*);
  inline void cb_Cancel_i(Fl_Button*, void*);
  static void cb_Cancel(Fl_Button*, void*);
  Fl_Return_Button *okButton;
  inline void cb_okButton_i(Fl_Return_Button*, void*);
  static void cb_okButton(Fl_Return_Button*, void*);
  Fl_FileInput *fileName;
  inline void cb_fileName_i(Fl_FileInput*, void*);
  static void cb_fileName(Fl_FileInput*, void*);
  Fl_Button *upButton;
  inline void cb_upButton_i(Fl_Button*, void*);
  static void cb_upButton(Fl_Button*, void*);
  Fl_Button *newButton;
  inline void cb_newButton_i(Fl_Button*, void*);
  static void cb_newButton(Fl_Button*, void*);
  Fl_Choice *dirMenu;
  inline void cb_dirMenu_i(Fl_Choice*, void*);
  static void cb_dirMenu(Fl_Choice*, void*);
  inline void cb_allfiles_i(Fl_Button*, void*);
  static void cb_allfiles(Fl_Button*, void*);
  char directory_[1024];
  int type_;
  void fileListCB();
  void fileNameCB();
  void newdir();
  void up();
public:
  void color(Fl_Color c);
  Fl_Color color();
  int count();
  void directory(const char *d);
  char * directory();
  void filter(const char *p);
  const char * filter();
  void hide();
  void iconsize(uchar s);
  uchar iconsize();
  void label(const char *l);
  const char * label();
  void rescan();
  void show();
  void textcolor(Fl_Color c);
  Fl_Color textcolor();
  void textfont(Fl_Font f);
  Fl_Font textfont();
  void textsize(uchar s);
  uchar textsize();
  void type(int t);
  int type();
  const char *value(int f = 1);
  void value(const char *filename);
  int visible();
};
#endif
