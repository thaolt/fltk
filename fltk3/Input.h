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
// "$Id: Fl_Input.H 6699 2009-03-18 22:58:12Z engelsman $"
//
// Input header file for the Fast Light Tool Kit (FLTK).
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

/* \file
   Fl_Input widget . */

#ifndef Fl_Input_H
#define Fl_Input_H

#include "Input_.h"

/**
  This is the FLTK text input widget. It displays a single line
  of text and lets the user edit it. Normally it is drawn with an
  inset box and a white background. The text may contain any
  characters (even 0), and will correctly display anything, using
  ^X notation for unprintable control characters and \\nnn notation
  for unprintable characters with the high bit set. It assumes the
  font can draw any characters in the ISO-8859-1 character set.</P>
  
  <CENTER><TABLE border=1 WIDTH=90% summary="Fl_Input keyboard and mouse bindings.">
  
  <TR><TD WIDTH=200><B>Mouse button 1</B></TD><TD>Moves the cursor to
  this point. Drag selects characters.  Double click selects words.
  Triple click selects all text.  Shift+click extends the selection.
  When you select text it is automatically copied to the clipboard.
  </TD></TR>
  
  <TR><TD><B>Mouse button 2</B></TD><TD>Insert the clipboard at
  the point clicked.  You can also select a region and replace it with the
  clipboard by selecting the region with mouse button 2.
  </TD></TR>
  
  <TR><TD><B>Mouse button 3</B></TD><TD>Currently acts like button 1.</TD></TR>
  
  <TR><TD><B>Backspace</B></TD><TD>Deletes one character to the left, or
  deletes the selected region.</TD></TR>
  <TR><TD><B>Enter</B></TD><TD>May cause the callback, see when().</TD></TR>
  <TR><TD><B>^A or Home</B></TD><TD>Go to start of line.</TD></TR>
  <TR><TD><B>^B or Left</B></TD><TD>Move left</TD></TR>
  <TR><TD><B>^C</B></TD><TD>Copy the selection to the clipboard</TD></TR>
  <TR><TD><B>^D or Delete</B></TD><TD>Deletes one character to the right
  or deletes the selected region.</TD></TR>
  <TR><TD><B>^E or End</B></TD><TD>Go to the end of line.</TD></TR>
  <TR><TD><B>^F or Right</B></TD><TD>Move right</TD></TR>
  <TR><TD><B>^K</B></TD><TD>Delete to the end of line (next \\n character)
  or deletes a single \\n character.  These deletions are all concatenated
  into the clipboard.</TD></TR>
  <TR><TD><B>^N or Down</B></TD><TD>Move down (for Fl_Multiline_Input
  only, otherwise it moves to the next input field).</TD></TR>
  <TR><TD><B>^P or Up</B></TD><TD>Move up (for Fl_Multiline_Input only,
  otherwise it moves to the previous input field).</TD></TR>
  <TR><TD><B>^U</B></TD><TD>Delete everything.</TD></TR>
  <TR><TD><B>^V or ^Y</B></TD><TD>Paste the clipboard</TD></TR>
  <TR><TD><B>^X or ^W</B></TD><TD>Copy the region to the clipboard and
  delete it.</TD></TR>
  <TR><TD><B>^Z or ^_</B></TD><TD>Undo.  This is a single-level undo
  mechanism, but all adjacent deletions and insertions are concatenated
  into a single "undo".  Often this will undo a lot more than you
  expected.</TD></TR>
  <TR><TD><B>Shift+move</B></TD><TD>Move the cursor but also extend the
  selection.</TD></TR>
  
  <TR><TD><B>RightCtrl or
  <BR>Compose</B></TD><TD>
  \anchor Fl_Input_Compose_Character
  Start a compose-character
  sequence.  The next one or two keys typed define the character to
  insert (see table that follows.)
  
  <p>For instance, to type "�" type [compose][a]['] or [compose]['][a].
  
  <P>The character "nbsp" (non-breaking space) is typed by using
  [compose][space].
  
  <P>The single-character sequences may be followed by a space if
  necessary to remove ambiguity.  For instance, if you really want to
  type "�~" rather than "�" you must type [compose][a][space][~].
  
  <p>The same key may be used to "quote" control characters into the
  text.  If you need a ^Q character you can get one by typing
  [compose][Control+Q].
  
  <p>X may have a key on the keyboard
  defined as XK_Multi_key.  If so this key may be used as well
  as the right-hand control key.  You can set this up with the program
  xmodmap.
  
  <p>If your keyboard is set to support a foreign language you should
  also be able to type "dead key" prefix characters.  On X you will
  actually be able to see what dead key you typed, and if you then move
  the cursor without completing the sequence the accent will remain
  inserted.</TD></TR>
  </TABLE></CENTER>
  
  <!-- NEW PAGE -->
  <center><table border=1 summary="Character Composition Table">
  <caption align="top">Character Composition Table</caption>
  <tr>
  	<th>Keys</th><th>Char</th>
  	<th>Keys</th><th>Char</th>
  	<th>Keys</th><th>Char</th>
  	<th>Keys</th><th>Char</th>
  	<th>Keys</th><th>Char</th>
  	<th>Keys</th><th>Char</th>
  
  </tr><tr>
  	<td align=center>sp</td><td align=center><small>nbsp</small></td>
  	<td align=center>*</td><td align=center>�</td>
  	<td align=center>` A</td><td align=center>�</td>
  	<td align=center>D -</td><td align=center>�</td>
  	<td align=center>` a</td><td align=center>�</td>
  	<td align=center>d -</td><td align=center>�</td>
  </tr><tr>
  	<td align=center>!</td><td align=center>�</td>
  	<td align=center>+ -</td><td align=center>�</td>
  	<td align=center>' A</td><td align=center>�</td>
  	<td align=center>~ N</td><td align=center>�</td>
  	<td align=center>' a</td><td align=center>�</td>
  	<td align=center>~ n</td><td align=center>�</td>
  </tr><tr>
  	<td align=center>%</td><td align=center>�</td>
  	<td align=center>2</td><td align=center>�</td>
  	<td align=center>A ^</td><td align=center>�</td>
  	<td align=center>` O</td><td align=center>�</td>
  	<td align=center>^ a</td><td align=center>�</td>
  	<td align=center>` o</td><td align=center>�</td>
  </tr><tr>
  	<td align=center>#</td><td align=center>�</td>
  	<td align=center>3</td><td align=center>�</td>
  	<td align=center>~ A</td><td align=center>�</td>
  	<td align=center>' O</td><td align=center>�</td>
  	<td align=center>~ a</td><td align=center>�</td>
  	<td align=center>' o</td><td align=center>�</td>
  </tr><tr>
  	<td align=center>$</td><td align=center>�</td>
  	<td align=center>'</td><td align=center>�</td>
  	<td align=center>: A</td><td align=center>�</td>
  	<td align=center>^ O</td><td align=center>�</td>
  	<td align=center>: a</td><td align=center>�</td>
  	<td align=center>^ o</td><td align=center>�</td>
  </tr><tr>
  	<td align=center>y =</td><td align=center>�</td>
  	<td align=center>u</td><td align=center>�</td>
  	<td align=center>* A</td><td align=center>�</td>
  	<td align=center>~ O</td><td align=center>�</td>
  	<td align=center>* a</td><td align=center>�</td>
  	<td align=center>~ o</td><td align=center>�</td>
  </tr><tr>
  	<td align=center>|</td><td align=center>�</td>
  	<td align=center>p</td><td align=center>�</td>
  	<td align=center>A E</td><td align=center>�</td>
  	<td align=center>: O</td><td align=center>�</td>
  	<td align=center>a e</td><td align=center>�</td>
  	<td align=center>: o</td><td align=center>�</td>
  </tr><tr>
  	<td align=center>&</td><td align=center>�</td>
  	<td align=center>.</td><td align=center>�</td>
  	<td align=center>, C</td><td align=center>�</td>
  	<td align=center>x</td><td align=center>�</td>
  	<td align=center>, c</td><td align=center>�</td>
  	<td align=center>- :</td><td align=center>�</td>
  </tr><tr>
  	<td align=center>:</td><td align=center>�</td>
  	<td align=center>,</td><td align=center>�</td>
  	<td align=center>E `</td><td align=center>�</td>
  	<td align=center>O /</td><td align=center>�</td>
  	<td align=center>` e</td><td align=center>�</td>
  	<td align=center>o /</td><td align=center>�</td>
  </tr><tr>
  	<td align=center>c</td><td align=center>�</td>
  	<td align=center>1</td><td align=center>�</td>
  	<td align=center>' E</td><td align=center>�</td>
  	<td align=center>` U</td><td align=center>�</td>
  	<td align=center>' e</td><td align=center>�</td>
  	<td align=center>` u</td><td align=center>�</td>
  </tr><tr>
  	<td align=center>a</td><td align=center>�</td>
  	<td align=center>o</td><td align=center>�</td>
  	<td align=center>^ E</td><td align=center>�</td>
  	<td align=center>' U</td><td align=center>�</td>
  	<td align=center>^ e</td><td align=center>�</td>
  	<td align=center>' u</td><td align=center>�</td>
  </tr><tr>
  	<td align=center>&lt; &lt;</td><td align=center>�</td>
  	<td align=center>&gt; &gt;</td><td align=center>�</td>
  	<td align=center>: E</td><td align=center>�</td>
  	<td align=center>^ U</td><td align=center>�</td>
  	<td align=center>: e</td><td align=center>�</td>
  	<td align=center>^ u</td><td align=center>�</td>
  </tr><tr>
  	<td align=center>~</td><td align=center>�</td>
  	<td align=center>1 4</td><td align=center>�</td>
  	<td align=center>` I</td><td align=center>�</td>
  	<td align=center>: U</td><td align=center>�</td>
  	<td align=center>` i</td><td align=center>�</td>
  	<td align=center>: u</td><td align=center>�</td>
  </tr><tr>
  	<td align=center>-</td><td align=center>�</td>
  	<td align=center>1 2</td><td align=center>�</td>
  	<td align=center>' I</td><td align=center>�</td>
  	<td align=center>' Y</td><td align=center>�</td>
  	<td align=center>' i</td><td align=center>�</td>
  	<td align=center>' y</td><td align=center>�</td>
  </tr><tr>
  	<td align=center>r</td><td align=center>�</td>
  	<td align=center>3 4</td><td align=center>�</td>
  	<td align=center>^ I</td><td align=center>�</td>
  	<td align=center>T H</td><td align=center>�</td>
  	<td align=center>^ i</td><td align=center>�</td>
  	<td align=center>t h</td><td align=center>�</td>
  </tr><tr>
  	<td align=center>_</td><td align=center>�</td>
  	<td align=center>?</td><td align=center>�</td>
  	<td align=center>: I</td><td align=center>�</td>
  	<td align=center>s s</td><td align=center>�</td>
  	<td align=center>: i</td><td align=center>�</td>
  	<td align=center>: y</td><td align=center>�</td>
  </tr>
  </table></center>
*/
class FL_EXPORT Fl_Input : public Fl_Input_ {
  int handle_key();
  int shift_position(int p);
  int shift_up_down_position(int p);
  void handle_mouse(int keepmark=0);
protected:
  void draw();
public:
  int handle(int);
  Fl_Input(int,int,int,int,const char * = 0);
};

