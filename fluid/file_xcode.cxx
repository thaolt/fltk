//
// "$Id: file_xcode.cxx 8870 2011-07-26 21:19:35Z matt $"
//
// Fluid file routines for the Fast Light Tool Kit (FLTK).
//
// You may find the basic read_* and write_* routines to
// be useful for other programs.  I have used them many times.
// They are somewhat similar to tcl, using matching { and }
// to quote strings.
//
// Copyright 1998-2010 by Bill Spitzak and others.
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

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include "Fl_Type.h"
#include "../fltk3/filename.h"

/*
 
 typedef enum {
 FL_FILE_DEFAULT = 0x8000,
 FL_FILE_UNKNOWN = 0,
 FL_FILE_C_SOURCE, FL_FILE_C_HEADER,
 FL_FILE_CPP_SOURCE, FL_FILE_CPP_HEADER,
 FL_FILE_OBJC_SOURCE, FL_FILE_OBJC_HEADER,
 FL_FILE_TEXT, FL_FILE_TEXT_SCRIPT
 } FileType;

lastKnownFileType  or  explicitFileType
 sourcecode.c.c
 sourcecode.c.h
 sourcecode.cpp.cpp
 sourcecode.cpp.objcpp
 sourcecode.cpp.h
 sourcecode.fluid (=text)
 text
 text.script.sh
 
 wrapper.framework
 wrapper.application
 "compiled.mach-o.dylib"
 
 */

// ------------ file conversion ------------------------------------------------

extern const char *filename;


static const char *xcode4_type(unsigned int ft) {
  static char buf[64];
  if (ft & FL_FILE_EXPLICIT) {
    strcpy(buf, "explicitFileType = ");
  } else {
    strcpy(buf, "lastKnownFileType = ");
  }
  switch (ft & 0x7fff) {
    case FL_FILE_C_SOURCE:     strcat(buf, "sourcecode.c.c"); break;
    case FL_FILE_C_HEADER:     strcat(buf, "sourcecode.c.h"); break;
    case FL_FILE_CPP_SOURCE:   strcat(buf, "sourcecode.cpp.cpp"); break;
    case FL_FILE_CPP_HEADER:   strcat(buf, "sourcecode.cpp.h"); break;
    case FL_FILE_OBJC_SOURCE:  strcat(buf, "sourcecode.cpp.objcpp"); break;
    case FL_FILE_OBJC_HEADER:  strcat(buf, "sourcecode.cpp.h"); break;
    case FL_FILE_TEXT:         strcat(buf, "text"); break;
    case FL_FILE_TEXT_SCRIPT:  strcat(buf, "text.script.sh"); break;
    default:                strcat(buf, "text"); break;
  }
  return buf;
}

