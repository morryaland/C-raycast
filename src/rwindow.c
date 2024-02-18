#include "rwindow.h"

int SCREEN_WIDTH=1920;
int SCREEN_HEIGHT=1080;

#ifdef __linux__

#include <X11/Xlib.h>
#include <stdlib.h>

Display *d;
Window w;
XEvent e;
int s;

STATUS create_window() {
  if ( (d = XOpenDisplay(getenv("DISPLAY"))) == NULL ) {
    puts("Can't connect X server");
    goto error_open_display;
  }
  s = XDefaultScreen(d);
  w = XCreateSimpleWindow( d, RootWindow(d, s), 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, 1,
                           XBlackPixel(d, s), XWhitePixel(d, s) );
  XSelectInput( d, w, ExposureMask | KeyPressMask );
  XMapWindow( d, w );
  #ifdef DEBUG
    puts("INFO: window create");
  #endif
  return SUCCESS;
  error_open_display:
  return ERROR_DISPLAY;
}

int next_event() {
  XNextEvent( d, &e );
  if ( e.type == KeyPress )
    return 1;
  return 0;
}

STATUS window_clear() {
  if (e.type == Expose) {
    XFillRectangle( d, w, DefaultGC(d, s), 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT ); 
    return SUCCESS;
  }
  return ERROR_CLEAR_WINDOW;
}

void close_window() {
  XCloseDisplay(d);
  #ifdef DEBUG
    puts("INFO: window close");
  #endif
  return;
}

#elif _WIN32



#else

#endif