#endif 

//
// End of "$Id: Fl_Input.H 6699 2009-03-18 22:58:12Z engelsman $".
//

/* suggested twin class
// This is the Twin Class to fltk::Input
class Fl_Input : public fltk::Input {
public:
  Fl_Input(int x, int t, int w, int h, const char *label=0)
  : fltk::Input(x, y, w, h, label), compat_(FLTK1) { }
};
*/

// ----- FLTK1 -----------------------------------------------------------------
#if 0
//
// "$Id: Fl_Input.H 6699 2009-03-18 22:58:12Z engelsman $"
//
// Input header file for the Fast Light Tool Kit (FLTK).
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

/* \file
   Fl_Input widget . */

#ifndef Fl_Input_H
#define Fl_Input_H

#include "Fl_Input_.H"

/**
  This is the FLTK text input widget. It displays a single line
  of text and lets the user edit it. Normally it is drawn with an
  inset box and a white background. The text may contain any
  characters (even 0), and will correctly display anything, using
  ^X notation for unprintable control characters and \\nnn notation
  for unprintable characters with the high bit set. It assumes the
  font can draw any characters in the ISO-8859-1 character set.</P>
  
  <CENTER><TABLE border=1 WIDTH=90% summary="Fl_Input keyboard and mouse bindings.">
  
  <TR><TD WIDTH=200><B>Mouse button 1</B></TD><TD>Moves the cursor to
  this point. Drag selects characters.  Double click selects words.
  Triple click selects all text.  Shift+click extends the selection.
  When you select text it is automatically copied to the clipboard.
  </TD></TR>
  
  <TR><TD><B>Mouse button 2</B></TD><TD>Insert the clipboard at
  the point clicked.  You can also select a region and replace it with the
  clipboard by selecting the region with mouse button 2.
  </TD></TR>
  
  <TR><TD><B>Mouse button 3</B></TD><TD>Currently acts like button 1.</TD></TR>
  
  <TR><TD><B>Backspace</B></TD><TD>Deletes one character to the left, or
  deletes the selected region.</TD></TR>
  <TR><TD><B>Enter</B></TD><TD>May cause the callback, see when().</TD></TR>
  <TR><TD><B>^A or Home</B></TD><TD>Go to start of line.</TD></TR>
  <TR><TD><B>^B or Left</B></TD><TD>Move left</TD></TR>
  <TR><TD><B>^C</B></TD><TD>Copy the selection to the clipboard</TD></TR>
  <TR><TD><B>^D or Delete</B></TD><TD>Deletes one character to the right
  or deletes the selected region.</TD></TR>
  <TR><TD><B>^E or End</B></TD><TD>Go to the end of line.</TD></TR>
  <TR><TD><B>^F or Right</B></TD><TD>Move right</TD></TR>
  <TR><TD><B>^K</B></TD><TD>Delete to the end of line (next \\n character)
  or deletes a single \\n character.  These deletions are all concatenated
  into the clipboard.</TD></TR>
  <TR><TD><B>^N or Down</B></TD><TD>Move down (for Fl_Multiline_Input
  only, otherwise it moves to the next input field).</TD></TR>
  <TR><TD><B>^P or Up</B></TD><TD>Move up (for Fl_Multiline_Input only,
  otherwise it moves to the previous input field).</TD></TR>
  <TR><TD><B>^U</B></TD><TD>Delete everything.</TD></TR>
  <TR><TD><B>^V or ^Y</B></TD><TD>Paste the clipboard</TD></TR>
  <TR><TD><B>^X or ^W</B></TD><TD>Copy the region to the clipboard and
  delete it.</TD></TR>
  <TR><TD><B>^Z or ^_</B></TD><TD>Undo.  This is a single-level undo
  mechanism, but all adjacent deletions and insertions are concatenated
  into a single "undo".  Often this will undo a lot more than you
  expected.</TD></TR>
  <TR><TD><B>Shift+move</B></TD><TD>Move the cursor but also extend the
  selection.</TD></TR>
  
  <TR><TD><B>RightCtrl or
  <BR>Compose</B></TD><TD>
  \anchor Fl_Input_Compose_Character
  Start a compose-character
  sequence.  The next one or two keys typed define the character to
  insert (see table that follows.)
  
  <p>For instance, to type "�" type [compose][a]['] or [compose]['][a].
  
  <P>The character "nbsp" (non-breaking space) is typed by using
  [compose][space].
  
  <P>The single-character sequences may be followed by a space if
  necessary to remove ambiguity.  For instance, if you really want to
  type "�~" rather than "�" you must type [compose][a][space][~].
  
  <p>The same key may be used to "quote" control characters into the
  text.  If you need a ^Q character you can get one by typing
  [compose][Control+Q].
  
  <p>X may have a key on the keyboard
  defined as XK_Multi_key.  If so this key may be used as well
  as the right-hand control key.  You can set this up with the program
  xmodmap.
  
  <p>If your keyboard is set to support a foreign language you should
  also be able to type "dead key" prefix characters.  On X you will
  actually be able to see what dead key you typed, and if you then move
  the cursor without completing the sequence the accent will remain
  inserted.</TD></TR>
  </TABLE></CENTER>
  
  <!-- NEW PAGE -->
  <center><table border=1 summary="Character Composition Table">
  <caption align="top">Character Composition Table</caption>
  <tr>
  	<th>Keys</th><th>Char</th>
  	<th>Keys</th><th>Char</th>
  	<th>Keys</th><th>Char</th>
  	<th>Keys</th><th>Char</th>
  	<th>Keys</th><th>Char</th>
  	<th>Keys</th><th>Char</th>
  
  </tr><tr>
  	<td align=center>sp</td><td align=center><small>nbsp</small></td>
  	<td align=center>*</td><td align=center>�</td>
  	<td align=center>` A</td><td align=center>�</td>
  	<td align=center>D -</td><td align=center>�</td>
  	<td align=center>` a</td><td align=center>�</td>
  	<td align=center>d -</td><td align=center>�</td>
  </tr><tr>
  	<td align=center>!</td><td align=center>�</td>
  	<td align=center>+ -</td><td align=center>�</td>
  	<td align=center>' A</td><td align=center>�</td>
  	<td align=center>~ N</td><td align=center>�</td>
  	<td align=center>' a</td><td align=center>�</td>
  	<td align=center>~ n</td><td align=center>�</td>
  </tr><tr>
  	<td align=center>%</td><td align=center>�</td>
  	<td align=center>2</td><td align=center>�</td>
  	<td align=center>A ^</td><td align=center>�</td>
  	<td align=center>` O</td><td align=center>�</td>
  	<td align=center>^ a</td><td align=center>�</td>
  	<td align=center>` o</td><td align=center>�</td>
  </tr><tr>
  	<td align=center>#</td><td align=center>�</td>
  	<td align=center>3</td><td align=center>�</td>
  	<td align=center>~ A</td><td align=center>�</td>
  	<td align=center>' O</td><td align=center>�</td>
  	<td align=center>~ a</td><td align=center>�</td>
  	<td align=center>' o</td><td align=center>�</td>
  </tr><tr>
  	<td align=center>$</td><td align=center>�</td>
  	<td align=center>'</td><td align=center>�</td>
  	<td align=center>: A</td><td align=center>�</td>
  	<td align=center>^ O</td><td align=center>�</td>
  	<td align=center>: a</td><td align=center>�</td>
  	<td align=center>^ o</td><td align=center>�</td>
  </tr><tr>
  	<td align=center>y =</td><td align=center>�</td>
  	<td align=center>u</td><td align=center>�</td>
  	<td align=center>* A</td><td align=center>�</td>
  	<td align=center>~ O</td><td align=center>�</td>
  	<td align=center>* a</td><td align=center>�</td>
  	<td align=center>~ o</td><td align=center>�</td>
  </tr><tr>
  	<td align=center>|</td><td align=center>�</td>
  	<td align=center>p</td><td align=center>�</td>
  	<td align=center>A E</td><td align=center>�</td>
  	<td align=center>: O</td><td align=center>�</td>
  	<td align=center>a e</td><td align=center>�</td>
  	<td align=center>: o</td><td align=center>�</td>
  </tr><tr>
  	<td align=center>&</td><td align=center>�</td>
  	<td align=center>.</td><td align=center>�</td>
  	<td align=center>, C</td><td align=center>�</td>
  	<td align=center>x</td><td align=center>�</td>
  	<td align=center>, c</td><td align=center>�</td>
  	<td align=center>- :</td><td align=center>�</td>
  </tr><tr>
  	<td align=center>:</td><td align=center>�</td>
  	<td align=center>,</td><td align=center>�</td>
  	<td align=center>E `</td><td align=center>�</td>
  	<td align=center>O /</td><td align=center>�</td>
  	<td align=center>` e</td><td align=center>�</td>
  	<td align=center>o /</td><td align=center>�</td>
  </tr><tr>
  	<td align=center>c</td><td align=center>�</td>
  	<td align=center>1</td><td align=center>�</td>
  	<td align=center>' E</td><td align=center>�</td>
  	<td align=center>` U</td><td align=center>�</td>
  	<td align=center>' e</td><td align=center>�</td>
  	<td align=center>` u</td><td align=center>�</td>
  </tr><tr>
  	<td align=center>a</td><td align=center>�</td>
  	<td align=center>o</td><td align=center>�</td>
  	<td align=center>^ E</td><td align=center>�</td>
  	<td align=center>' U</td><td align=center>�</td>
  	<td align=center>^ e</td><td align=center>�</td>
  	<td align=center>' u</td><td align=center>�</td>
  </tr><tr>
  	<td align=center>&lt; &lt;</td><td align=center>�</td>
  	<td align=center>&gt; &gt;</td><td align=center>�</td>
  	<td align=center>: E</td><td align=center>�</td>
  	<td align=center>^ U</td><td align=center>�</td>
  	<td align=center>: e</td><td align=center>�</td>
  	<td align=center>^ u</td><td align=center>�</td>
  </tr><tr>
  	<td align=center>~</td><td align=center>�</td>
  	<td align=center>1 4</td><td align=center>�</td>
  	<td align=center>` I</td><td align=center>�</td>
  	<td align=center>: U</td><td align=center>�</td>
  	<td align=center>` i</td><td align=center>�</td>
  	<td align=center>: u</td><td align=center>�</td>
  </tr><tr>
  	<td align=center>-</td><td align=center>�</td>
  	<td align=center>1 2</td><td align=center>�</td>
  	<td align=center>' I</td><td align=center>�</td>
  	<td align=center>' Y</td><td align=center>�</td>
  	<td align=center>' i</td><td align=center>�</td>
  	<td align=center>' y</td><td align=center>�</td>
  </tr><tr>
  	<td align=center>r</td><td align=center>�</td>
  	<td align=center>3 4</td><td align=center>�</td>
  	<td align=center>^ I</td><td align=center>�</td>
  	<td align=center>T H</td><td align=center>�</td>
  	<td align=center>^ i</td><td align=center>�</td>
  	<td align=center>t h</td><td align=center>�</td>
  </tr><tr>
  	<td align=center>_</td><td align=center>�</td>
  	<td align=center>?</td><td align=center>�</td>
  	<td align=center>: I</td><td align=center>�</td>
  	<td align=center>s s</td><td align=center>�</td>
  	<td align=center>: i</td><td align=center>�</td>
  	<td align=center>: y</td><td align=center>�</td>
  </tr>
  </table></center>
*/
class FL_EXPORT Fl_Input : public Fl_Input_ {
  int handle_key();
  int shift_position(int p);
  int shift_up_down_position(int p);
  void handle_mouse(int keepmark=0);
protected:
  void draw();
public:
  int handle(int);
  Fl_Input(int,int,int,int,const char * = 0);
};

