#ifndef __WINDOW_H__
#define __WINDOW_H__
#include <X11/Xlib.h>
#include <iostream>
#include <string>
#include <map>

class Xwindow {
    Display *d;
    Window w;
    Colormap cmap;
    int s;
    GC gc;

    // default colors
    unsigned long Black;
    unsigned long White;

    std::map<int, unsigned long> colorMap;

    public:
        Xwindow(int width=600, int height=600);  // Constructor; displays the window.
        ~Xwindow();                              // Destructor; destroys the window.
        Xwindow(const Xwindow&) = delete;
        Xwindow &operator=(const Xwindow&) = delete;

        // Add color
        // Usage: addColor(White, "ff", "ff", "ff")
        void addColor(int color, char r[3], char g[3], char b[3]);

        // get color
        unsigned long getColor(int color) const;

        // Draws a rectangle
        void fillRectangle(int x, int y, int width, int height, unsigned long color);

        // Draws a string
        void drawString(int x, int y, std::string msg);
};

#endif
