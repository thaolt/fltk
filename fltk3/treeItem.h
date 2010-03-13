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
// "$Id: Fl_Tree_Item.H 6957 2009-12-08 08:39:31Z greg.ercolano $"
//

#ifndef FL_TREE_ITEM_H
#define FL_TREE_ITEM_H

#include <FL/Fl.H>
#include <FL/Fl_Widget.H>
#include <FL/Fl_Image.H>
#include <FL/fl_draw.H>

#include <FL/Fl_Tree_Item_Array.H>
#include <FL/Fl_Tree_Prefs.H>

//////////////////////
// FL/Fl_Tree_Item.H
//////////////////////
//
// Fl_Tree -- This file is part of the Fl_Tree widget for FLTK
// Copyright (C) 2009 by Greg Ercolano.
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

///
/// \file
/// \brief This file contains the definitions for Fl_Tree_Item
///

/// \brief Tree item
///
/// This class is a single tree item, and manages all of the item's attributes.
/// Fl_Tree_Item is used by Fl_Tree, which is comprised of many instances of Fl_Tree_Item.
///
/// Fl_Tree_Item is hierarchical; it dynamically manages an Fl_Tree_Item_Array of children
/// that are themselves instances of Fl_Tree_Item. Each item can have zero or more children.
/// When an item has children, close() and open() can be used to hide or show them.
///
/// Items have their own attributes; font size, face, color.
/// Items maintain their own hierarchy of children.
///
/// When you make changes to items, you'll need to tell the tree to redraw()
/// for the changes to show up.
///
class Fl_Tree_Item {
  const char             *_label;		// label (memory managed)
  int                     _labelfont;		// label's font face
  int                     _labelsize;		// label's font size
  Fl_Color                _labelfgcolor;	// label's fg color
  Fl_Color                _labelbgcolor;	// label's bg color
  char                    _open;		// item is open?
  char                    _visible;		// item is visible?
  char                    _active;		// item activated?
  char                    _selected;		// item selected?
  int                     _xywh[4];		// xywh of this widget (if visible)
  int                     _collapse_xywh[4];	// xywh of collapse icon (if any)
  int                     _label_xywh[4];	// xywh of label
  Fl_Widget              *_widget;		// item's label widget (optional)
  Fl_Image               *_usericon;		// item's user-specific icon (optional)
  Fl_Tree_Item_Array      _children;		// array of child items
  Fl_Tree_Item           *_parent;		// parent item (=0 if root)
  void                   *_userdata;    	// user data that can be associated with an item
protected:
  void show_widgets();
  void hide_widgets();
  void draw_vertical_connector(int x, int y1, int y2, const Fl_Tree_Prefs &prefs);
  void draw_horizontal_connector(int x1, int x2, int y, const Fl_Tree_Prefs &prefs);
public:
  Fl_Tree_Item(const Fl_Tree_Prefs &prefs);	// CTOR
  ~Fl_Tree_Item();				// DTOR
  Fl_Tree_Item(const Fl_Tree_Item *o);		// COPY CTOR
  void draw(int X, int &Y, int W, Fl_Widget *tree, const Fl_Tree_Prefs &prefs, int lastchild=1);
  void show_self(const char *indent = "") const;
  void label(const char *val);
  const char *label() const;

  /// Set a user-data value for the item.
  inline void user_data( void* data ) { _userdata = data; }

  /// Retrieve the user-data value that has been assigned to the item.
  inline void* user_data() const { return _userdata; }
  
