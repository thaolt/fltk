/
// "$Id$
/
// Xlib X specific code for the Fast Light Tool Kit (FLTK)
/
// Copyright 1998-2004 by Bill Spitzak and others
/
// This library is free software; you can redistribute it and/o
// modify it under the terms of the GNU Library General Publi
// License as published by the Free Software Foundation; eithe
// version 2 of the License, or (at your option) any later version
/
// This library is distributed in the hope that it will be useful
// but WITHOUT ANY WARRANTY; without even the implied warranty o
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GN
// Library General Public License for more details
/
// You should have received a copy of the GNU Library General Publi
// License along with this library; if not, write to the Free Softwar
// Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-130
// USA
/
// Please report all bugs and problems to "fltk-bugs@fltk.org"
/



#  define CONSOLIDATE_MOTION 
/**** Define this if your keyboard lacks a backspace key... ****
/* #define BACKSPACE_HACK 1 *

#  include <FL/Fl.H
#  include <FL/x.H
#  include <FL/Fl_Window.H
#  include <stdio.h
#  include <stdlib.h
#  include "../flstring.h
#  include <unistd.h
#  include <sys/time.h

///////////////////////////////////////////////////////////////
// interface to poll/select call

#  if USE_POL

#    include <poll.h
static pollfd *pollfds = 0

#  els
#    if HAVE_SYS_SELECT_
#      include <sys/select.h
#    endif /* HAVE_SYS_SELECT_H *

// The following #define is only needed for HP-UX 9.x and earlier
//#define select(a,b,c,d,e) select((a),(int *)(b),(int *)(c),(int *)(d),(e)

static fd_set fdsets[3]
static int maxfd
#    define POLLIN 
#    define POLLOUT 
#    define POLLERR 

#  endif /* USE_POLL *

static int nfds = 0
static int fd_array_size = 0
struct FD 
#  if !USE_POL
  int fd
  short events
#  endi
  void (*cb)(int, void*)
  void* arg
}

static FD *fd = 0

void Fl::add_fd(int n, int events, void (*cb)(int, void*), void *v) 
  remove_fd(n,events)
  int i = nfds++
  if (i >= fd_array_size) 
    FD *temp
    fd_array_size = 2*fd_array_size+1

    if (!fd) temp = (FD*)malloc(fd_array_size*sizeof(FD))
    else temp = (FD*)realloc(fd, fd_array_size*sizeof(FD))

    if (!temp) return
    fd = temp

#  if USE_POL
    pollfd *tpoll

    if (!pollfds) tpoll = (pollfd*)malloc(fd_array_size*sizeof(pollfd))
    else tpoll = (pollfd*)realloc(pollfds, fd_array_size*sizeof(pollfd))

    if (!tpoll) return
    pollfds = tpoll
#  endi
  
  fd[i].cb = cb
  fd[i].arg = v
#  if USE_POL
  pollfds[i].fd = n
  pollfds[i].events = events
#  els
  fd[i].fd = n
  fd[i].events = events
  if (events & POLLIN) FD_SET(n, &fdsets[0])
  if (events & POLLOUT) FD_SET(n, &fdsets[1])
  if (events & POLLERR) FD_SET(n, &fdsets[2])
  if (n > maxfd) maxfd = n
#  endi


void Fl::add_fd(int n, void (*cb)(int, void*), void* v) 
  Fl::add_fd(n, POLLIN, cb, v)


void Fl::remove_fd(int n, int events) 
  int i,j
  maxfd = -1; // recalculate maxfd on the fl
  for (i=j=0; i<nfds; i++) 
#  if USE_POL
    if (pollfds[i].fd == n) 
      int e = pollfds[i].events & ~events
      if (!e) continue; // if no events left, delete this f
      pollfds[j].events = e
    
#  els
    if (fd[i].fd == n) 
      int e = fd[i].events & ~events
      if (!e) continue; // if no events left, delete this f
      fd[i].events = e
    
#  endi
    if (fd[i].fd > maxfd) maxfd = fd[i].fd
    // move it down in the array if necessary
    if (j<i) 
      fd[j] = fd[i]
#  if USE_POL
      pollfds[j] = pollfds[i]
#  endi
    
    j++
  
  nfds = j
#  if !USE_POL
  if (events & POLLIN) FD_CLR(n, &fdsets[0])
  if (events & POLLOUT) FD_CLR(n, &fdsets[1])
  if (events & POLLERR) FD_CLR(n, &fdsets[2])
#  endi


void Fl::remove_fd(int n) 
  remove_fd(n, -1)


#if CONSOLIDATE_MOTIO
static Fl_Window* send_motion
extern Fl_Window* fl_xmousewin
#endi
static bool in_a_window; // true if in any of our windows, even destroyed one
static void do_queued_events() 
  in_a_window = true
  while (XEventsQueued(fl_display,QueuedAfterReading)) 
    XEvent xevent
    XNextEvent(fl_display, &xevent)
    fl_handle(xevent)
  
  // we send FL_LEAVE only if the mouse did not enter some other window
  if (!in_a_window) Fl::handle(FL_LEAVE, 0)
#if CONSOLIDATE_MOTIO
  else if (send_motion == fl_xmousewin) 
    send_motion = 0
    Fl::handle(FL_MOVE, fl_xmousewin)
  
#endi


// these pointers are set by the Fl::lock() function
static void nothing() {
void (*fl_lock_function)() = nothing
void (*fl_unlock_function)() = nothing

// This is never called with time_to_wait < 0.0
// It should return negative on error, 0 if nothing happens befor
// timeout, and >0 if any callbacks were done
int fl_wait(double time_to_wait) 

  // OpenGL and other broken libraries call XEventsQueue
  // unnecessarily and thus cause the file descriptor to not be ready
  // so we must check for already-read events
  if (fl_display && XQLength(fl_display)) {do_queued_events(); return 1;

#  if !USE_POL
  fd_set fdt[3]
  fdt[0] = fdsets[0]
  fdt[1] = fdsets[1]
  fdt[2] = fdsets[2]
#  endi
  int n

  fl_unlock_function()

  if (time_to_wait < 2147483.648) 
#  if USE_POL
    n = ::poll(pollfds, nfds, int(time_to_wait*1000 + .5))
#  els
    timeval t
    t.tv_sec = int(time_to_wait)
    t.tv_usec = int(1000000 * (time_to_wait-t.tv_sec))
    n = ::select(maxfd+1,&fdt[0],&fdt[1],&fdt[2],&t)
#  endi
  } else 
#  if USE_POL
    n = ::poll(pollfds, nfds, -1)
#  els
    n = ::select(maxfd+1,&fdt[0],&fdt[1],&fdt[2],0)
#  endi
  

  fl_lock_function()

  if (n > 0) 
    for (int i=0; i<nfds; i++) 
#  if USE_POL
      if (pollfds[i].revents) fd[i].cb(pollfds[i].fd, fd[i].arg)
#  els
      int f = fd[i].fd
      short revents = 0
      if (FD_ISSET(f,&fdt[0])) revents |= POLLIN
      if (FD_ISSET(f,&fdt[1])) revents |= POLLOUT
      if (FD_ISSET(f,&fdt[2])) revents |= POLLERR
      if (fd[i].events & revents) fd[i].cb(f, fd[i].arg)
#  endi
    
  
  return n


// fl_ready() is just like fl_wait(0.0) except no callbacks are done
int fl_ready() 
  if (XQLength(fl_display)) return 1
#  if USE_POL
  return ::poll(pollfds, nfds, 0)
#  els
  timeval t
  t.tv_sec = 0
  t.tv_usec = 0
  fd_set fdt[3]
  fdt[0] = fdsets[0]
  fdt[1] = fdsets[1]
  fdt[2] = fdsets[2]
  return ::select(maxfd+1,&fdt[0],&fdt[1],&fdt[2],&t)
#  endi


///////////////////////////////////////////////////////////////

Display *fl_display
Window fl_message_window = 0
int fl_screen
XVisualInfo *fl_visual
Colormap fl_colormap

XIM fl_xim_im = 0
XIC fl_xim_ic = 0
char fl_is_over_the_spot = 0
static XRectangle status_area

static Atom WM_DELETE_WINDOW
static Atom WM_PROTOCOLS
static Atom fl_MOTIF_WM_HINTS
static Atom TARGETS
static Atom CLIPBOARD
Atom fl_XdndAware
Atom fl_XdndSelection
Atom fl_XdndEnter
Atom fl_XdndTypeList
Atom fl_XdndPosition
Atom fl_XdndLeave
Atom fl_XdndDrop
Atom fl_XdndStatus
Atom fl_XdndActionCopy
Atom fl_XdndFinished
//Atom fl_XdndProxy


static void fd_callback(int,void *) 
  do_queued_events()


extern "C" 
  static int io_error_handler(Display*) 
    Fl::fatal("X I/O error")
    return 0
  

  static int xerror_handler(Display* d, XErrorEvent* e) 
    char buf1[128], buf2[128]
    sprintf(buf1, "XRequest.%d", e->request_code)
    XGetErrorDatabaseText(d,"",buf1,buf1,buf2,128)
    XGetErrorText(d, e->error_code, buf1, 128)
    Fl::warning("%s: %s 0x%lx", buf2, buf1, e->resourceid)
    return 0
  


extern char *fl_get_font_xfld(char *buffer, int bufsize, int fnum, int size)

void fl_new_ic() 
  XVaNestedList preedit_attr
  XVaNestedList status_attr
  static XFontSet   fs = NULL
  char          **missing_list
  int           missing_count
  char          *def_string
  char		fnt[8192]
  static XRectangle    spot

  if (!fs) {
    fl_get_font_xfld(fnt, sizeof(fnt), 0, 14)

    fs = XCreateFontSet(fl_display, fnt, &missing_list
	                &missing_count, &def_string)
  

  preedit_attr = XVaCreateNestedList(0
				     XNSpotLocation, &spot
				     XNFontSet, fs, NULL)
  status_attr = XVaCreateNestedList(0
				    XNAreaNeeded, &status_area
				    XNFontSet, fs, NULL)

  fl_xim_ic = XCreateIC(fl_xim_im
                	XNInputStyle, (XIMPreeditPosition | XIMStatusArea)
			XNPreeditAttributes, preedit_attr
			XNStatusAttributes, status_attr
                	NULL)
  if (!fl_xim_ic) 
    fl_xim_ic = XCreateIC(fl_xim_im
        		  XNInputStyle, (XIMPreeditPosition | XIMStatusNothing)
			  XNPreeditAttributes, preedit_attr
        		  NULL)
  

  XFree(preedit_attr)
  XFree(status_attr)

  if (!fl_xim_ic) 
    fl_is_over_the_spot = 0
    fl_xim_ic = XCreateIC(fl_xim_im
        		  XNInputStyle, (XIMPreeditNothing | XIMStatusNothing)
        		  NULL)
  } else 
    fl_is_over_the_spot = 1
    XVaNestedList status_attr
    status_attr = XVaCreateNestedList(0, XNAreaNeeded, &status_area, NULL)

    XGetICValues(fl_xim_ic, XNStatusAttributes, status_attr, NULL)
    XFree(status_attr)
  



static XRectangle    spot
static int spotf = -1
static int spots = -1

void fl_reset_spot(void) 
  spot.x = -1
  spot.y = -1
  //if (fl_xim_ic) XUnsetICFocus(fl_xim_ic)


void fl_set_spot(int font, int size, int x, int y, int w, int h) 
  int change = 0
  XVaNestedList preedit_attr
  static XFontSet   fs = NULL
  char          **missing_list
  int           missing_count
  char          *def_string
  char fnt[8192]
  static XIC ic = NULL

  if (!fl_xim_ic || !fl_is_over_the_spot) return

  //XSetICFocus(fl_xim_ic)

  if (x != spot.x || y != spot.y) {
    spot.x = x
    spot.y = y
    spot.height = h
    spot.width = w
    change = 1
  

  if (font != spotf || size != spots) 
    spotf = font
    spots = size
    change = 1
    if (fs) 
      XFreeFontSet(fl_display, fs)
    
    fl_get_font_xfld(fnt, sizeof(fnt), font, size)
    fs = XCreateFontSet(fl_display, fnt, &missing_list
	                &missing_count, &def_string)
    free(fnt)
  

  if (fl_xim_ic != ic) 
    ic = fl_xim_ic
    change = 1
  

  if (!change) return

  preedit_attr = XVaCreateNestedList(0
				     XNSpotLocation, &spot
				     XNFontSet, fs, NULL)
  XSetICValues(fl_xim_ic, XNPreeditAttributes, preedit_attr, NULL)
  XFree(preedit_attr)


void fl_set_status(int x, int y, int w, int h) 
  if (!fl_xim_ic) return

  XVaNestedList status_attr

  status_area.x = x
  status_area.y = y
  status_area.width = w
  status_area.height = h

  status_attr = XVaCreateNestedList(0, XNArea, &status_area, NULL)

  XSetICValues(fl_xim_ic, XNStatusAttributes, status_attr, NULL)

  XFree(status_attr)


void fl_init_xim() {
  //XIMStyle *style
  XIMStyles *xim_styles
  if (!fl_display) return
  if (fl_xim_im) return

  fl_xim_im = XOpenIM(fl_display, NULL, NULL, NULL)
  xim_styles = NULL
  fl_xim_ic = NULL

  if (fl_xim_im) 
    XGetIMValues(fl_xim_im, XNQueryInputStyle
                 &xim_styles, NULL, NULL)
  } else 
    Fl::warning("XOpenIM() failed")
    return
  

  if (xim_styles && xim_styles->count_styles) 
    fl_new_ic()
  } else 
    Fl::warning("No XIM style found")
    XCloseIM(fl_xim_im)
    fl_xim_im = NULL
    return
  

  if (!fl_xim_ic) 
    Fl::warning("XCreateIC() failed")
    XCloseIM(fl_xim_im)
    XFree(xim_styles)
    fl_xim_im = NULL
  



void fl_open_display() 
  if (fl_display) return

//  setlocale(LC_CTYPE, "")
  XSetLocaleModifiers("")

  XSetIOErrorHandler(io_error_handler)
  XSetErrorHandler(xerror_handler)

  Display *d = XOpenDisplay(0)
  if (!d) Fl::fatal("Can't open display: %s",XDisplayName(0))

  fl_open_display(d)


void fl_open_display(Display* d) 
  fl_display = d

  WM_DELETE_WINDOW      = XInternAtom(d, "WM_DELETE_WINDOW",	0)
  WM_PROTOCOLS          = XInternAtom(d, "WM_PROTOCOLS",	0)
  fl_MOTIF_WM_HINTS     = XInternAtom(d, "_MOTIF_WM_HINTS",	0)
  TARGETS               = XInternAtom(d, "TARGETS",		0)
  CLIPBOARD		= XInternAtom(d, "CLIPBOARD",		0)
  fl_XdndAware          = XInternAtom(d, "XdndAware",		0)
  fl_XdndSelection      = XInternAtom(d, "XdndSelection",	0)
  fl_XdndEnter          = XInternAtom(d, "XdndEnter",		0)
  fl_XdndTypeList       = XInternAtom(d, "XdndTypeList",	0)
  fl_XdndPosition       = XInternAtom(d, "XdndPosition",	0)
  fl_XdndLeave          = XInternAtom(d, "XdndLeave",		0)
  fl_XdndDrop           = XInternAtom(d, "XdndDrop",		0)
  fl_XdndStatus         = XInternAtom(d, "XdndStatus",		0)
  fl_XdndActionCopy     = XInternAtom(d, "XdndActionCopy",	0)
  fl_XdndFinished       = XInternAtom(d, "XdndFinished",	0)
  //fl_XdndProxy        = XInternAtom(d, "XdndProxy",		0)

  Fl::add_fd(ConnectionNumber(d), POLLIN, fd_callback)

  fl_screen = DefaultScreen(d)

  fl_message_window 
    XCreateSimpleWindow(d, RootWindow(d,fl_screen), 0,0,1,1,0, 0, 0)

// construct an XVisualInfo that matches the default Visual
  XVisualInfo templt; int num
  templt.visualid = XVisualIDFromVisual(DefaultVisual(d, fl_screen))
  fl_visual = XGetVisualInfo(d, VisualIDMask, &templt, &num)
  fl_colormap = DefaultColormap(d, fl_screen)

  fl_init_xim()

#if !USE_COLORMA
  Fl::visual(FL_RGB)
#endi


void fl_close_display() 
  Fl::remove_fd(ConnectionNumber(fl_display))
  XCloseDisplay(fl_display)


int Fl::h() 
  fl_open_display()
  return DisplayHeight(fl_display,fl_screen)


int Fl::w() 
  fl_open_display()
  return DisplayWidth(fl_display,fl_screen)


void Fl::get_mouse(int &xx, int &yy) 
  fl_open_display()
  Window root = RootWindow(fl_display, fl_screen)
  Window c; int mx,my,cx,cy; unsigned int mask
  XQueryPointer(fl_display,root,&root,&c,&mx,&my,&cx,&cy,&mask)
  xx = mx
  yy = my


///////////////////////////////////////////////////////////////
// Code used for paste and DnD into the program

Fl_Widget *fl_selection_requestor
char *fl_selection_buffer[2]
int fl_selection_length[2]
int fl_selection_buffer_length[2]
char fl_i_own_selection[2]

// Call this when a "paste" operation happens
void Fl::paste(Fl_Widget &receiver, int clipboard) 
  if (fl_i_own_selection[clipboard]) 
    // We already have it, do it quickly without window server
    // Notice that the text is clobbered if set_selection i
    // called in response to FL_PASTE
    Fl::e_text = fl_selection_buffer[clipboard]
    Fl::e_length = fl_selection_length[clipboard]
    if (!Fl::e_text) Fl::e_text = (char *)""
    receiver.handle(FL_PASTE)
    return
  
  // otherwise get the window server to return it
  fl_selection_requestor = &receiver
  Atom property = clipboard ? CLIPBOARD : XA_PRIMARY
  XConvertSelection(fl_display, property, XA_STRING, property
		    fl_xid(Fl::first_window()), fl_event_time)


Window fl_dnd_source_window
Atom *fl_dnd_source_types; // null-terminated list of data types being supplie
Atom fl_dnd_type
Atom fl_dnd_source_action
Atom fl_dnd_action

void fl_sendClientMessage(Window window, Atom message
                                 unsigned long d0
                                 unsigned long d1=0
                                 unsigned long d2=0
                                 unsigned long d3=0
                                 unsigned long d4=0

  XEvent e
  e.xany.type = ClientMessage
  e.xany.window = window
  e.xclient.message_type = message
  e.xclient.format = 32
  e.xclient.data.l[0] = (long)d0
  e.xclient.data.l[1] = (long)d1
  e.xclient.data.l[2] = (long)d2
  e.xclient.data.l[3] = (long)d3
  e.xclient.data.l[4] = (long)d4
  XSendEvent(fl_display, window, 0, 0, &e)


///////////////////////////////////////////////////////////////
// Code for copying to clipboard and DnD out of the program

void Fl::copy(const char *stuff, int len, int clipboard) 
  if (!stuff || len<0) return
  if (len+1 > fl_selection_buffer_length[clipboard]) 
    delete[] fl_selection_buffer[clipboard]
    fl_selection_buffer[clipboard] = new char[len+100]
    fl_selection_buffer_length[clipboard] = len+100
  
  memcpy(fl_selection_buffer[clipboard], stuff, len)
  fl_selection_buffer[clipboard][len] = 0; // needed for direct past
  fl_selection_length[clipboard] = len
  fl_i_own_selection[clipboard] = 1
  Atom property = clipboard ? CLIPBOARD : XA_PRIMARY
  XSetSelectionOwner(fl_display, property, fl_message_window, fl_event_time)


///////////////////////////////////////////////////////////////

const XEvent* fl_xevent; // the current x even
ulong fl_event_time; // the last timestamp from an x even

char fl_key_vector[32]; // used by Fl::get_key(

// Record event mouse position and state from an XEvent

static int px, py
static ulong ptime

static void set_event_xy() 
#  if CONSOLIDATE_MOTIO
  send_motion = 0
#  endi
  Fl::e_x_root  = fl_xevent->xbutton.x_root
  Fl::e_x       = fl_xevent->xbutton.x
  Fl::e_y_root  = fl_xevent->xbutton.y_root
  Fl::e_y       = fl_xevent->xbutton.y
  Fl::e_state   = fl_xevent->xbutton.state << 16
  fl_event_time = fl_xevent->xbutton.time
#  ifdef __sg
  // get the meta key off PC keyboards
  if (fl_key_vector[18]&0x18) Fl::e_state |= FL_META
#  endi
  // turn off is_click if enough time or mouse movement has passed
  if (abs(Fl::e_x_root-px)+abs(Fl::e_y_root-py) > 3 |
      fl_event_time >= ptime+1000
    Fl::e_is_click = 0


// if this is same event as last && is_click, increment click count
static inline void checkdouble() 
  if (Fl::e_is_click == Fl::e_keysym
    Fl::e_clicks++
  else 
    Fl::e_clicks = 0
    Fl::e_is_click = Fl::e_keysym
  
  px = Fl::e_x_root
  py = Fl::e_y_root
  ptime = fl_event_time


static Fl_Window* resize_bug_fix

extern "C" 
  static Bool fake_keyup_test(Display*, XEvent* event, char* previous) 
     retur
      event->type == KeyPress &
      event->xkey.keycode == ((XKeyEvent*)previous)->keycode &
      event->xkey.time == ((XKeyEvent*)previous)->time
  


///////////////////////////////////////////////////////////////

int fl_handle(const XEvent& thisevent

  XEvent xevent = thisevent
  fl_xevent = &thisevent
  Window xid = xevent.xany.window
  static Window xim_win = 0

  if (fl_xim_ic && xevent.type == DestroyNotify &&
      xid != xim_win && !fl_find(xid)) 
    XIM xim_im
    xim_im = XOpenIM(fl_display, NULL, NULL, NULL)
    if (!xim_im) 
      /*  XIM server has crashed *
      XSetLocaleModifiers("@im=")
      fl_xim_im = NULL
      fl_init_xim()
    } else 
     // XCloseIM(xim_im); FIXM
	/* XFree86 has a bug when closing IM it crashes in
	 * _XlcCreateDefaultCharSet() !  So don't close it
         * This will cause a memory leak :-
	 *
    

    return 0
  

  if (fl_xim_ic && (xevent.type == FocusIn)) 
    if (Fl::first_window() && Fl::first_window()->modal()) 
      Window x  = fl_xid(Fl::first_window())
      if (x != xim_win) 
	xim_win  = x
        XSetICValues(fl_xim_ic
                        XNFocusWindow, xim_win
                        XNClientWindow, xim_win,
                        NULL)
	fl_set_spot(spotf, spots, spot.x, spot.y, spot.width, spot.height)
      
    } else if (xim_win != xid && xid) 
      xim_win = xid
      XSetICValues(fl_xim_ic
                        XNFocusWindow, xim_win
                        XNClientWindow, xim_win,
                        NULL)
      fl_set_spot(spotf, spots, spot.x, spot.y, spot.width, spot.height)
    
  

  if (XFilterEvent((XEvent *)&xevent, 0)) return 1

  switch (xevent.type) 

  case KeymapNotify
    memcpy(fl_key_vector, xevent.xkeymap.key_vector, 32)
    return 0

  case MappingNotify
    XRefreshKeyboardMapping((XMappingEvent*)&xevent.xmapping)
    return 0

  case SelectionNotify: 
    if (!fl_selection_requestor) return 0
    static unsigned char* buffer
    if (buffer) {XFree(buffer); buffer = 0;
    long bytesread = 0
    if (fl_xevent->xselection.property) for (;;) 
      // The Xdnd code pastes 64K chunks together, possibly to avoi
      // bugs in X servers, or maybe to avoid an extra round-trip t
      // get the property length.  I copy this here
      Atom actual; int format; unsigned long count, remaining
      unsigned char* portion
      if (XGetWindowProperty(fl_display
			     fl_xevent->xselection.requestor
			     fl_xevent->xselection.property
			     bytesread/4, 65536, 1, 0
			     &actual, &format, &count, &remaining
			     &portion)) break; // quit on erro
      if (bytesread) { // append to the accumulated buffe
	buffer = (unsigned char*)realloc(buffer, bytesread+count*format/8+remaining)
	memcpy(buffer+bytesread, portion, count*format/8)
	XFree(portion)
      } else {	// Use the first section without moving the memory
	buffer = portion
      
      bytesread += count*format/8
      if (!remaining) break
    
    Fl::e_text = buffer ? (char*)buffer : (char *)""
    Fl::e_length = bytesread
    int old_event = Fl::e_number
    fl_selection_requestor->handle(Fl::e_number = FL_PASTE)
    Fl::e_number = old_event
    // Detect if this paste is due to Xdnd by the property name (I us
    // XA_SECONDARY for that) and send an XdndFinished message. It is no
    // clear if this has to be delayed until now or if it can be don
    // immediatly after calling XConvertSelection
    if (fl_xevent->xselection.property == XA_SECONDARY &
	fl_dnd_source_window) 
      fl_sendClientMessage(fl_dnd_source_window, fl_XdndFinished
                           fl_xevent->xselection.requestor)
      fl_dnd_source_window = 0; // don't send a second tim
    
    return 1;

  case SelectionClear: 
    int clipboard = fl_xevent->xselectionclear.selection == CLIPBOARD
    fl_i_own_selection[clipboard] = 0
    return 1;

  case SelectionRequest: 
    XSelectionEvent e
    e.type = SelectionNotify
    e.requestor = fl_xevent->xselectionrequest.requestor
    e.selection = fl_xevent->xselectionrequest.selection
    int clipboard = e.selection == CLIPBOARD
    e.target = fl_xevent->xselectionrequest.target
    e.time = fl_xevent->xselectionrequest.time
    e.property = fl_xevent->xselectionrequest.property
    if (e.target == TARGETS) 
      Atom a = XA_STRING
      XChangeProperty(fl_display, e.requestor, e.property
		      XA_ATOM, sizeof(Atom)*8, 0, (unsigned char*)&a
		      sizeof(Atom))
    } else if (/*e.target == XA_STRING &&*/ fl_selection_length[clipboard]) 
      XChangeProperty(fl_display, e.requestor, e.property
		      e.target, 8, 0
		      (unsigned char *)fl_selection_buffer[clipboard]
		      fl_selection_length[clipboard])
    } else 
