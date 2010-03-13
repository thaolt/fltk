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
// "$Id: Fl_Plugin.H 6995 2010-01-12 08:48:55Z matt $"
//
// A Plugin system for FLTK, implemented in Fl_Preferences.cxx.
//
// Copyright 2002-2010 by Matthias Melcher.
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
   Fl_Plugin class . */

#ifndef Fl_Plugin_H
#  define Fl_Plugin_H

#  include "Preferences.h"


/**
 \brief Fl_Plugin allows link-time and run-time integration of binary modules.
 
 Fl_Plugin and Fl_Plugin_Manager provide a small and simple solution for
 linking C++ classes at run-time, or optionally linking modules at compile
 time without the need to change the main application.

 Fl_Plugin_Manager uses static initialisation to create the plugin interface
 early during startup. Plugins are stored in a temporary database, organized
 in classes.
 
 Plugins should derive a new class from Fl_Plugin as a base:
 \code
 class My_Plugin : public Fl_Plugin {
 public:
   My_Plugin() : Fl_Plugin("effects", "blur") { }
   void do_something(...);
 };
 My_Plugin blur_plugin();
 \endcode
 
 Plugins can be put into modules and either linked befor distribution, or loaded
 from dynamically linkable files. An Fl_Plugin_Manager is used to list and 
 access all currently loaded plugins.
 \code
 Fl_Plugin_Manager mgr("effects");
 int i, n = mgr.plugins();
 for (i=0; i<n; i++) {
   My_Plugin *pin = (My_Plugin*)mgr.plugin(i);
   pin->do_something();
 }
 \endcode
 */
class FL_EXPORT Fl_Plugin 
{
  Fl_Preferences::ID id;
public:
  Fl_Plugin(const char *klass, const char *name);
  virtual ~Fl_Plugin();
};


/**
 \brief Fl_Plugin_Manager manages link-time and run-time plugin binaries.
 \see Fl_Plugin
 */
class FL_EXPORT Fl_Plugin_Manager : public Fl_Preferences
{
public:
  Fl_Plugin_Manager(const char *klass);
  ~Fl_Plugin_Manager();
  
  /** \brief Return the number of plugins in the klass.
   */
  int plugins() { return groups(); }
  Fl_Plugin *plugin(int index);
  Fl_Plugin *plugin(const char *name);
  Fl_Preferences::ID addPlugin(const char *name, Fl_Plugin *plugin);
  
  static void removePlugin(Fl_Preferences::ID id);
  static int load(const char *filename);
  static int loadAll(const char *filepath, const char *pattern=0);
};


#endif // !Fl_Preferences_H

//
// End of "$Id: Fl_Preferences.H 6995 2010-01-12 08:48:55Z matt $".
//

/* suggested twin class
// This is the Twin Class to fltk::load_plugin
class Fl_Plugin : public fltk::load_plugin {
public:
  Fl_Plugin(int x, int t, int w, int h, const char *label=0)
  : fltk::load_plugin(x, y, w, h, label), compat_(FLTK1) { }
};
*/

// ----- FLTK1 -----------------------------------------------------------------
#if 0
//
// "$Id: Fl_Plugin.H 6995 2010-01-12 08:48:55Z matt $"
//
// A Plugin system for FLTK, implemented in Fl_Preferences.cxx.
//
// Copyright 2002-2010 by Matthias Melcher.
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
   Fl_Plugin class . */

#ifndef Fl_Plugin_H
#  define Fl_Plugin_H

#  include "Fl_Preferences.H"


/**
 \brief Fl_Plugin allows link-time and run-time integration of binary modules.
 
 Fl_Plugin and Fl_Plugin_Manager provide a small and simple solution for
 linking C++ classes at run-time, or optionally linking modules at compile
 time without the need to change the main application.

 Fl_Plugin_Manager uses static initialisation to create the plugin interface
 early during startup. Plugins are stored in a temporary database, organized
 in classes.
 
 Plugins should derive a new class from Fl_Plugin as a base:
 \code
 class My_Plugin : public Fl_Plugin {
 public:
   My_Plugin() : Fl_Plugin("effects", "blur") { }
   void do_something(...);
 };
 My_Plugin blur_plugin();
 \endcode
 
 Plugins can be put into modules and either linked befor distribution, or loaded
 from dynamically linkable files. An Fl_Plugin_Manager is used to list and 
 access all currently loaded plugins.
 \code
 Fl_Plugin_Manager mgr("effects");
 int i, n = mgr.plugins();
 for (i=0; i<n; i++) {
   My_Plugin *pin = (My_Plugin*)mgr.plugin(i);
   pin->do_something();
 }
 \endcode
 */
class FL_EXPORT Fl_Plugin 
{
  Fl_Preferences::ID id;
public:
  Fl_Plugin(const char *klass, const char *name);
  virtual ~Fl_Plugin();
};


/**
 \brief Fl_Plugin_Manager manages link-time and run-time plugin binaries.
 \see Fl_Plugin
 */
class FL_EXPORT Fl_Plugin_Manager : public Fl_Preferences
{
public:
  Fl_Plugin_Manager(const char *klass);
  ~Fl_Plugin_Manager();
  
  /** \brief Return the number of plugins in the klass.
   */
  int plugins() { return groups(); }
  Fl_Plugin *plugin(int index);
  Fl_Plugin *plugin(const char *name);
  Fl_Preferences::ID addPlugin(const char *name, Fl_Plugin *plugin);
  
  static void removePlugin(Fl_Preferences::ID id);
  static int load(const char *filename);
  static int loadAll(const char *filepath, const char *pattern=0);
};


#endif // !Fl_Preferences_H

//
// End of "$Id: Fl_Preferences.H 6995 2010-01-12 08:48:55Z matt $".
//
#endif
// ----- FLTK2 -----------------------------------------------------------------
#if 0
/*! \file
  This is a convienence function for portable loading of a plugin
  and possibly returing a symbol in that plugin. The function is
  \e not in the fltk namespace!
*/

#ifndef fl_load_plugin_h
#define fl_load_plugin_h

#include "FL_API.h"

FL_API void* load_plugin(const char* name, const char* symbol);

#endif
#endif
// ----- END -------------------------------------------------------------------
//
// End of "$Id$"
//