  /// Set item's label font face.
  void labelfont(int val) {
    _labelfont = val; 
  }
  /// Get item's label font face.
  int labelfont() const {
    return(_labelfont);
  }
  /// Set item's label font size.
  void labelsize(int val) {
    _labelsize = val; 
  }
  /// Get item's label font size.
  int labelsize() const {
    return(_labelsize);
  }
  /// Set item's label foreground text color.
  void labelfgcolor(Fl_Color val) {
    _labelfgcolor = val; 
  }
  /// Set item's label text color.
  void labelcolor(Fl_Color val) {
    _labelfgcolor = val; 
  }
  /// Return item's label text color.
  Fl_Color labelcolor() const {
    return(_labelfgcolor); 
  }
  /// Return item's label foreground text color.
  Fl_Color labelfgcolor() const {
    return(_labelfgcolor); 
  }
  /// Set item's label background color.
  void labelbgcolor(Fl_Color val) {
    _labelbgcolor = val; 
  }
  /// Return item's background text color.
  Fl_Color labelbgcolor() const {
    return(_labelbgcolor); 
  }
  /// Assign an FLTK widget to this item.
  void widget(Fl_Widget *val) {
    _widget = val; 
  }
  /// Return FLTK widget assigned to this item.
  Fl_Widget *widget() const {
    return(_widget); 
  }
  /// Return the number of children this item has.
  int children() const {
    return(_children.total()); 
  }
  /// Return the child item for the given 'index'.
  Fl_Tree_Item *child(int index) {
    return(_children[index]); 
  }
  /// Return the const child item for the given 'index'.
  const Fl_Tree_Item *child(int t) const;
  /// See if this item has children.
  int has_children() const {
    return(children()); 
  }
  int find_child(const char *name);
  int find_child(Fl_Tree_Item *item);
  int remove_child(Fl_Tree_Item *item);
  int remove_child(const char *new_label);
  void clear_children();
  void swap_children(int ax, int bx);
  int swap_children(Fl_Tree_Item *a, Fl_Tree_Item *b);
  const Fl_Tree_Item *find_item(char **arr) const;
  Fl_Tree_Item *find_item(char **arr);
  //////////////////
  // Adding items
  //////////////////
  Fl_Tree_Item *add(const Fl_Tree_Prefs &prefs, const char *new_label);
  Fl_Tree_Item *add(const Fl_Tree_Prefs &prefs, char **arr);
  Fl_Tree_Item *insert(const Fl_Tree_Prefs &prefs, const char *new_label, int pos=0);
  Fl_Tree_Item *insert_above(const Fl_Tree_Prefs &prefs, const char *new_label);
  int depth() const;
  Fl_Tree_Item *prev();
  Fl_Tree_Item *next();
  
  /// Return the parent for this item.
  Fl_Tree_Item *parent() {
    return(_parent);
  }
  /// Return the const parent for this item.
  const Fl_Tree_Item *parent() const {
    return(_parent);
  }
  /// Set the parent for this item.
  /// Should only be used by Fl_Tree's internals.
  ///
  void parent(Fl_Tree_Item *val) {
    _parent = val;
  }
  //////////////////
  // State
  //////////////////
  void open();
  void close();
  /// See if the item is 'open'.
  int is_open() const {
    return(_open?1:0);
  }
  /// See if the item is 'closed'.
  int is_close() const {
    return(_open?0:1);
  }
  /// Toggle the item's open/closed state.
  void open_toggle() {
    _open?close():open();
  }
  /// Change the item's selection state to the optionally specified 'val'.
  /// If 'val' is not specified, the item will be selected.
  ///
  void select(int val=1) {
    _selected = val;
  }
  /// Toggle the item's selection state.
  void select_toggle() {
    if ( is_selected() ) {
      deselect();		// deselect if selected
    } else {
      select();		// select if deselected
    }
  }
  /// Select self and all children
  ///     Returns count of how many items were in the 'deselected' state,
  ///     ie. how many items were "changed".
  ///
  int select_all() {
    int count = 0;
    if ( ! is_selected() ) {
      select();
      ++count;
    }
    for ( int t=0; t<children(); t++ ) {
      count += child(t)->select_all();
    }
    return(count);
  }
  /// Disable the item's selection state.
  void deselect() {
    _selected = 0;
  }
  /// Deselect self and all children
  ///     Returns count of how many items were in the 'selected' state,
  ///     ie. how many items were "changed".
  ///
  int deselect_all() {
    int count = 0;
    if ( is_selected() ) {
      deselect();
      ++count;
    }
    for ( int t=0; t<children(); t++ ) {
      count += child(t)->deselect_all();
    }
    return(count);
  }
  /// See if the item is selected.
  char is_selected() const {
    return(_selected);
  }
  /// Change the item's activation state to the optionally specified 'val'.
  ///
  /// When deactivated, the item will be 'grayed out'; the callback() 
  /// won't be invoked if the user clicks on the label. If the item
  /// has a widget() associated with the item, its activation state
  /// will be changed as well.
  ///
  /// If 'val' is not specified, the item will be activated.
  ///
  void activate(int val=1) {
    _active = val;
    if ( _widget && val != (int)_widget->active() ) {
      if ( val ) {
	_widget->activate();
      } else {
	_widget->deactivate();
      }
      _widget->redraw();
    }
  }
  /// Deactivate the item; the callback() won't be invoked when clicked.
  /// Same as activate(0)
  ///
  void deactivate() {
    activate(0);
  }
  /// See if the item is activated.
  char is_activated() const {
    return(_active);
  }
  /// See if the item is activated.
  char is_active() const {
    return(_active);
  }
  /// Set the user icon's image. '0' will disable.
  void usericon(Fl_Image *val) {
    _usericon = val;
  }
  /// Get the user icon. Returns '0' if disabled.
  Fl_Image *usericon() const {
    return(_usericon);
  }
  //////////////////
  // Events
  //////////////////
  const Fl_Tree_Item *find_clicked(const Fl_Tree_Prefs &prefs) const;
  Fl_Tree_Item *find_clicked(const Fl_Tree_Prefs &prefs);
  int event_on_collapse_icon(const Fl_Tree_Prefs &prefs) const;
  int event_on_label(const Fl_Tree_Prefs &prefs) const;
  /// Is this item the root of the tree?
  int is_root() const {
    return(_parent==0?1:0);
  }
};