//    char* x = XGetAtomName(fl_display,e.target)
//    fprintf(stderr,"selection request of %s\n",x)
//    XFree(x)
      e.property = 0
    
    XSendEvent(fl_display, e.requestor, 0, 0, (XEvent *)&e);
    return 1

  // events where interesting window id is in a different place
  case CirculateNotify
  case CirculateRequest
  case ConfigureNotify
  case ConfigureRequest
  case CreateNotify
  case DestroyNotify
  case GravityNotify
  case MapNotify
  case MapRequest
  case ReparentNotify
  case UnmapNotify
    xid = xevent.xmaprequest.window
    break
  

  int event = 0
  Fl_Window* window = fl_find(xid)

  if (window) switch (xevent.type) 

  case ClientMessage: 
    Atom message = fl_xevent->xclient.message_type
    const long* data = fl_xevent->xclient.data.l
    if ((Atom)(data[0]) == WM_DELETE_WINDOW) 
      event = FL_CLOSE
    } else if (message == fl_XdndEnter) 
      fl_xmousewin = window
      in_a_window = true
      fl_dnd_source_window = data[0]
      // version number is data[1]>>2
      if (data[1]&1) 
	// get list of data types
	Atom actual; int format; unsigned long count, remaining
	unsigned char *buffer = 0
	XGetWindowProperty(fl_display, fl_dnd_source_window, fl_XdndTypeList
			   0, 0x8000000L, False, XA_ATOM, &actual, &format
			   &count, &remaining, &buffer)
	if (actual != XA_ATOM || format != 32 || count<4 || !buffer
	  goto FAILED
	delete [] fl_dnd_source_types
	fl_dnd_source_types = new Atom[count+1]
	for (unsigned i = 0; i < count; i++
	  fl_dnd_source_types[i] = ((Atom*)buffer)[i]
	fl_dnd_source_types[count] = 0
      } else 
      FAILED
	// less than four data types, or if the above messes up
	if (!fl_dnd_source_types) fl_dnd_source_types = new Atom[4]
	fl_dnd_source_types[0] = data[2]
	fl_dnd_source_types[1] = data[3]
	fl_dnd_source_types[2] = data[4]
	fl_dnd_source_types[3] = 0
      
      fl_dnd_type = fl_dnd_source_types[0]; // should pick text or ur
      event = FL_DND_ENTER
      break

    } else if (message == fl_XdndPosition) 
      fl_xmousewin = window
      in_a_window = true
      fl_dnd_source_window = data[0]
      Fl::e_x_root = data[2]>>16
      Fl::e_y_root = data[2]&0xFFFF
      if (window) 
	Fl::e_x = Fl::e_x_root-window->x()
	Fl::e_y = Fl::e_y_root-window->y()
      
      fl_event_time = data[3]
      fl_dnd_source_action = data[4]
      fl_dnd_action = fl_XdndActionCopy
      int accept = Fl::handle(FL_DND_DRAG, window)
      fl_sendClientMessage(data[0], fl_XdndStatus
                           fl_xevent->xclient.window
                           accept ? 1 : 0
                           0, // used for xy rectangle to not send position insid
                           0, // used for width+height of rectangl
                           accept ? fl_dnd_action : None)
      return 1

    } else if (message == fl_XdndLeave) 
      fl_dnd_source_window = 0; // don't send a finished message to i
      event = FL_DND_LEAVE
      break

    } else if (message == fl_XdndDrop) 
      fl_xmousewin = window
      in_a_window = true
      fl_dnd_source_window = data[0]
      fl_event_time = data[2]
      Window to_window = fl_xevent->xclient.window
      if (Fl::handle(FL_DND_RELEASE, window)) 
	fl_selection_requestor = Fl::belowmouse()
	XConvertSelection(fl_display, fl_XdndSelection
			  fl_dnd_type, XA_SECONDARY
			  to_window, fl_event_time)
      } else 
	// Send the finished message if I refuse the drop
	// It is not clear whether I can just send finished always
	// or if I have to wait for the SelectionNotify event as th
	// code is currently doing
	fl_sendClientMessage(fl_dnd_source_window, fl_XdndFinished, to_window)
	fl_dnd_source_window = 0
      
      return 1

    
    break;

  case UnmapNotify
    event = FL_HIDE
    break

  case Expose
    Fl_X::i(window)->wait_for_expose = 0
