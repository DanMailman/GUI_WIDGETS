/* tHimW.cpp - Implementation for Help/Info/Msg Wdg */

#include "tHimW.h" // Interface

tHimW::tHimW(size_t x, size_t y, size_t w, size_t h)
   :Fl_Box(FL_FLAT_BOX,x,y,w,h,""){
   color(FL_WHITE);
   labelcolor(FL_BLACK);
   labelfont(FL_BOLD);
}
