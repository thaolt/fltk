//
// "$Id$"
//

// 123 TODO: remove stray comments
// 123 TODO: add namespace statements
// 123 TODO: replace class name, constructors and destructor
// 123 TODO: add friend statement for Twin Class
// 123 TODO: add 'compat(FLTK2)' to constructors
// 123 TODO: add twin class with all constructors
// 123 TODO: change all arguments to the FLTK2 class name
// 123 TODO: change the source code to use the new class names
// 123 TODO: add casting to return values
// 123 TODO: move all FLTK2-only functions to the FLTK3 section and implement them
// 123 TODO: remove the FLTK1 and FLTK2 sections in the headers
// 123 TODO: 

//
// "$Id: Fl_File_Input.H 6716 2009-03-24 01:40:44Z fabien $"
//
// File_Input header file for the Fast Light Tool Kit (FLTK).
//
// Copyright 1998-2009 by Bill Spitzak and others.
// Original version Copyright 1998 by Curtis Edwards.
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

/* \file
   Fl_File_Input widget . */

#ifndef Fl_File_Input_H
#  define Fl_File_Input_H

#  include <FL/Fl_Input.H>

/**
  \class Fl_File_Input
  \brief This widget displays a pathname in a text input field.

  A navigation bar located above the input field allows the user to
  navigate upward in the directory tree.
  You may want to handle FL_WHEN_CHANGED events for tracking text changes
  and also FL_WHEN_RELEASE for button release when changing to parent dir.
  FL_WHEN_RELEASE callback won't be called if the directory clicked 
  is the same that the current one.
  <P align=CENTER> \image html Fl_File_Input.gif </P> 
  \image latex Fl_File_Input.eps "Fl_File_Input"  width=6cm
  \note As all Fl_Input derived objects, Fl_File_Input may call its callback
  when loosing focus (see FL_UNFOCUS) to update its state like its cursor shape.
  One resulting side effect is that you should call clear_changed() early in your callback
  to avoid reentrant calls if you plan to show another window or dialog box in the callback.
*/
class FL_EXPORT Fl_File_Input : public Fl_Input
{
  Fl_Color	errorcolor_;
  char		ok_entry_;
  uchar		down_box_;
  short		buttons_[200];
  short		pressed_;

  void		draw_buttons();
  int		handle_button(int event);
  void		update_buttons();

public:

  Fl_File_Input(int X, int Y, int W, int H, const char *L=0);

  virtual int handle(int event);

protected:
  virtual void draw();

public:
  /** Gets the box type used for the navigation bar. */
  Fl_Boxtype	down_box() const { return (Fl_Boxtype)down_box_; }
  /** Sets the box type to use for the navigation bar.  */
  void		down_box(Fl_Boxtype b) { down_box_ = b; }

  /**
    Gets the current error color.
    \todo Better docs for Fl_File_Input::errorcolor() - is it even used?
  */
  Fl_Color	errorcolor() const { return errorcolor_; }
  /** Sets the current error color to \p c */
  void		errorcolor(Fl_Color c) { errorcolor_ = c; }

  int	value(const char *str);
  int	value(const char *str, int len);

  /**
    Returns the current value, which is a pointer to an internal buffer
    and is valid only until the next event is handled.
  */
  const char	*value() { return Fl_Input_::value(); }
};

#endif // !Fl_File_Input_H


//
// End of "$Id: Fl_File_Input.H 6716 2009-03-24 01:40:44Z fabien $".
//

/* suggested twin class
// This is the Twin Class to fltk::FileInput
class Fl_File_Input : public fltk::FileInput {
public:
  Fl_File_Input(int x, int t, int w, int h, const char *label=0)
  : fltk::FileInput(x, y, w, h, label), compat_(FLTK1) { }
};
*/

// ----- FLTK1 -----------------------------------------------------------------
#if 0
//
// "$Id: Fl_File_Input.H 6716 2009-03-24 01:40:44Z fabien $"
//
// File_Input header file for the Fast Light Tool Kit (FLTK).
//
// Copyright 1998-2009 by Bill Spitzak and others.
// Original version Copyright 1998 by Curtis Edwards.
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

