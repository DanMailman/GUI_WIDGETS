/* tWndW.h - Interface for App Wnd Wdg */
// TODO: tWdg
#ifndef WNDW_H
#define WNDW_H

#include <FL/Fl.H>        // Event Loop
#include <FL/Fl_Window.H> // Window Widget 

#include "Utilities.h" // StrP

struct tWndW : Fl_Window {
   tWndW(size_t, size_t, size_t, size_t, StrP); 
};

#endif //WNDW_H