#endif /*FL_TREE_ITEM_H*/

//
// End of "$Id: Fl_Tree_Item.H 6957 2009-12-08 08:39:31Z greg.ercolano $".
//

/* suggested twin class
// This is the Twin Class to fltk::treeItem
class Fl_Tree_Item : public fltk::treeItem {
public:
  Fl_Tree_Item(int x, int t, int w, int h, const char *label=0)
  : fltk::treeItem(x, y, w, h, label), compat_(FLTK1) { }
};
*/

// ----- FLTK1 -----------------------------------------------------------------
#if 0
//
// "$Id: Fl_Tree_Item.H 6957 2009-12-08 08:39:31Z greg.ercolano $"
//

#ifndef FL_TREE_ITEM_H
#define FL_TREE_ITEM_H

#include <FL/Fl.H>
#include <FL/Fl_Widget.H>
#include <FL/Fl_Image.H>
#include <FL/fl_draw.H>

#include <FL/Fl_Tree_Item_Array.H>
#include <FL/Fl_Tree_Prefs.H>

//////////////////////
// FL/Fl_Tree_Item.H
//////////////////////
//
// Fl_Tree -- This file is part of the Fl_Tree widget for FLTK
// Copyright (C) 2009 by Greg Ercolano.
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

///
/// \file
/// \brief This file contains the definitions for Fl_Tree_Item
///

