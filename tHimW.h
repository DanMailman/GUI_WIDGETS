/* tHimW.h - Interface for Help/Info/Msg Wdg */

#ifndef HIMW_H
#define HIMW_H

#include <cstddef>     // size_t

#include <FL/Fl_Box.H> // Fl_Box

struct tHimW : Fl_Box {
   tHimW(size_t, size_t, size_t, size_t);
};

#endif // HIMW_H