#  if 
    // try to keep windows on top even if WM_TRANSIENT_FOR does not work
    // opaque move/resize window managers do not like this, so I disabled it
    if (Fl::first_window()->non_modal() && window != Fl::first_window()
      Fl::first_window()->show()
#  endi

  case GraphicsExpose
    window->damage(FL_DAMAGE_EXPOSE, xevent.xexpose.x, xevent.xexpose.y
		   xevent.xexpose.width, xevent.xexpose.height)
    return 1

  case FocusIn
    if (fl_xim_ic) XSetICFocus(fl_xim_ic)
    event = FL_FOCUS
    break

  case FocusOut
    if (fl_xim_ic) XUnsetICFocus(fl_xim_ic)
    event = FL_UNFOCUS
    break

  case KeyPress
  case KeyRelease: 
  KEYPRESS
    int keycode = xevent.xkey.keycode
    fl_key_vector[keycode/8] |= (1 << (keycode%8))
    static char buffer[4096]
    int len
    KeySym keysym
    if (xevent.type == KeyPress) 
      event = FL_KEYDOWN
      //static XComposeStatus compose

      if (fl_xim_ic) 
        Status status
        len = Xutf8LookupString(fl_xim_ic, (XKeyPressedEvent *)&xevent.xkey
                                buffer, sizeof(buffer) - 1, &keysym, &status)
      } else 
	len = XLookupString((XKeyEvent*)&(xevent.xkey)
	                    buffer, sizeof(buffer) - 1, &keysym, 0/*&compose*/)

	if (keysym && keysym < 0x100) { // a character in latin-1 se
	  // force it to type a character (not sure if this ever is needed)
	  if (!len) 
	    if (keysym & 0x80) 
	      buffer[0] = 0xc0 | (keysym >> 6)
	      buffer[1] = 0x80 | (keysym & 0x3f)
	      len = 2
	    } else 
	      buffer[0] = keysym & 0x7f
	      len = 1
	    
	  

	  // ignore all effects of shift on the keysyms, which makes it a lo
	  // easier to program shortcuts and is Windoze-compatable
	  keysym = XKeycodeToKeysym(fl_display, keycode, 0)
	
      

      // MRS: Can't use Fl::event_state(FL_CTRL) since the state is no
      //      set until set_event_xy() is called later..
      if ((xevent.xkey.state & ControlMask) && keysym == '-') buffer[0] = 0x1f; // ^
      buffer[len] = 0
      Fl::e_text = buffer
      Fl::e_length = len
    } else 
      // Stupid X sends fake key-up events when a repeating key is hel
      // down, probably due to some back compatability problem. Fortunatle
      // we can detect this because the repeating KeyPress event is i
      // the queue, get it and execute it instead
      XEvent temp
      if (XCheckIfEvent(fl_display,&temp,fake_keyup_test,(char*)(&xevent)))
	xevent = temp
	goto KEYPRESS
      
      event = FL_KEYUP
      fl_key_vector[keycode/8] &= ~(1 << (keycode%8))
      // keyup events just get the unshifted keysym
      keysym = XKeycodeToKeysym(fl_display, keycode, 0)
    