/// \brief Tree item
///
/// This class is a single tree item, and manages all of the item's attributes.
/// Fl_Tree_Item is used by Fl_Tree, which is comprised of many instances of Fl_Tree_Item.
///
/// Fl_Tree_Item is hierarchical; it dynamically manages an Fl_Tree_Item_Array of children
/// that are themselves instances of Fl_Tree_Item. Each item can have zero or more children.
/// When an item has children, close() and open() can be used to hide or show them.
///
/// Items have their own attributes; font size, face, color.
/// Items maintain their own hierarchy of children.
///
/// When you make changes to items, you'll need to tell the tree to redraw()
/// for the changes to show up.
///
class Fl_Tree_Item {
  const char             *_label;		// label (memory managed)
  int                     _labelfont;		// label's font face
  int                     _labelsize;		// label's font size
  Fl_Color                _labelfgcolor;	// label's fg color
  Fl_Color                _labelbgcolor;	// label's bg color
  char                    _open;		// item is open?
  char                    _visible;		// item is visible?
  char                    _active;		// item activated?
  char                    _selected;		// item selected?
  int                     _xywh[4];		// xywh of this widget (if visible)
  int                     _collapse_xywh[4];	// xywh of collapse icon (if any)
  int                     _label_xywh[4];	// xywh of label
  Fl_Widget              *_widget;		// item's label widget (optional)
  Fl_Image               *_usericon;		// item's user-specific icon (optional)
  Fl_Tree_Item_Array      _children;		// array of child items
  Fl_Tree_Item           *_parent;		// parent item (=0 if root)
  void                   *_userdata;    	// user data that can be associated with an item
protected:
  void show_widgets();
  void hide_widgets();
  void draw_vertical_connector(int x, int y1, int y2, const Fl_Tree_Prefs &prefs);
  void draw_horizontal_connector(int x1, int x2, int y, const Fl_Tree_Prefs &prefs);
public:
  Fl_Tree_Item(const Fl_Tree_Prefs &prefs);	// CTOR
  ~Fl_Tree_Item();				// DTOR
  Fl_Tree_Item(const Fl_Tree_Item *o);		// COPY CTOR
  void draw(int X, int &Y, int W, Fl_Widget *tree, const Fl_Tree_Prefs &prefs, int lastchild=1);
  void show_self(const char *indent = "") const;
  void label(const char *val);
  const char *label() const;

  /// Set a user-data value for the item.
  inline void user_data( void* data ) { _userdata = data; }

  /// Retrieve the user-data value that has been assigned to the item.
  inline void* user_data() const { return _userdata; }
  
  /// Set item's label font face.
  void labelfont(int val) {
    _labelfont = val; 
  }
  /// Get item's label font face.
  int labelfont() const {
    return(_labelfont);
  }
  /// Set item's label font size.
  void labelsize(int val) {
    _labelsize = val; 
  }
  /// Get item's label font size.
  int labelsize() const {
    return(_labelsize);
  }
  /// Set item's label foreground text color.
  void labelfgcolor(Fl_Color val) {
    _labelfgcolor = val; 
  }
  /// Set item's label text color.
  void labelcolor(Fl_Color val) {
    _labelfgcolor = val; 
  }
  /// Return item's label text color.
  Fl_Color labelcolor() const {
    return(_labelfgcolor); 
  }
  /// Return item's label foreground text color.
  Fl_Color labelfgcolor() const {
    return(_labelfgcolor); 
  }
  /// Set item's label background color.
  void labelbgcolor(Fl_Color val) {
    _labelbgcolor = val; 
  }
  /// Return item's background text color.
  Fl_Color labelbgcolor() const {
    return(_labelbgcolor); 
  }
  /// Assign an FLTK widget to this item.
  void widget(Fl_Widget *val) {
    _widget = val; 
  }
  /// Return FLTK widget assigned to this item.
  Fl_Widget *widget() const {
    return(_widget); 
  }
  /// Return the number of children this item has.
  int children() const {
    return(_children.total()); 
  }
  /// Return the child item for the given 'index'.
  Fl_Tree_Item *child(int index) {
    return(_children[index]); 
  }
  /// Return the const child item for the given 'index'.
  const Fl_Tree_Item *child(int t) const;
  /// See if this item has children.
  int has_children() const {
    return(children()); 
  }
  int find_child(const char *name);
  int find_child(Fl_Tree_Item *item);
  int remove_child(Fl_Tree_Item *item);
  int remove_child(const char *new_label);
  void clear_children();
  void swap_children(int ax, int bx);
  int swap_children(Fl_Tree_Item *a, Fl_Tree_Item *b);
  const Fl_Tree_Item *find_item(char **arr) const;
  Fl_Tree_Item *find_item(char **arr);
  //////////////////
  // Adding items
  //////////////////
  Fl_Tree_Item *add(const Fl_Tree_Prefs &prefs, const char *new_label);
  Fl_Tree_Item *add(const Fl_Tree_Prefs &prefs, char **arr);
  Fl_Tree_Item *insert(const Fl_Tree_Prefs &prefs, const char *new_label, int pos=0);
  Fl_Tree_Item *insert_above(const Fl_Tree_Prefs &prefs, const char *new_label);
  int depth() const;
  Fl_Tree_Item *prev();
  Fl_Tree_Item *next();
  
