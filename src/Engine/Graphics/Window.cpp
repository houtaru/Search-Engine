#include <Engine/EngineGlobals.hpp>
#include <Engine/Graphics/Window.hpp>

#include <sstream>          //stringstream
#include <iostream> 

Window::Window(int x, int y, int w, int h): 
    x(x), 
    y(y), 
    width(w), 
    height(h),
    win(NULL),
    borderType(BORDER_NONE),
    topLeftTitle(""),
    topRightTitle(""),
    bottomLeftTitle(""),
    bottomRightTitle("")
{
    this->win = newwin(height, width, y, x);
    if (!this->win)
        throw "Could not create Nucrses window";

    this->setBorders();
}

Window::Window(Window * parent, int x, int y, int width, int height) {
    if (parent->borderType == BORDER_NONE) {
        if (width == 0) width = parent->width;
        if (height == 0) height = parent->height;
    } else {
        // Has borders
        if (x == 0) x = 1;
        if (y == 0) y = 1;

        if (width == 0) width = parent->width - 2;
        if (height == 0) height = parent->height - 2;
    }

    this->x = x;
    this->y = y;
    this->width = width;
    this->height = height;

    // Create subwindow
    this->win = derwin(parent->win, height, width, x, y);
    if (!win)
        throw "Could not create Ncurses window";

    this->setBorders();
}

Window::~Window() {
    if (this->win)
        delwin(this->win);
}