#  ifdef __sg
    // You can plug a microsoft keyboard into an sgi but the extra shif
    // keys are not translated.  Make them translate like XFree86 does
    if (!keysym) switch(keycode) 
    case 147: keysym = FL_Meta_L; break
    case 148: keysym = FL_Meta_R; break
    case 149: keysym = FL_Menu; break
    
#  endi
#  if BACKSPACE_HAC
    // Attempt to fix keyboards that send "delete" for the key in th
    // upper-right corner of the main keyboard.  But it appears tha
    // very few of these remain
    static int got_backspace
    if (!got_backspace) 
      if (keysym == FL_Delete) keysym = FL_BackSpace
      else if (keysym == FL_BackSpace) got_backspace = 1
    
#  endi
    // We have to get rid of the XK_KP_function keys, because they ar
    // not produced on Windoze and thus case statements tend not to chec
    // for them.  There are 15 of these in the range 0xff91 ... 0xff9
    if (keysym >= 0xff91 && keysym <= 0xff9f) 
      // Map keypad keysym to character or keysym depending o
      // numlock state..
      unsigned long keysym1 = XKeycodeToKeysym(fl_display, keycode, 1)
      if ((xevent.xkey.state & Mod2Mask) &
          (keysym1 <= 0x7f || (keysym1 > 0xff9f && keysym1 <= FL_KP_Last))) 
	// Store ASCII numeric keypad value..
	keysym = keysym1 | FL_KP
	buffer[0] = char(keysym1) & 0x7F
	len = 1
      } else 
	// Map keypad to special key..
	static const unsigned short table[15] = 
	  FL_F+1, FL_F+2, FL_F+3, FL_F+4
	  FL_Home, FL_Left, FL_Up, FL_Right
	  FL_Down, FL_Page_Up, FL_Page_Down, FL_End
	  0xff0b/*XK_Clear*/, FL_Insert, FL_Delete}
	keysym = table[keysym-0xff91]
      
    
    Fl::e_keysym = int(keysym)
    set_event_xy()
    Fl::e_is_click = 0
    break;

  case ButtonPress
    Fl::e_keysym = FL_Button + xevent.xbutton.button
    set_event_xy()
    if (xevent.xbutton.button == Button4) 
      Fl::e_dy = -1; // U
      event = FL_MOUSEWHEEL
    } else if (xevent.xbutton.button == Button5) 
      Fl::e_dy = +1; // Dow
      event = FL_MOUSEWHEEL
    } else 
      Fl::e_state |= (FL_BUTTON1 << (xevent.xbutton.button-1))
      event = FL_PUSH
      checkdouble()
    

    fl_xmousewin = window
    in_a_window = true
    break

  case MotionNotify
    set_event_xy()
