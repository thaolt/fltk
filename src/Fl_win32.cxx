// Fl_win32.C

// fltk (Fast Light Tool Kit) version 0.99
// Copyright (C) 1998 Bill Spitzak

// This library is free software; you can redistribute it and/or
// modify it under the terms of the GNU Library General Public
// License as published by the Free Software Foundation; either
// version 2 of the License, or (at your option) any later version.

// This library is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
// Library General Public License for more details.

// You should have received a copy of the GNU Library General Public
// License along with this library; if not, write to the Free Software
// Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307
// USA.

// Written by Bill Spitzak spitzak@d2.com

// This file contains win32-specific code for fltk which is always linked
// in.  Search other files for "WIN32" or filenames ending in _win32.C
// for other system-specific code.

#include <config.h>
#include <FL/Fl.H>
#include <FL/win32.H>
#include <FL/Fl_Window.H>
#include <string.h>

////////////////////////////////////////////////////////////////
// interface to poll/select call:

// fd's are not yet implemented.
// On NT these are probably only used for network stuff, so this may
// talk to a package that Wonko has proposed writing to make the network
// interface system independent.

#define POLLIN 1
#define POLLOUT 4
#define POLLERR 8

void Fl::add_fd(int n, int events, void (*cb)(int, void*), void *v) {}

void Fl::add_fd(int fd, void (*cb)(int, void*), void* v) {
  Fl::add_fd(fd,POLLIN,cb,v);
}

void Fl::remove_fd(int n) {}

MSG fl_msg;

int fl_ready() {
  return PeekMessage(&fl_msg, NULL, 0, 0, PM_NOREMOVE);
}

double fl_wait(int timeout_flag, double time) {
  int have_message;
  // get the first message by waiting the correct amount of time:
  if (!timeout_flag) {
    GetMessage(&fl_msg, NULL, 0, 0);
    have_message = 1;
  } else {
    if (time >= 0.001) {
      int timerid = SetTimer(NULL, 0, int(time*1000), NULL);
      GetMessage(&fl_msg, NULL, 0, 0);
      KillTimer(NULL, timerid);
      have_message = 1;
    } else {
      have_message = PeekMessage(&fl_msg, NULL, 0, 0, PM_REMOVE);
    }
  }
  // execute it, them execute any other messages that become ready during it:
  while (have_message) {
    DispatchMessage(&fl_msg);
    have_message = PeekMessage(&fl_msg, NULL, 0, 0, PM_REMOVE);
  }
  return time;
}

////////////////////////////////////////////////////////////////

int Fl::h() {return GetSystemMetrics(SM_CYSCREEN);}

int Fl::w() {return GetSystemMetrics(SM_CXSCREEN);}

void Fl::get_mouse(int &x, int &y) {
  POINT p;
  GetCursorPos(&p);
  x = p.x;
  y = p.y;
}

////////////////////////////////////////////////////////////////

extern Fl_Window *fl_xfocus;	// in Fl.C
extern Fl_Window *fl_xmousewin; // in Fl.C
void fl_fix_focus(); // in Fl.C

////////////////////////////////////////////////////////////////

extern HWND fl_capture;