#endif 

//
// End of "$Id: Fl_Input.H 6699 2009-03-18 22:58:12Z engelsman $".
//
#endif
// ----- FLTK2 -----------------------------------------------------------------
#if 0
//
// "$Id: Input.h 4886 2006-03-30 09:55:32Z fabien $"
//
// One-line text input field.
//
// Copyright 1998-2006 by Bill Spitzak and others.
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
// Please report all bugs and problems to "fltk-bugs@fltk.org".
//

#ifndef fltk_Input_h
#define fltk_Input_h

#ifndef fltk_Widget_h
#include "Widget.h"
#endif

namespace fltk {

class FL_API Input : public Widget {
public:
  enum { // values for type()
    NORMAL	= 0,
    FLOAT_INPUT = 1,
    INT_INPUT	= 2,
    SECRET	= 3,
    MULTILINE	= 4,
    WORDWRAP	= 5
  };

  Input(int, int, int, int, const char* = 0);
  ~Input();
  static NamedStyle* default_style;

  void draw();
  void draw(const Rectangle&);
  int handle(int);
  int handle(int event, const Rectangle&);
  bool handle_key();

  bool text(const char*);
  bool text(const char*, int);
  bool static_text(const char*);
  bool static_text(const char*, int);
  const char* text() const {return text_;}
  char at(int i) const {return text_[i];}
#ifdef FLTK_1_WIDGET  // back-compatability section:
  char index(int i) const {return text_[i];}
#endif
#ifndef SKIP_DEPRECIATED
  bool value(const char* v) {return text(v);}
  bool value(const char* v, int n) {return text(v,n);}
  bool static_value(const char* v) {return static_text(v);}
  const char* value() const {return text_;}
#endif
  int size() const {return size_;}
  void reserve(int newsize);