#  if CONSOLIDATE_MOTIO
    send_motion = fl_xmousewin = window
    in_a_window = true
    return 0
#  els
    event = FL_MOVE
    fl_xmousewin = window
    in_a_window = true
    break
#  endi

  case ButtonRelease
    Fl::e_keysym = FL_Button + xevent.xbutton.button
    set_event_xy()
    Fl::e_state &= ~(FL_BUTTON1 << (xevent.xbutton.button-1))
    if (xevent.xbutton.button == Button4 |
        xevent.xbutton.button == Button5) return 0
    event = FL_RELEASE

    fl_xmousewin = window
    in_a_window = true
    break

  case EnterNotify
    if (xevent.xcrossing.detail == NotifyInferior) break
    // XInstallColormap(fl_display, Fl_X::i(window)->colormap)
    set_event_xy()
    Fl::e_state = xevent.xcrossing.state << 16
    event = FL_ENTER

    fl_xmousewin = window
    in_a_window = true
    break

  case LeaveNotify
    if (xevent.xcrossing.detail == NotifyInferior) break
    set_event_xy()
    Fl::e_state = xevent.xcrossing.state << 16
    fl_xmousewin = 0
    in_a_window = false; // make do_queued_events produce FL_LEAVE even
    return 0

  // We cannot rely on the x,y position in the configure notify event
  // I now think this is an unavoidable problem with X: it is impossibl
  // for a window manager to prevent the "real" notify event from bein
  // sent when it resizes the contents, even though it can send a
  // artificial event with the correct position afterwards (and som
  // window managers do not send this fake event anyway
  // So anyway, do a round trip to find the correct x,y
  case MapNotify
    event = FL_SHOW

  case ConfigureNotify: 
    if (window->parent()) break; // ignore child window

    // figure out where OS really put windo
    XWindowAttributes actual
    XGetWindowAttributes(fl_display, fl_xid(window), &actual)
    Window cr; int X, Y, W = actual.width, H = actual.height
    XTranslateCoordinates(fl_display, fl_xid(window), actual.root
                          0, 0, &X, &Y, &cr)

    // tell Fl_Window about it and set flag to prevent echoing
    resize_bug_fix = window
    window->resize(X, Y, W, H)
    break; // allow add_handler to do something to
    
   
    case ReparentNotify: 
      int xpos, ypos
      Window junk;
      //ReparentNotify gives the new position of the window relative t
      //the new parent. FLTK cares about the position on the root window
      XTranslateCoordinates(fl_display, xevent.xreparent.parent
                            XRootWindow(fl_display, fl_screen)
                            xevent.xreparent.x, xevent.xreparent.y
                            &xpos, &ypos, &junk)
     // tell Fl_Window about it and set flag to prevent echoing
      resize_bug_fix = window
      window->position(xpos, ypos)
      break
    
  

  return Fl::handle(event, window)