static int mouse_event(Fl_Window *window, int what, int button,
			WPARAM wParam, LPARAM lParam)
{
  static int px, py, pmx, pmy;
  POINT pt;
  Fl::e_x = pt.x = (signed short)LOWORD(lParam);
  Fl::e_y = pt.y = (signed short)HIWORD(lParam);
  ClientToScreen(fl_xid(window), &pt);
  Fl::e_x_root = pt.x;
  Fl::e_y_root = pt.y;
  while (window->parent()) {
    Fl::e_x += window->x();
    Fl::e_y += window->y();
    window = window->window();
  }

  ulong state = Fl::e_state & 0xff0000; // keep shift key states
#if 0
  // mouse event reports some shift flags, perhaps save them?
  if (wParam & MK_SHIFT) state |= FL_SHIFT;
  if (wParam & MK_CONTROL) state |= FL_CTRL;
#endif
  if (wParam & MK_LBUTTON) state |= FL_BUTTON1;
  if (wParam & MK_MBUTTON) state |= FL_BUTTON2;
  if (wParam & MK_RBUTTON) state |= FL_BUTTON3;
  Fl::e_state = state;

  switch (what) {
  case 1: // double-click
    if (Fl::e_is_click) {Fl::e_clicks++; goto J1;}
  case 0: // single-click
    Fl::e_clicks = 0;
  J1:
    if (!fl_capture) SetCapture(fl_xid(window));
    Fl::e_keysym = FL_Button + button;
    Fl::e_is_click = 1;
    px = pmx = Fl::e_x_root; py = pmy = Fl::e_y_root;
    return Fl::handle(FL_PUSH,window);

  case 2: // release:
    if (!fl_capture) ReleaseCapture();
    Fl::e_keysym = FL_Button + button;
    return Fl::handle(FL_RELEASE,window);

  case 3: // move:
  default: // avoid compiler warning
    // MSWindows produces extra events even if mouse does not move, ignore em:
    if (Fl::e_x_root == pmx && Fl::e_y_root == pmy) return 1;
    pmx = Fl::e_x_root; pmy = Fl::e_y_root;
    if (abs(Fl::e_x_root-px)>5 || abs(Fl::e_y_root-py)>5) Fl::e_is_click = 0;
    return Fl::handle(FL_MOVE,window);

  }
}

// convert a MSWindows VK_x to an Fltk (X) Keysym:
// See also the inverse converter in Fl_get_key_win32.C
// This table is in numeric order by VK:
static const struct {unsigned short vk, fltk;} vktab[] = {
  {VK_BACK,	FL_BackSpace},
  {VK_TAB,	FL_Tab},
  {VK_CLEAR,	FL_KP+'5'},
  {VK_RETURN,	FL_Enter},
  {VK_SHIFT,	FL_Shift_L},
  {VK_CONTROL,	FL_Control_L},
  {VK_MENU,	FL_Alt_L},
  {VK_PAUSE,	FL_Pause},
  {VK_CAPITAL,	FL_Caps_Lock},
  {VK_ESCAPE,	FL_Escape},
  {VK_SPACE,	' '},
  {VK_PRIOR,	FL_Page_Up},
  {VK_NEXT,	FL_Page_Down},
  {VK_END,	FL_End},
  {VK_HOME,	FL_Home},
  {VK_LEFT,	FL_Left},
  {VK_UP,	FL_Up},
  {VK_RIGHT,	FL_Right},
  {VK_DOWN,	FL_Down},
  {VK_SNAPSHOT,	FL_Print},	// does not work on NT
  {VK_INSERT,	FL_Insert},
  {VK_DELETE,	FL_Delete},
  {VK_LWIN,	FL_Meta_L},
  {VK_RWIN,	FL_Meta_R},
  {VK_APPS,	FL_Menu},
  {VK_MULTIPLY,	FL_KP+'*'},
  {VK_ADD,	FL_KP+'+'},
  {VK_SUBTRACT,	FL_KP+'-'},
  {VK_DECIMAL,	FL_KP+'.'},
  {VK_DIVIDE,	FL_KP+'/'},
  {VK_NUMLOCK,	FL_Num_Lock},
  {VK_SCROLL,	FL_Scroll_Lock},
  {0xba,	';'},
  {0xbb,	'='},
  {0xbc,	','},
  {0xbd,	'-'},
  {0xbe,	'.'},
  {0xbf,	'/'},
  {0xc0,	'`'},
  {0xdb,	'['},
  {0xdc,	'\\'},
  {0xdd,	']'},
  {0xde,	'\''}
};
static int ms2fltk(int vk, int extended) {
  static unsigned short vklut[256];
  if (!vklut[1]) { // init the table
    unsigned int i;
    for (i = 0; i < 256; i++) vklut[i] = tolower(i);
    for (i=VK_F1; i<=VK_F16; i++) vklut[i] = i+(FL_F-(VK_F1-1));
    for (i=VK_NUMPAD0; i<=VK_NUMPAD9; i++) vklut[i] = i+(FL_KP+'0'-VK_NUMPAD0);
    for (i = 0; i < sizeof(vktab)/sizeof(*vktab); i++)
      vklut[vktab[i].vk] = vktab[i].fltk;
  }
  if (extended) switch (vk) {
    case VK_CONTROL : return FL_Control_R;
    case VK_MENU: return FL_Alt_R;
    case VK_RETURN: return FL_KP_Enter;
  }
  return vklut[vk];
}

