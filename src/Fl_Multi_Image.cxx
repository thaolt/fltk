#include <fltk/MultiImage.h>

using namespace fltk;

void MultiImage::measure(float& w, float& h) const {
  images[0]->measure(w,h);
}

void MultiImage::draw(float x, float y, float w, float h, Flags f) const
{
  int which = 0;
  Flags passed_flags = f;
  for (int i = 1; i < MAXIMAGES; i++) {
    if (!images[i]) break;
    // Test to make sure all the requested flags are on:
    if ((f & flags[i]) == flags[i]) {which = i; passed_flags = f&~flags[i];}
  }
  images[which]->draw(x,y,w,h,passed_flags);
}