///////////////////////////////////////////////////////////////

void Fl_Window::resize(int X,int Y,int W,int H) 
  int is_a_move = (X != x() || Y != y())
  int is_a_resize = (W != w() || H != h())
  int resize_from_program = (this != resize_bug_fix)
  if (!resize_from_program) resize_bug_fix = 0
  if (is_a_move && resize_from_program) set_flag(FL_FORCE_POSITION)
  else if (!is_a_resize && !is_a_move) return
  if (is_a_resize) 
    Fl_Group::resize(X,Y,W,H)
    if (shown()) {redraw(); i->wait_for_expose = 1;
  } else 
    x(X); y(Y)
  

  if (resize_from_program && is_a_resize && !resizable()) 
    size_range(w(), h(), w(), h())
  

  if (resize_from_program && shown()) 
    if (is_a_resize) 
      if (!resizable()) size_range(w(),h(),w(),h())
      if (is_a_move) 
	XMoveResizeWindow(fl_display, i->xid, X, Y, W>0 ? W : 1, H>0 ? H : 1)
      } else 
	XResizeWindow(fl_display, i->xid, W>0 ? W : 1, H>0 ? H : 1)
      
    } els
      XMoveWindow(fl_display, i->xid, X, Y)
  


///////////////////////////////////////////////////////////////