#if USE_COLORMAP
extern HPALETTE fl_select_palette(); // in fl_color_win32.C
#endif

static Fl_Window* resize_bug_fix;

static LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) 
{
  static char buffer[2];

  fl_msg.message = uMsg;

  Fl_Window *window = fl_find(hWnd);

 STUPID_MICROSOFT:
  if (window) switch (uMsg) {

  case WM_QUIT: // this should not happen?
    Fl::fatal("WM_QUIT message");

  case WM_CLOSE: // user clicked close box
    Fl::handle(FL_CLOSE, window);
    return 0;

  case WM_PAINT: {
    // MSWindows has already set the clip region!  Fltk does not like this,
    // since it wants to draw it's own damage at the same time, and
    // this damage may be outside the clip region.  I kludge around
    // this, grep for fl_direct_paint to find the kludges...
    // if (!(window->damage())) fl_direct_paint = 1;
    PAINTSTRUCT ps;

    // I think MSWindows refuses to allocate two DCs for the same hWnd,
    // so it may kludge the way the DCs are being handled. Works for now,
    // the "final" solution can wait... Whatever the behaviour of the win32
    // API, there is bound to be some small memory leak here. 
    // If anyone knows EXACTLY how DCs are allocated, please fix.
    fl_window = hWnd;
    fl_gc = BeginPaint(hWnd, &ps);
    // A bug popped up because of the two following lines, which according to 
    // the original code's comments GetDC always resets. I just don't get
    // why the problem hadn't manifested itself here earlier (well, probably
    // because MSWindows was not allocating a new DC, but using the old one)
    // Anyway, these followed the original GetDC calls, but for some reason
    // were not here with the BeginPaint
    SetTextAlign(fl_gc, TA_BASELINE|TA_LEFT);
    SetBkMode(fl_gc, TRANSPARENT);

    window->expose(2, ps.rcPaint.left, ps.rcPaint.top,
		   ps.rcPaint.right-ps.rcPaint.left,
		   ps.rcPaint.bottom-ps.rcPaint.top);

    Fl_X::i(window)->flush();
    window->clear_damage();
    //Since damage has been reset, we can dispose of the clip region
    Region &r=Fl_X::i(window)->region;
    if (r) {
      DeleteObject(r);
      r = 0;
    }
    EndPaint(hWnd, &ps);

    fl_gc = 0;
    fl_window = (HWND)-1;
    } break;

  case WM_LBUTTONDOWN:  mouse_event(window, 0, 1, wParam, lParam); return 0;
  case WM_LBUTTONDBLCLK:mouse_event(window, 1, 1, wParam, lParam); return 0;
  case WM_LBUTTONUP:    mouse_event(window, 2, 1, wParam, lParam); return 0;
  case WM_MBUTTONDOWN:  mouse_event(window, 0, 2, wParam, lParam); return 0;
  case WM_MBUTTONDBLCLK:mouse_event(window, 1, 2, wParam, lParam); return 0;
  case WM_MBUTTONUP:    mouse_event(window, 2, 2, wParam, lParam); return 0;
  case WM_RBUTTONDOWN:  mouse_event(window, 0, 3, wParam, lParam); return 0;
  case WM_RBUTTONDBLCLK:mouse_event(window, 1, 3, wParam, lParam); return 0;
  case WM_RBUTTONUP:    mouse_event(window, 2, 3, wParam, lParam); return 0;
  case WM_MOUSEMOVE:    mouse_event(window, 3, 0, wParam, lParam); return 0;

  // kludges so the pop-up menus work.  Title bar still blinks, sigh...
  case WM_CAPTURECHANGED:
    if (fl_capture && lParam != (LPARAM)fl_capture) {
      SetCapture(fl_capture);
      return 0;
    }
    break;
  case WM_ACTIVATE:
    if (fl_capture && wParam && hWnd!=fl_capture) {
      SetActiveWindow(fl_capture);
      return 0;
    }
    break;

  case WM_SETFOCUS:
    Fl::handle(FL_FOCUS, window);
    break;

  case WM_KILLFOCUS:
    Fl::handle(FL_UNFOCUS, window);
    Fl::flush(); // it never returns to main loop when deactivated...
    break;

  case WM_SHOWWINDOW:
    if (!window->parent())
      Fl::handle(wParam ? FL_SHOW : FL_HIDE, window);
    break;

  case WM_KEYDOWN:
  case WM_SYSKEYDOWN:
    // save the keysym until we figure out the characters:
    Fl::e_keysym = ms2fltk(wParam,lParam&(1<<24));
  case WM_KEYUP:
  case WM_SYSKEYUP:
    TranslateMessage(&fl_msg); // always returns 1!!!
    // TranslateMessage is supposed to return true only if it turns
    // into another message, but it seems to always return 1 on my
    // NT machine.  So I will instead peek to see if there is a
    // character message in the queue, I hope this can only happen
    // if the translation worked:
    if (PeekMessage(&fl_msg, hWnd, WM_CHAR, WM_SYSDEADCHAR, 1)) {
      uMsg = fl_msg.message;
      wParam = fl_msg.wParam;
      lParam = fl_msg.lParam;
      goto STUPID_MICROSOFT;
    }
    // otherwise use it as a 0-character key...
  case WM_DEADCHAR:
  case WM_SYSDEADCHAR:
    buffer[0] = 0;
    Fl::e_text = buffer;
    Fl::e_length = 0;
    goto GETSTATE;
  case WM_CHAR:
  case WM_SYSCHAR:
    buffer[0] = char(wParam);
    Fl::e_text = buffer;
    Fl::e_length = 1;
  GETSTATE:
    {ulong state = Fl::e_state & 0xff000000; // keep the mouse button state
     // if GetKeyState is expensive we might want to comment some of these out:
      if (GetKeyState(VK_SHIFT)&~1) state |= FL_SHIFT;
      if (GetKeyState(VK_CAPITAL)) state |= FL_CAPS_LOCK;
      if (GetKeyState(VK_CONTROL)&~1) state |= FL_CTRL;
      // Alt gets reported for the Alt-GR switch on foreign keyboards.
      // so we need to check the event as well to get it right:
      if ((lParam&(1<<29)) //same as GetKeyState(VK_MENU)
	&& uMsg != WM_CHAR) state |= FL_ALT;
      if (GetKeyState(VK_NUMLOCK)) state |= FL_NUM_LOCK;
      if (GetKeyState(VK_LWIN)&~1 || GetKeyState(VK_RWIN)&~1) state |= FL_META;
      if (GetKeyState(VK_SCROLL)) state |= FL_SCROLL_LOCK;
      Fl::e_state = state;}
    if (lParam & (1<<31)) goto DEFAULT; // ignore up events after fixing shift
    // for (int i = lParam&0xff; i--;)
    while (window->parent()) window = window->window();
    if (Fl::handle(FL_KEYBOARD,window)) return 0;
    break;

  case WM_GETMINMAXINFO:
    Fl_X::i(window)->set_minmax((LPMINMAXINFO)lParam);
    break;

  case WM_SIZE:
    if (!window->parent()) {
      if (wParam == SIZE_MINIMIZED || wParam == SIZE_MAXHIDE) {
	Fl::handle(FL_HIDE, window);
      } else {
	Fl::handle(FL_SHOW, window);
	resize_bug_fix = window;
	window->size(LOWORD(lParam), HIWORD(lParam));
      }
    }
    break;

  case WM_MOVE:
    resize_bug_fix = window;
    window->position(LOWORD(lParam), HIWORD(lParam));
    break;

  case WM_SETCURSOR:
    if (LOWORD(lParam) == HTCLIENT) {
      while (window->parent()) window = window->window();
      SetCursor(Fl_X::i(window)->cursor);
      return 0;
    }
    break;

#if USE_COLORMAP
  case WM_QUERYNEWPALETTE :
    fl_GetDC(hWnd);
    if (fl_select_palette()) InvalidateRect(hWnd, NULL, FALSE);
    break;
       
  case WM_PALETTECHANGED:
    fl_GetDC(hWnd);
    if ((HWND)wParam != hWnd && fl_select_palette()) UpdateColors(fl_gc);
    break;

  case WM_CREATE :
    fl_GetDC(hWnd);
    fl_select_palette();
    break;
#endif

  default:
  DEFAULT:
    if (Fl::handle(0,0)) return 0;
    break;
  }

  return DefWindowProc(hWnd, uMsg, wParam, lParam);
}