/* \file
   Fl_File_Input widget . */

#ifndef Fl_File_Input_H
#  define Fl_File_Input_H

#  include <FL/Fl_Input.H>

/**
  \class Fl_File_Input
  \brief This widget displays a pathname in a text input field.

  A navigation bar located above the input field allows the user to
  navigate upward in the directory tree.
  You may want to handle FL_WHEN_CHANGED events for tracking text changes
  and also FL_WHEN_RELEASE for button release when changing to parent dir.
  FL_WHEN_RELEASE callback won't be called if the directory clicked 
  is the same that the current one.
  <P align=CENTER> \image html Fl_File_Input.gif </P> 
  \image latex Fl_File_Input.eps "Fl_File_Input"  width=6cm
  \note As all Fl_Input derived objects, Fl_File_Input may call its callback
  when loosing focus (see FL_UNFOCUS) to update its state like its cursor shape.
  One resulting side effect is that you should call clear_changed() early in your callback
  to avoid reentrant calls if you plan to show another window or dialog box in the callback.
*/
class FL_EXPORT Fl_File_Input : public Fl_Input
{
  Fl_Color	errorcolor_;
  char		ok_entry_;
  uchar		down_box_;
  short		buttons_[200];
  short		pressed_;

  void		draw_buttons();
  int		handle_button(int event);
  void		update_buttons();

public:

  Fl_File_Input(int X, int Y, int W, int H, const char *L=0);

  virtual int handle(int event);

protected:
  virtual void draw();

public:
  /** Gets the box type used for the navigation bar. */
  Fl_Boxtype	down_box() const { return (Fl_Boxtype)down_box_; }
  /** Sets the box type to use for the navigation bar.  */
  void		down_box(Fl_Boxtype b) { down_box_ = b; }

  /**
    Gets the current error color.
    \todo Better docs for Fl_File_Input::errorcolor() - is it even used?
  */
  Fl_Color	errorcolor() const { return errorcolor_; }
  /** Sets the current error color to \p c */
  void		errorcolor(Fl_Color c) { errorcolor_ = c; }

  int	value(const char *str);
  int	value(const char *str, int len);

  /**
    Returns the current value, which is a pointer to an internal buffer
    and is valid only until the next event is handled.
  */
  const char	*value() { return Fl_Input_::value(); }
};

#endif // !Fl_File_Input_H


//
// End of "$Id: Fl_File_Input.H 6716 2009-03-24 01:40:44Z fabien $".
//
#endif
// ----- FLTK2 -----------------------------------------------------------------
#if 0
//
// "$Id: FileInput.h 4886 2006-03-30 09:55:32Z fabien $"
//
// File_Input header file for the Fast Light Tool Kit (FLTK).
//
// Copyright 1998-2006 by Bill Spitzak and others.
// Original version Copyright 1998 by Curtis Edwards.
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

#ifndef fltk_FileInput_H
#  define fltk_FileInput_H

#  include "Input.h"

namespace fltk {

class FL_API FileInput : public Input {
  Color	errorcolor_;
  char		ok_entry_;
  short		buttons_[120];
  short		pressed_;

  void		draw_buttons();
  int		handle_button(int event);
  void		update_buttons();

public:

  FileInput(int,int,int,int,const char *t=0);

  void draw_boxes(bool pressed, const Rectangle& r);
  virtual int handle(int);
  virtual void draw();

  Color			errorcolor() const { return errorcolor_; }
  void			errorcolor(Color c) { errorcolor_ = c; }
  int			text(const char*);
  int			text(const char*, int);
  const char *		text() { return Input::text(); }
};

}
#endif // !Fl_File_Input_H


//
// End of "$Id: FileInput.h 4886 2006-03-30 09:55:32Z fabien $".
//
#endif
// ----- END -------------------------------------------------------------------
//
// End of "$Id$"
//
