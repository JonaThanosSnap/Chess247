#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <iostream>
#include <cstdlib>
#include <string>
#include <unistd.h>
#include "window.h"

Xwindow::Xwindow(int width, int height) {
    d = XOpenDisplay(NULL);
    if (d == NULL) {
        std::cerr << "Cannot open display" << std::endl;
        exit(1);
    }
    s = DefaultScreen(d);
    w = XCreateSimpleWindow(d, RootWindow(d, s), 10, 10, width, height, 1, BlackPixel(d, s), WhitePixel(d, s));
    XSelectInput(d, w, ExposureMask | KeyPressMask);
    XMapRaised(d, w);

    Pixmap pix = XCreatePixmap(d,w,width,height,DefaultDepth(d,DefaultScreen(d)));
    gc = XCreateGC(d, pix, 0,(XGCValues *)0);

    XFlush(d);
    XFlush(d);

    // Set up colours.
    cmap=DefaultColormap(d,DefaultScreen(d));

    XColor xcolor;

    // Black
    XParseColor(d, cmap, "black", &xcolor);
    XAllocColor(d, cmap, &xcolor);
    Black = xcolor.pixel;

    // White
    XParseColor(d, cmap, "white", &xcolor);
    XAllocColor(d, cmap, &xcolor);
    White = xcolor.pixel;

    XSetForeground(d,gc,colorMap[Black]);

    // Make window non-resizeable.
    XSizeHints hints;
    hints.flags = (USPosition | PSize | PMinSize | PMaxSize );
    hints.height = hints.base_height = hints.min_height = hints.max_height = height;
    hints.width = hints.base_width = hints.min_width = hints.max_width = width;
    XSetNormalHints(d, w, &hints);

    XSynchronize(d,True);

    usleep(1000);
}

Xwindow::~Xwindow() {
    XFreeGC(d, gc);
    XCloseDisplay(d);
}

void Xwindow::addColor(int color, char* r, char* g, char* b) {
    std::string colorString = "rgb:";
    colorString = colorString + r + "/" + g + "/" + b;

    XColor xcolor;
    XParseColor(d, cmap, colorString.c_str(), &xcolor);
    XAllocColor(d, cmap, &xcolor);

    colorMap[color] = xcolor.pixel;
}

unsigned long Xwindow::getColor(int color) const {
    return colorMap.at(color);
}

void Xwindow::fillRectangle(int x, int y, int width, int height, unsigned long color) {
    XSetForeground(d, gc, color);
    XFillRectangle(d, w, gc, x, y, width, height);
    XSetForeground(d, gc, Black);
}

void Xwindow::drawString(int x, int y, std::string msg) {
    XDrawString(d, w, DefaultGC(d, s), x, y, msg.c_str(), msg.length());
}