////////////////////////////////////////////////////////////////

void Fl_Window::resize(int X,int Y,int W,int H) {
  int resize_from_program = 1;
  if (this == resize_bug_fix) {
    resize_from_program = 0;
    resize_bug_fix = 0;
  }
  if (X==x() && Y==y() && W==w() && H==h()) return;
  if (X != x() || Y != y()) set_flag(FL_FORCE_POSITION);
  if (W != w() || H != h()) Fl_Group::resize(X,Y,W,H); else {x(X); y(Y);}
  if (resize_from_program && shown()) {
    if (border() && !parent()) {
      X -= GetSystemMetrics(SM_CXFRAME);
      Y -= GetSystemMetrics(SM_CYFRAME)+GetSystemMetrics(SM_CYCAPTION);
      W += 2*GetSystemMetrics(SM_CXFRAME);
      H += 2*GetSystemMetrics(SM_CYFRAME)+GetSystemMetrics(SM_CYCAPTION);
    }
    MoveWindow(i->xid, X, Y, W, H, TRUE);
    //if (!parent()) redraw();
  }
}

////////////////////////////////////////////////////////////////

char fl_show_iconic;	// hack for Fl_Window::iconic()
// int fl_background_pixel = -1; // color to use for background
HCURSOR fl_default_cursor;
int fl_disable_transient_for; // secret method of removing TRANSIENT_FOR

