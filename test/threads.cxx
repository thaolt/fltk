#include <FL/Fl.H>
#include <FL/Fl_Window.H>
#include <FL/Fl_Browser.H>
#include <stdio.h>

Fl_Thread prime_thread;

Fl_Browser *browser1, *browser2;

void* prime_func(void* p)
{
  Fl_Browser* browser = (Fl_Browser*) p;

  // very loosy prime number calculator !
  for (int n=1000000; ; n++) {
    int p;
    for (p=2; p<n; p++) if ( n%p == 0 ) break;
    if (p == n) {
      char s[128];
      sprintf(s, "%d", n);
      Fl::lock();
      browser->add(s);
      Fl::unlock();
      Fl::awake((void*)0x80008000);	// Cause the browser to redraw ...
    }
  }
  return 0;
}

int main()
{
  Fl_Window* w = new Fl_Window(200, 300, "Multithread test");
  browser1 = new Fl_Browser(0, 0, 200, 300);
  w->end();
  w->show();
  w = new Fl_Window(200, 300, "Multithread test");
  browser2 = new Fl_Browser(0, 0, 200, 300);
  w->end();
  w->show();
  
  browser1->add("Prime numbers :");
  browser2->add("Prime numbers :");


  // One thread displaying in one browser
  Fl::create_thread(prime_thread, prime_func, browser1);
  // Several threads displaying in another browser
  Fl::create_thread(prime_thread, prime_func, browser2);
  Fl::create_thread(prime_thread, prime_func, browser2);
  Fl::create_thread(prime_thread, prime_func, browser2);
  Fl::create_thread(prime_thread, prime_func, browser2);
  Fl::create_thread(prime_thread, prime_func, browser2);
  Fl::create_thread(prime_thread, prime_func, browser2);

//  Fl::run();
  while( Fl::wait() ) {
     printf("%x\n", Fl::thread_message);
  }

  return 0;
}
