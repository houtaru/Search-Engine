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
    borderType(BORDER_NONE)
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

void Window::resize(int w, int h) {
    wresize(this->win, w, h);

    this->width = w;
    this->height = h;
}

void Window::print(std::string str, int x, int y, ColorPair p) {
    Colors::pairActivate(this->win, p);
    if (!str.empty()) {
        mvwaddstr(this->win, y, x, str.c_str());
    }
    Colors::pairDeactivate(this->win, p);
}

void Window::print(std::vector < std::string > lines, int x, int y, ColorPair p) {
    for (size_t i = 0; i < lines.size(); ++i)
        this->print(lines[i], x, y, p);
}

void Window::printChar(int c, int x, int y, ColorPair p) {
    Colors::pairActivate(this->win, p);
    mvwaddch(this->win, y, x, c);
    Colors::pairDeactivate(this->win, p);
}

void Window::setBackground(chtype ch, ColorPair p) {
    wbkgd(this->win, ch | p.ncurses_pair);
}

void Window::refresh() {
    // wrefresh(this->win) gets heavy to do the former.
    // So I use wnoutrefresh(this->win).
    // @note You need to call `refresh()` at the end of every draw cycle.
    //wnoutrefresh(this->win);
    wrefresh(this->win);
}

void Window::clear() {
    werase(this->win);
    
    // Redrawing borders if existing
    if (this->borderType != BORDER_NONE) 
        this->borders(this->borderType);
}

int Window::getW() const { return this->width; }

int Window::getH() const { return this->height; }

int Window::getX() const { return this->x; }

int Window::getY() const { return this->y; }

void Window::borders(BorderType type) {
    this->borderType = type;
    if (type == BORDER_NONE) return;

    if (type == Window::BORDER_FANCY) {
        wborder(this->win,
		        ACS_VLINE    | Colors::pair("white", "default"      ).ncurses_pair,
		        ACS_VLINE    | Colors::pair("black", "default", true).ncurses_pair,
		        ACS_HLINE    | Colors::pair("white", "default"      ).ncurses_pair,
		        ACS_HLINE    | Colors::pair("black", "default", true).ncurses_pair,
		        ACS_ULCORNER | Colors::pair("white", "default", true).ncurses_pair,
		        ACS_URCORNER | Colors::pair("white", "default"      ).ncurses_pair,
		        ACS_LLCORNER | Colors::pair("white", "default"      ).ncurses_pair,
		        ACS_LRCORNER | Colors::pair("black", "default", true).ncurses_pair);
    }
    if (type == Window::BORDER_REGULAR) {
        wborder(this->win, ACS_VLINE, ACS_VLINE, ACS_HLINE, ACS_HLINE, 
                ACS_ULCORNER, ACS_URCORNER, ACS_LLCORNER, ACS_LRCORNER);
    }
}

void Window::setBorders() {
    if (EngineGlobals::Screen::show_borders) {
        this->borders(EngineGlobals::Screen::fancy_borders ? 
                        Window::BORDER_FANCY : Window::BORDER_REGULAR);
    }
}

void Window::horizontalLine(int x, int y, int c, int width, ColorPair p) {
    Colors::pairActivate(this->win, p);
    mvwhline(this->win, y, x, c, width);
    Colors::pairDeactivate(this->win, p);
}