  int position() const {return position_;}
  int mark() const {return mark_;}
  void position(int p, int m);
  void position(int p) {position(p, p);}
  void up_down_position(int position, bool extend);
  void mark(int m) { position(position(), m);}

  virtual bool replace(int, int, const char*, int);
  bool cut() {return replace(position(), mark(), 0, 0);}
  bool cut(int n) {return replace(position(), position()+n, 0, 0);}
  bool cut(int a, int b) {return replace(a, b, 0, 0);}
  bool insert(const char* t);
  bool insert(const char* t, int l){return replace(position_, mark_, t, l);}
  bool replace(int a, int b, char c) {return replace(a,b,&c,1);}
  bool copy(bool clipboard = true);
  bool undo();
  void maybe_do_callback();

  int word_start(int i) const;
  int word_end(int i) const;
  int line_start(int i) const;
  int line_end(int i) const;
  int mouse_position(const Rectangle&) const;
  int xscroll() const {return xscroll_;}
  int yscroll() const {return yscroll_;}

private:

  const char* text_;
  char* buffer;

  int size_;
  int bufsize;
  int position_;
  int mark_;
  int xscroll_, yscroll_;
  int mu_p;
  int label_width;

  const char* expand(const char*, char*, int) const;
  float expandpos(const char*, const char*, const char*, int*) const;
  void minimal_update(int, int);
  void minimal_update(int p);
  void erase_cursor_at(int p);

  void setfont() const;

  void shift_position(int p);
  void shift_up_down_position(int p);

};

}

#endif

//
// End of "$Id: Input.h 4886 2006-03-30 09:55:32Z fabien $".
//
#endif
// ----- END -------------------------------------------------------------------
//
// End of "$Id$"
//
