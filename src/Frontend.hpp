#ifndef __FRONTEND__
#define __FRONTEND__

#include <ncurses.h>

#include <string>
#include <vector>

struct Color {
    std::string name;
    int red, green, blue;

    short ncurses_color;

    Color(std::string name = "white");

    std::string toString();

    static Color fromString(std::string str);
};

struct ColorPair {
    Color foregound, background;

    bool bold;

    chtype ncurses_pair;

    ColorPair();

    ColorPair(Color foregound, Color background);

    std::string toString();

    static ColorPair fromString(std::string str);
};

namespace Color {
    extern bool hasColors;

    bool init();

    Color rgb(short red, short green, short blue);

    Color hex(std::string hex);

    Color name(std::string str);

    ColorPair(Color& foregound, Color& background, bool is_bold = false);

    ColorPair pair(std::string foreground, std::string background, bool is_bold = false);

    void active(WINDOW * )
};