Fl_X* Fl_X::make(Fl_Window* w) {
  Fl_Group::current(0); // get rid of very common user bug: forgot end()
  w->clear_damage(); // wait for expose events

  static char* class_name;
  if (!class_name) {	// create a single WNDCLASS used for everything:
    class_name = "FLTK";
    WNDCLASSEX wc;
    wc.style = CS_HREDRAW | CS_VREDRAW | CS_CLASSDC | CS_DBLCLKS;
    wc.lpfnWndProc = (WNDPROC)WndProc;
    wc.cbClsExtra = wc.cbWndExtra = 0;
    wc.hInstance = fl_display;
    wc.hIcon = wc.hIconSm = LoadIcon(NULL, IDI_APPLICATION);
    wc.hCursor = fl_default_cursor = LoadCursor(NULL, IDC_ARROW);
    //uchar r,g,b; Fl::get_color(FL_GRAY,r,g,b);
    //wc.hbrBackground = (HBRUSH)CreateSolidBrush(RGB(r,g,b));
    wc.hbrBackground = NULL;
    wc.lpszMenuName = NULL;
    wc.lpszClassName = class_name;
    wc.cbSize = sizeof(WNDCLASSEX);
    RegisterClassEx(&wc);
  }

  HWND parent;
  DWORD style;
  DWORD styleEx;
  int xp = w->x();
  int yp = w->y();
  int wp = w->w();
  int hp = w->h();

  if (w->parent()) {
    style = WS_CHILD | WS_CLIPCHILDREN | WS_CLIPSIBLINGS;
    styleEx = WS_EX_LEFT | WS_EX_WINDOWEDGE | WS_EX_CONTROLPARENT;
    parent = fl_xid(w->window());
  } else {
    if (!w->size_range_set) {
      if (w->resizable()) {
	Fl_Widget *o = w->resizable();
	int minw = o->w(); if (minw > 100) minw = 100;
	int minh = o->h(); if (minh > 100) minh = 100;
	w->size_range(w->w() - o->w() + minw, w->h() - o->h() + minh, 0, 0);
      } else {
	w->size_range(w->w(), w->h(), w->w(), w->h());
      }
    }
    if (w->border()) {
      style = WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU
	| WS_CLIPCHILDREN | WS_CLIPSIBLINGS;
      styleEx = WS_EX_LEFT | WS_EX_WINDOWEDGE | WS_EX_CONTROLPARENT;
      if (w->maxw != w->minw || w->maxh != w->minh)
	style |= WS_THICKFRAME | WS_MAXIMIZEBOX;
      if (!w->modal()) style |= WS_MINIMIZEBOX;
      xp -= GetSystemMetrics(SM_CXFRAME);
      yp -= GetSystemMetrics(SM_CYFRAME)+GetSystemMetrics(SM_CYCAPTION);
      wp += 2*GetSystemMetrics(SM_CXFRAME);
      hp += 2*GetSystemMetrics(SM_CYFRAME)+GetSystemMetrics(SM_CYCAPTION);
    } else {
      style = WS_POPUP | WS_CLIPCHILDREN | WS_CLIPSIBLINGS | WS_OVERLAPPED;
      styleEx = WS_EX_LEFT | WS_EX_TOPMOST | WS_EX_TOOLWINDOW;
    }
    if (!(w->flags() & Fl_Window::FL_FORCE_POSITION)) {
      xp = yp = CW_USEDEFAULT;
    }
    parent = 0;
    if (w->non_modal() && !fl_disable_transient_for) {
      // find some other window to be "transient for":
      for (Fl_X* y = Fl_X::first; y; y = y->next) {
	Fl_Window* w = y->w;
	while (w->parent()) w = w->window();
	if (!w->non_modal()) {
	  parent = fl_xid(w);
	  break;
	}
      }
    }
  }

  Fl_X* x = new Fl_X;
  x->other_xid = 0;
  x->setwindow(w);
  x->region = 0;
  x->private_dc = 0;
  x->cursor = fl_default_cursor;
  x->xid = CreateWindowEx(
    styleEx,
    class_name, w->label(), style,
    xp, yp, wp, hp,
    parent,
    NULL, // menu
    fl_display,
    NULL // creation parameters
    );
  x->next = Fl_X::first;
  Fl_X::first = x;

  // use w->xclass() to set the icon...

  w->set_visible();
  w->handle(FL_SHOW); // get child windows to appear
  ShowWindow(x->xid, fl_show_iconic ? SW_MINIMIZE : SW_SHOW);
  fl_show_iconic = 0;
  fl_fix_focus();
  return x;
}