  /// Return the parent for this item.
  Fl_Tree_Item *parent() {
    return(_parent);
  }
  /// Return the const parent for this item.
  const Fl_Tree_Item *parent() const {
    return(_parent);
  }
  /// Set the parent for this item.
  /// Should only be used by Fl_Tree's internals.
  ///
  void parent(Fl_Tree_Item *val) {
    _parent = val;
  }
  //////////////////
  // State
  //////////////////
  void open();
  void close();
  /// See if the item is 'open'.
  int is_open() const {
    return(_open?1:0);
  }
  /// See if the item is 'closed'.
  int is_close() const {
    return(_open?0:1);
  }
  /// Toggle the item's open/closed state.
  void open_toggle() {
    _open?close():open();
  }
  /// Change the item's selection state to the optionally specified 'val'.
  /// If 'val' is not specified, the item will be selected.
  ///
  void select(int val=1) {
    _selected = val;
  }
  /// Toggle the item's selection state.
  void select_toggle() {
    if ( is_selected() ) {
      deselect();		// deselect if selected
    } else {
      select();		// select if deselected
    }
  }
  /// Select self and all children
  ///     Returns count of how many items were in the 'deselected' state,
  ///     ie. how many items were "changed".
  ///
  int select_all() {
    int count = 0;
    if ( ! is_selected() ) {
      select();
      ++count;
    }
    for ( int t=0; t<children(); t++ ) {
      count += child(t)->select_all();
    }
    return(count);
  }
  /// Disable the item's selection state.
  void deselect() {
    _selected = 0;
  }
  /// Deselect self and all children
  ///     Returns count of how many items were in the 'selected' state,
  ///     ie. how many items were "changed".
  ///
  int deselect_all() {
    int count = 0;
    if ( is_selected() ) {
      deselect();
      ++count;
    }
    for ( int t=0; t<children(); t++ ) {
      count += child(t)->deselect_all();
    }
    return(count);
  }
  /// See if the item is selected.
  char is_selected() const {
    return(_selected);
  }
  /// Change the item's activation state to the optionally specified 'val'.
  ///
  /// When deactivated, the item will be 'grayed out'; the callback() 
  /// won't be invoked if the user clicks on the label. If the item
  /// has a widget() associated with the item, its activation state
  /// will be changed as well.
  ///
  /// If 'val' is not specified, the item will be activated.
  ///
  void activate(int val=1) {
    _active = val;
    if ( _widget && val != (int)_widget->active() ) {
      if ( val ) {
	_widget->activate();
      } else {
	_widget->deactivate();
      }
      _widget->redraw();
    }
  }
  /// Deactivate the item; the callback() won't be invoked when clicked.
  /// Same as activate(0)
  ///
  void deactivate() {
    activate(0);
  }
  /// See if the item is activated.
  char is_activated() const {
    return(_active);
  }
  /// See if the item is activated.
  char is_active() const {
    return(_active);
  }
  /// Set the user icon's image. '0' will disable.
  void usericon(Fl_Image *val) {
    _usericon = val;
  }
  /// Get the user icon. Returns '0' if disabled.
  Fl_Image *usericon() const {
    return(_usericon);
  }
  //////////////////
  // Events
  //////////////////
  const Fl_Tree_Item *find_clicked(const Fl_Tree_Prefs &prefs) const;
  Fl_Tree_Item *find_clicked(const Fl_Tree_Prefs &prefs);
  int event_on_collapse_icon(const Fl_Tree_Prefs &prefs) const;
  int event_on_label(const Fl_Tree_Prefs &prefs) const;
  /// Is this item the root of the tree?
  int is_root() const {
    return(_parent==0?1:0);
  }
};

#endif /*FL_TREE_ITEM_H*/

//
// End of "$Id: Fl_Tree_Item.H 6957 2009-12-08 08:39:31Z greg.ercolano $".
//
#endif
// ----- FLTK2 -----------------------------------------------------------------
#if 0
#endif
// ----- END -------------------------------------------------------------------
//
// End of "$Id$"
//