int write_fltk_ide_xcode4() {
  // for now, we use a template project file. Eventually, the entire file will be generated
  //    template is ide/Xcode4/FLTK.xcodeproj/project.pbxproj.tmpl
  // destination is ide/Xcode4/FLTK.xcodeproj/project.pbxproj

  char buf[2048];
  strcpy(buf, filename);
  strcpy((char*)fltk3::filename_name(buf), "ide/Xcode4/FLTK.xcodeproj/project.pbxproj");
  FILE *out = fopen(buf, "wb");
  strcat(buf, ".tmpl");
  FILE *in = fopen(buf, "rb");
  
  for (;;) {
    if (fgets(buf, 2047, in)==0) // FIXME: handle error!
      break;
    char *hash = buf-1;
    char copyLine = 1;
    for (;;) {
      hash = strchr(hash+1, '#');
      if (!hash) break;
      if (hash && hash[1]=='#') { // double hash escapes the control character
        int n = strlen(hash);
        memmove(hash, hash+1, n);
        continue;
      } else { // single hash is a command
        copyLine = 0;
        if (strncmp(hash, "#BuildFileReferences(", 21)==0) {
          Fl_Type *tgt = Fl_Target_Type::find(hash+21, ')'); // keep tgt local
          if (!tgt) {
            printf("ERROR writing Xcode 4 file: target not found!");
            return -1;
          }
          Fl_File_Type *f;
          for (f = Fl_File_Type::first_file(tgt); f; f = f->next_file(tgt)) {
            if (f->builds_in(FL_ENV_XC4)) {
              char PBXBuildFile[32]; strcpy(PBXBuildFile, f->get_UUID_Xcode("Xcode4_PBXBuildFile"));
              char PBXFileRef[32]; strcpy(PBXFileRef, f->get_UUID_Xcode("Xcode4_PBXFileRef"));
              fprintf(out, "\t\t%s /* %s in %s */ = {isa = PBXBuildFile; fileRef = %s /* %s */; };\n", 
                      PBXBuildFile, 
                      f->filename_name(), 
                      "Sources", 
                      PBXFileRef, 
                      f->filename_name());
            }
          }
          hash = strchr(hash, ';')+1;
        } else if (strncmp(hash, "#FileReferences(", 16)==0) {
          Fl_Type *tgt = Fl_Target_Type::find(hash+16, ')');
          if (!tgt) {
            printf("ERROR writing Xcode 4 file: target not found!");
            return -1;
          }
          Fl_File_Type *f;
          for (f = Fl_File_Type::first_file(tgt); f; f = f->next_file(tgt)) {
            // FIXME: write a file type converter!
            if (f->lists_in(FL_ENV_XC4)) {
              char PBXFileRef[32]; strcpy(PBXFileRef, f->get_UUID_Xcode("Xcode4_PBXFileRef"));
              fprintf(out, "\t\t%s /* %s */ = {isa = PBXFileReference; fileEncoding = 4; %s; name = %s; path = ../../%s; sourceTree = SOURCE_ROOT; };\n", 
                      PBXFileRef,
                      f->filename_name(), 
                      xcode4_type(f->filetype()),
                      f->filename_name(), 
                      f->filename());
            }
          }
          hash = strchr(hash, ';')+1;
        } else if (strncmp(hash, "#HeadersGroup(", 14)==0) {
          Fl_Type *tgt = Fl_Target_Type::find(hash+14, ')');
          if (!tgt) {
            printf("ERROR writing Xcode 4 file: target not found!");
            return -1;
          }
          Fl_File_Type *f;
          for (f = Fl_File_Type::first_file(tgt); f; f = f->next_file(tgt)) {
            if (f->lists_in(FL_ENV_XC4) && f->is_header()) {
              char PBXFileRef[32]; strcpy(PBXFileRef, f->get_UUID_Xcode("Xcode4_PBXFileRef"));
              fprintf(out, "\t\t\t\t%s /* %s */,\n", 
                      PBXFileRef, 
                      f->filename_name());
            }
          }
          hash = strchr(hash, ';')+1;
        } else if (strncmp(hash, "#SourcesGroup(", 14)==0) {
          Fl_Type *tgt = Fl_Target_Type::find(hash+14, ')');
          if (!tgt) {
            printf("ERROR writing Xcode 4 file: target not found!");
            return -1;
          }
          Fl_File_Type *f;
          for (f = Fl_File_Type::first_file(tgt); f; f = f->next_file(tgt)) {
            if (f->lists_in(FL_ENV_XC4) && f->is_code()) {
              char PBXFileRef[32]; strcpy(PBXFileRef, f->get_UUID_Xcode("Xcode4_PBXFileRef"));
              fprintf(out, "\t\t\t\t%s /* %s */,\n", 
                      PBXFileRef, 
                      f->filename_name());
            }
          }
          hash = strchr(hash, ';')+1;
        } else if (strncmp(hash, "#HeadersBuildPhase(", 19)==0) {
          Fl_Type *tgt = Fl_Target_Type::find(hash+19, ')');
          if (!tgt) {
            printf("ERROR writing Xcode 4 file: target not found!");
            return -1;
          }
          Fl_File_Type *f;
          for (f = Fl_File_Type::first_file(tgt); f; f = f->next_file(tgt)) {
            if (f->builds_in(FL_ENV_XC4) && f->is_header()) {
              char PBXBuildFile[32]; strcpy(PBXBuildFile, f->get_UUID_Xcode("Xcode4_PBXBuildFile"));
              fprintf(out, "\t\t\t\t%s /* %s in %s */,\n", 
                      PBXBuildFile, 
                      f->filename_name(), 
                      "Sources");
            }
          }
          hash = strchr(hash, ';')+1;
        } else if (strncmp(hash, "#SourcesBuildPhase(", 19)==0) {
          Fl_Type *tgt = Fl_Target_Type::find(hash+19, ')');
          if (!tgt) {
            printf("ERROR writing Xcode 4 file: target not found!");
            return -1;
          }
          Fl_File_Type *f;
          for (f = Fl_File_Type::first_file(tgt); f; f = f->next_file(tgt)) {
            if (f->builds_in(FL_ENV_XC4) && f->is_code()) {
              char PBXBuildFile[32]; strcpy(PBXBuildFile, f->get_UUID_Xcode("Xcode4_PBXBuildFile"));
              fprintf(out, "\t\t\t\t%s /* %s in %s */,\n", 
                      PBXBuildFile, 
                      f->filename_name(), 
                      "Sources");
            }
          }
          hash = strchr(hash, ';')+1;
        } else {
          printf("Unknown command in template: <<%s>>\n", hash);
          copyLine = 1;
          hash++;
        }
      }
    }
    if (copyLine) fputs(buf, out);
  }
  
  fclose(in);
  fclose(out);
  
  return 0;
}


//
// End of "$Id: file_xcode.cxx 8870 2011-07-26 21:19:35Z matt $".
//