////////////////////////////////////////////////////////////////

HINSTANCE fl_display;

int Fl_WinMain(HINSTANCE hInstance, LPSTR lpCmdLine, int nCmdShow,
	       int (*mainp)(int, char**)) {
  fl_display = hInstance;

  int argc;
  char **argv;
  // test version for now:
  argc = 1; char* testargv[] = {"test", 0}; argv = testargv;

  return mainp(argc, argv);
}

////////////////////////////////////////////////////////////////

void Fl_Window::size_range_() {
  size_range_set = 1;
}

void Fl_X::set_minmax(LPMINMAXINFO minmax)
{
  int wd, hd;
  if (w->border()) {
    wd = 2*GetSystemMetrics(SM_CXFRAME);
    hd = 2*GetSystemMetrics(SM_CYFRAME) + GetSystemMetrics(SM_CYCAPTION);
  } else {
    wd = hd = 0;
  }
  minmax->ptMinTrackSize.x = w->minw + wd;
  minmax->ptMinTrackSize.y = w->minh + hd;
  if (w->maxw) {
    minmax->ptMaxTrackSize.x = w->maxw + wd;
    minmax->ptMaxSize.x = w->maxw + wd;
  }
  if (w->maxh) {
    minmax->ptMaxTrackSize.y = w->maxh + hd;
    minmax->ptMaxSize.y = w->maxh + hd;
  }
}

////////////////////////////////////////////////////////////////

// returns pointer to the filename, or null if name ends with '/'
const char *filename_name(const char *name) {
  const char *p,*q;
  q = name;
  if (q[0] && q[1]==':') q += 2; // skip leading drive letter
  for (p = q; *p; p++) if (*p == '/' || *p == '\\') q = p+1;
  return q;
}

void Fl_Window::label(const char *name,const char *iname) {
  Fl_Widget::label(name);
  iconlabel_ = iname;
  if (shown() && !parent()) {
    if (!name) name = "";
    SetWindowText(i->xid, name);
    // if (!iname) iname = filename_name(name);
    // should do something with iname here...
  }
}

