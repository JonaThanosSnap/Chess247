#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <iostream>
#include <cstdlib>
#include <string>
#include <unistd.h>
#include "window.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

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
    for (auto kv : imageMap) {
        XDestroyImage(kv.second);
    }
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

void Xwindow::fillRectangle(int x, int y, int width, int height, int color) {
    XSetForeground(d, gc, getColor(color));
    XFillRectangle(d, w, gc, x, y, width, height);
    XSetForeground(d, gc, Black);
}

void Xwindow::drawString(int x, int y, std::string msg, int color) {
    XSetForeground(d, gc, getColor(color));
    XDrawString(d, w, gc, x, y, msg.c_str(), msg.length());
    XSetForeground(d, gc, Black);
}

// Add image
// Takes a png
void Xwindow::addImage(std::string file) {
    //imageMap[file] = createTrueColorImage(d, DefaultVisual(d, 0), width, height);
    int x, y, n;
    unsigned char* imgdata = stbi_load(file.c_str(), &x, &y, &n, 4);
    unsigned char* p = imgdata;

    int nPixels = x*y;

    for (int i = 0; i < nPixels; i++) {
        unsigned char tmp = p[0];
        p[0] = p[2];
        p[2] = tmp;
        p = p + n;
    }

    imageMap[file] = XCreateImage(d, DefaultVisual(d, 0), 24, ZPixmap, 0, (char*)imgdata, x, y, 32, 0);
}

// Draw image
void Xwindow::putImage(std::string file, int x, int y, int width, int height) {
    XPutImage(d, w, gc, imageMap.at(file), 0, 0, x-width/2, y-height/2, width, height);
}