// A subclass of Fl_Window may call this to associate an X window i
// creates with the Fl_Window

void fl_fix_focus(); // in Fl.cx

Fl_X* Fl_X::set_xid(Fl_Window* win, Window winxid) 
  Fl_X* xp = new Fl_X
  xp->xid = winxid
  xp->other_xid = 0
  xp->setwindow(win)
  xp->next = Fl_X::first
  xp->region = 0
  xp->wait_for_expose = 1
  xp->backbuffer_bad = 1
  Fl_X::first = xp
  if (win->modal()) {Fl::modal_ = win; fl_fix_focus();
  return xp


// More commonly a subclass calls this, because it hides the reall
// ugly parts of X and sets all the stuff for a window that is se
// normally.  The global variables like fl_show_iconic are so tha
// subclasses of *that* class may change the behavior..

char fl_show_iconic;	// hack for iconize(
int fl_background_pixel = -1; // hack to speed up bg box drawin
int fl_disable_transient_for; // secret method of removing TRANSIENT_FO

static const int childEventMask = ExposureMask

static const int XEventMask 
ExposureMask|StructureNotifyMas
|KeyPressMask|KeyReleaseMask|KeymapStateMask|FocusChangeMas
|ButtonPressMask|ButtonReleaseMas
|EnterWindowMask|LeaveWindowMas
|PointerMotionMask

void Fl_X::make_xid(Fl_Window* win, XVisualInfo *visual, Colormap colormap

  Fl_Group::current(0); // get rid of very common user bug: forgot end(

  int X = win->x()
  int Y = win->y()
  int W = win->w()
  if (W <= 0) W = 1; // X don't like zero..
  int H = win->h()
  if (H <= 0) H = 1; // X don't like zero..
  if (!win->parent() && !Fl::grab()) 
    // center windows in case window manager does not do anything
#ifdef FL_CENTER_WINDOW
    if (!(win->flags() & Fl_Window::FL_FORCE_POSITION)) 
      win->x(X = (Fl::w()-W)/2)
      win->y(Y = (Fl::h()-H)/2)
    
#endif // FL_CENTER_WINDOW

    // force the window to be on-screen.  Usually the X window manage
    // does this, but a few don't, so we do it here for consistency
    if (win->border()) 
      // ensure border is on screen
      // (assumme extremely minimal dimensions for this border
      const int top = 20
      const int left = 1
      const int right = 1
      const int bottom = 1
      if (X+W+right > Fl::w()) X = Fl::w()-right-W
      if (X-left < 0) X = left
      if (Y+H+bottom > Fl::h()) Y = Fl::h()-bottom-H
      if (Y-top < 0) Y = top
    
    // now insure contents are on-screen (more important than border)
    if (X+W > Fl::w()) X = Fl::w()-W
    if (X < 0) X = 0
    if (Y+H > Fl::h()) Y = Fl::h()-H
    if (Y < 0) Y = 0
  

  ulong root = win->parent() 
    fl_xid(win->window()) : RootWindow(fl_display, fl_screen)

  XSetWindowAttributes attr
  int mask = CWBorderPixel|CWColormap|CWEventMask|CWBitGravity
  attr.event_mask = win->parent() ? childEventMask : XEventMask
  attr.colormap = colormap
  attr.border_pixel = 0
  attr.bit_gravity = 0; // StaticGravity
  if (win->override()) 
    attr.override_redirect = 1
    attr.save_under = 1
    mask |= CWOverrideRedirect | CWSaveUnder
  } else attr.override_redirect = 0
  if (Fl::grab()) 
    attr.save_under = 1; mask |= CWSaveUnder
    if (!win->border()) {attr.override_redirect = 1; mask |= CWOverrideRedirect;
  
  if (fl_background_pixel >= 0) 
    attr.background_pixel = fl_background_pixel
    fl_background_pixel = -1
    mask |= CWBackPixel
  

  Fl_X* xp 
    set_xid(win, XCreateWindow(fl_display
			       root
			       X, Y, W, H
			       0, // borderwidt
			       visual->depth
			       InputOutput
			       visual->visual
			       mask, &attr))
  int showit = 1

  if (!win->parent() && !attr.override_redirect) 
    // Communicate all kinds 'o junk to the X Window Manager

    win->label(win->label(), win->iconlabel())

    XChangeProperty(fl_display, xp->xid, WM_PROTOCOLS
 		    XA_ATOM, 32, 0, (uchar*)&WM_DELETE_WINDOW, 1)

    // send size limits and border
    xp->sendxjunk()

    // set the class property, which controls the icon used
    if (win->xclass()) 
      char buffer[1024]
      char *p; const char *q
      // truncate on any punctuation, because they break XResource lookup
      for (p = buffer, q = win->xclass(); isalnum(*q)||(*q&128);) *p++ = *q++
      *p++ = 0
      // create the capitalized version
      q = buffer
      *p = toupper(*q++); if (*p++ == 'X') *p++ = toupper(*q++)
      while ((*p++ = *q++))
      XChangeProperty(fl_display, xp->xid, XA_WM_CLASS, XA_STRING, 8, 0
		      (unsigned char *)buffer, p-buffer-1)
    

    if (win->non_modal() && xp->next && !fl_disable_transient_for) 
      // find some other window to be "transient for"
      Fl_Window* wp = xp->next->w
      while (wp->parent()) wp = wp->window()
      XSetTransientForHint(fl_display, xp->xid, fl_xid(wp))
      if (!wp->visible()) showit = 0; // guess that wm will not show i
    

    // Make it receptive to DnD
    long version = 4
    XChangeProperty(fl_display, xp->xid, fl_XdndAware
		    XA_ATOM, sizeof(int)*8, 0, (unsigned char*)&version, 1)

    XWMHints *hints = XAllocWMHints()
    hints->input = True
    hints->flags = InputHint
    if (fl_show_iconic) 
      hints->flags |= StateHint
      hints->initial_state = IconicState
      fl_show_iconic = 0
      showit = 0
    
    if (win->icon()) 
      hints->icon_pixmap = (Pixmap)win->icon()
      hints->flags       |= IconPixmapHint
    
    XSetWMHints(fl_display, xp->xid, hints)
    XFree(hints)
  

  XMapWindow(fl_display, xp->xid)
  if (showit) 
    win->set_visible()
    int old_event = Fl::e_number
    win->handle(Fl::e_number = FL_SHOW); // get child windows to appea
    Fl::e_number = old_event
    win->redraw()
  


///////////////////////////////////////////////////////////////
// Send X window stuff that can be changed over time

void Fl_X::sendxjunk() 
  if (w->parent() || w->override()) return; // it's not a window manager window

  if (!w->size_range_set) { // default size_range based on resizable()
    if (w->resizable()) 
      Fl_Widget *o = w->resizable()
      int minw = o->w(); if (minw > 100) minw = 100
      int minh = o->h(); if (minh > 100) minh = 100
      w->size_range(w->w() - o->w() + minw, w->h() - o->h() + minh, 0, 0)
    } else 
      w->size_range(w->w(), w->h(), w->w(), w->h())
    
    return; // because this recursively called her
  

  XSizeHints *hints = XAllocSizeHints()
  // memset(&hints, 0, sizeof(hints)); jreiser suggestion to fix purify
  hints->min_width = w->minw
  hints->min_height = w->minh
  hints->max_width = w->maxw
  hints->max_height = w->maxh
  hints->width_inc = w->dw
  hints->height_inc = w->dh
  hints->win_gravity = StaticGravity

  // see the file /usr/include/X11/Xm/MwmUtil.h
  // fill all fields to avoid bugs in kwm and perhaps other window managers
  // 0, MWM_FUNC_ALL, MWM_DECOR_AL
  long prop[5] = {0, 1, 1, 0, 0}

  if (hints->min_width != hints->max_width |
      hints->min_height != hints->max_height) { // resizabl
    hints->flags = PMinSize|PWinGravity
    if (hints->max_width >= hints->min_width |
	hints->max_height >= hints->min_height) 
      hints->flags = PMinSize|PMaxSize|PWinGravity
      // unfortunately we can't set just one maximum size.  Guess 
      // value for the other one.  Some window managers will make th
      // window fit on screen when maximized, others will put it off screen
      if (hints->max_width < hints->min_width) hints->max_width = Fl::w()
      if (hints->max_height < hints->min_height) hints->max_height = Fl::h()
    
    if (hints->width_inc && hints->height_inc) hints->flags |= PResizeInc
    if (w->aspect) 
      // stupid X!  It could insist that the corner go on th
      // straight line between min and max..
      hints->min_aspect.x = hints->max_aspect.x = hints->min_width
      hints->min_aspect.y = hints->max_aspect.y = hints->min_height
      hints->flags |= PAspect
    
  } else { // not resizable
    hints->flags = PMinSize|PMaxSize|PWinGravity
    prop[0] = 1; // MWM_HINTS_FUNCTION
    prop[1] = 1|2|16; // MWM_FUNC_ALL | MWM_FUNC_RESIZE | MWM_FUNC_MAXIMIZ
  

  if (w->flags() & Fl_Window::FL_FORCE_POSITION) 
    hints->flags |= USPosition
    hints->x = w->x()
    hints->y = w->y()
  

  if (!w->border()) 
    prop[0] |= 2; // MWM_HINTS_DECORATION
    prop[2] = 0; // no decoration
  

  XSetWMNormalHints(fl_display, xid, hints)
  XChangeProperty(fl_display, xid
		  fl_MOTIF_WM_HINTS, fl_MOTIF_WM_HINTS
		  32, 0, (unsigned char *)prop, 5)
  XFree(hints)


void Fl_Window::size_range_() 
  size_range_set = 1
  if (shown()) i->sendxjunk()


///////////////////////////////////////////////////////////////

// returns pointer to the filename, or null if name ends with '/
const char *fl_filename_name(const char *name) 
  const char *p,*q
  if (!name) return (0)
  for (p=q=name; *p;) if (*p++ == '/') q = p
  return q


void Fl_Window::label(const char *name,const char *iname) 
  Fl_Widget::label(name)
  iconlabel_ = iname
  if (shown() && !parent()) 
    if (!name) name = ""
    XChangeProperty(fl_display, i->xid, XA_WM_NAME
		    XA_STRING, 8, 0, (uchar*)name, strlen(name))
    if (!iname) iname = fl_filename_name(name)
    XChangeProperty(fl_display, i->xid, XA_WM_ICON_NAME,
		    XA_STRING, 8, 0, (uchar*)iname, strlen(iname))
  


///////////////////////////////////////////////////////////////
// Implement the virtual functions for the base Fl_Window class

// If the box is a filled rectangle, we can make the redisplay *look
// faster by using X's background pixel erasing.  We can make i
// actually *be* faster by drawing the frame only, this is done b
// setting fl_boxcheat, which is seen by code in fl_drawbox.cxx
/
// On XFree86 (and prehaps all X's) this has a problem if the windo
// is resized while a save-behind window is atop it.  The previou
// contents are restored to the area, but this assummes the are
// is cleared to background color.  So this is disabled in this version
// Fl_Window *fl_boxcheat
static inline int can_boxcheat(Fl_Boxtype b) 
    int i = Fl::box_index(b)
    return (i==1 || (i&2) && i<=15)


void Fl_Window::show() 
  image(Fl::scheme_bg_)
  if (Fl::scheme_bg_) 
    labeltype(FL_NORMAL_LABEL)
    align(FL_ALIGN_CENTER | FL_ALIGN_INSIDE | FL_ALIGN_CLIP)
  } else 
    labeltype(FL_NO_LABEL)
  
  if (!shown()) 
    fl_open_display()
    if (can_boxcheat(box())) fl_background_pixel = int(fl_xpixel(color()))
    Fl_X::make_xid(this)
  } else 
    XMapRaised(fl_display, i->xid)
  


Window fl_window
Fl_Window *Fl_Window::current_
GC fl_gc

// make X drawing go into this window (called by subclass flush() impl.
void Fl_Window::make_current() 
  static GC gc;	// the GC used by all X window
  if (!gc) gc = XCreateGC(fl_display, i->xid, 0, 0)
  fl_window = i->xid
  fl_gc = gc
  current_ = this
  fl_clip_region(0)




/
// End of "$Id$"
/