////////////////////////////////////////////////////////////////
// Implement the virtual functions for the base Fl_Window class:

// If the box is a filled rectangle, we can make the redisplay *look*
// faster by using X's background pixel erasing.  We can make it
// actually *be* faster by drawing the frame only, this is done by
// setting fl_boxcheat, which is seen by code in fl_drawbox.C:
// For WIN32 it looks like all windows share a background color, so
// I use FL_GRAY for this and only do this cheat for windows that are
// that color.
// Actually it is totally disabled.
// Fl_Widget *fl_boxcheat;
//static inline int can_boxcheat(uchar b) {return (b==1 || (b&2) && b<=15);}

void Fl_Window::show() {
  if (!shown()) {
    // if (can_boxcheat(box())) fl_background_pixel = fl_xpixel(color());
    Fl_X::make(this);
  } else {
    ShowWindow(i->xid, SW_RESTORE);
    SetActiveWindow(i->xid);
  }
}

Fl_Window *Fl_Window::current_;
HDC window_dc;
// the current context
HDC fl_gc = 0;
// the current window handle, initially set to -1 so we can correctly
// allocate fl_GetDC(0)
HWND fl_window = (HWND)-1;

// Here we ensure only one GetDC is ever in place. There is a little
// workaround for the case of direct_paint.
HDC fl_GetDC(HWND w) {
 /*
  if (fl_direct_paint) {
    if (w == direct_paint_window) return direct_paint_dc;
  } 
*/
  if (fl_gc) {
    if (w == fl_window) return fl_gc;
    ReleaseDC(fl_window, fl_gc);
  }
  fl_gc = GetDC(w);
  fl_window = w;
  // calling GetDC seems to always reset these: (?)
  SetTextAlign(fl_gc, TA_BASELINE|TA_LEFT);
  SetBkMode(fl_gc, TRANSPARENT);
  return fl_gc;
}

// make X drawing go into this window (called by subclass flush() impl.)
void Fl_Window::make_current() {
  fl_GetDC(fl_xid(this));
  current_ = this;
}

// WM_PAINT events and cropped damage call this:
void Fl_Window::expose(uchar flags,int X,int Y,int W,int H) {
  if (i) {
    Region temp= XRectangleRegion(X,Y,W,H);
    if (i->region) {
      CombineRgn(temp,temp,i->region,RGN_AND);
      DeleteObject((HGDIOBJ)i->region);
    }
    i->region=temp;
  }
  damage(flags);
}

#include <FL/fl_draw.H>

void Fl_Widget::damage(uchar flags) {
  if (type() < FL_WINDOW) {
    damage(flags, x(), y(), w(), h());
  } else {
    Fl_X* i = Fl_X::i((Fl_Window*)this);
    if (i) {
      if (i->region) {DeleteObject((HGDIOBJ)i->region); i->region = 0;}
      damage_ |= flags;
      Fl::damage(1);
    }
  }
}

void Fl_Widget::redraw() {damage(~0);}

Region XRectangleRegion(int x, int y, int w, int h); // in fl_rect.C

void Fl_Widget::damage(uchar flags, int X, int Y, int W, int H) {
  if (type() < FL_WINDOW) {
    damage_ |= flags;
    if (parent()) parent()->damage(1,X,Y,W,H);
  } else {
    // see if damage covers entire window:
    if (X<=0 && Y<=0 && W>=w() && H>=h()) {damage(flags); return;}
    Fl_X* i = Fl_X::i((Fl_Window*)this);
    if (i) {
      if (damage()) {
	// if we already have damage we must merge with existing region:
	if (i->region) {
	  Region r = XRectangleRegion(X,Y,W,H);
	  CombineRgn(i->region,i->region,r,RGN_OR);
	  DeleteObject(r);
	}
	damage_ |= flags;
      } else {
	// create a new region:
	if (i->region) DeleteObject(i->region);
	i->region = XRectangleRegion(X,Y,W,H);
	damage_ = flags;
      }
      Fl::damage(1);
    }
  }
}

void Fl_Window::flush() {
  make_current();
  if (damage() & ~6) {
    draw();
  } else {
    fl_clip_region(i->region);
    draw();
    fl_pop_clip();
  }
}

// End of Fl_win32.C //
