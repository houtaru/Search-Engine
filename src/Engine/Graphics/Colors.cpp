#include <Engine/Graphics/Colors.hpp>

#include <cstdlib>              //strtol

/**
 * Color definition
 */
Color::Color(std::string name): name(name), red(-1), green(-1), blue(-1), ncurses_color(COLOR_WHITE) {}

std::string Color::toString() {
    if (!this->name.empty()) return this->name;
    return String::toString(this->red) + "," + String::toString(this->green) + "," + String::toString(this->blue);
}

Color Color::fromString(std::string str) {
    if (str.find(",") == std::string::npos) return Colors::name(str);
    std::vector < std::string > c = String::split(str, ',');
    if (c.size() != 3) return Color();
    for (size_t i = 0; i < c.size(); ++i)
        c[i] = String::trim(c[i]);
 
    return Colors::rgb(String::to<int>(c[0]), String::to<int>(c[1]), String::to<int>(c[2]));
}

/**
 * ColorPair definition
 */
ColorPair::ColorPair(): bold(false), ncurses_pair(0) {}

ColorPair::ColorPair(Color foreground, Color background): foreground(foreground), background(background) {}

std::string ColorPair::toString() {

    return foreground.toString() + "+" + background.toString() + (this->bold ? "!" : "");
}

ColorPair ColorPair::fromString(std::string str) {
    size_t is_bold = false;
    if (str.find("!") != std::string::npos) {
        is_bold = true;
        str.pop_back();
    }
    std::vector < std::string > c = String::split(str, '+');
    if (c.size() != 2) return ColorPair();
    Color fg = Color::fromString(c[0]);
    Color bg = Color::fromString(c[1]);
    return Colors::pair(fg, bg, is_bold);
}

/**
 * Colors definition
 */

// Default color of the current terminal.
//
// Thhis is the color your terminal has - both for foreground and background
#define COLOR_DEFAULT -1

bool Colors::hasColors  = false;

bool Colors::init() {
    if (has_colors() == FALSE) {
        Colors::hasColors = false;
        return false;
    }
    Colors::hasColors = true;
    start_color();
    int k = 1;
    for (int i = COLOR_BLACK; i <= COLOR_WHITE; ++i) for (int j = COLOR_BLACK; j <= COLOR_WHITE; ++j) {
        init_pair(k++, i, j);
    }
    // Beside the normal color pairs, we can use whatever colors the user has currently set to their terminal.
    // *It looks more natural.
    if (use_default_colors() != ERR) {
        for (int i = COLOR_BLACK; i <= COLOR_WHITE; ++i)
            init_pair(k++, i, COLOR_DEFAULT);
    }
 
    return true;
}

Color Colors::rgb(short red, short green, short blue) {
    Color color;
    // Since we use rgb, so we left the name blank.
    color.name = "";
    if (can_change_color() == FALSE || COLORS < 256) {
        return color;
    }
    static int color_no = 8;
    color_no++;
    if (color_no >= COLORS) color_no = 8;
    // `init_color` receives values from 0 to 1000, so we'll map from 255 to 1000
    int expand = 1000 / 255;
    init_color((color_no - 1), red * expand, green * expand, blue * expand);
    color.ncurses_color = color_no - 1;
    color.red = red;
    color.green = green;
    color.blue = blue;
 
    return color;
}

Color Colors::hex(std::string str) {
    Color color;
 
    // If not hex color code format.
    if (str[0] != '#' || str.size() != 7) return color;
    // convert hexadecimal to decimal
    char cur[3]; cur[3] = '\0';
    int comps[3];
    for (int i = 1; i <= 3; ++i) {
        cur[0] = str[2 * i - 1];
        cur[1] = str[2 * i];
        comps[i] = strtol(cur, NULL, 16);
    }
    return Colors::rgb(comps[0], comps[1], comps[3]);
}

Color name(std::string str) {
    Color color;
    if (str.empty()) return color;
    if (str == "default") color.ncurses_color = COLOR_DEFAULT;
    if (str == "black") color.ncurses_color = COLOR_BLACK;
    if (str == "red") color.ncurses_color = COLOR_RED;
    if (str == "green") color.ncurses_color = COLOR_GREEN;
    if (str == "yellow") color.ncurses_color = COLOR_YELLOW;
    if (str == "blue") color.ncurses_color = COLOR_BLUE;
    if (str == "magenta") color.ncurses_color = COLOR_MAGENTA;
    if (str == "cyan") color.ncurses_color = COLOR_CYAN;
    if (str == "white") color.ncurses_color = COLOR_WHITE;
 
    color.name = str;
    return color;
}

ColorPair Colors::pair(Color &foreground, Color &background, bool is_bold) {
    ColorPair p(foreground, background);
    if (is_bold) p.bold = true;
    
    short fg = foreground.ncurses_color;
    short bg = background.ncurses_color;
    
    // Basic ncurses colors
    if (fg < 8 && bg < 8) {
        if (bg == COLOR_DEFAULT) {
           p.ncurses_pair = COLOR_PAIR(64 + fg);
           if (is_bold) p.ncurses_pair |= A_BOLD;
 
           return p;
        }
        p.ncurses_pair = COLOR_PAIR(fg * 8 + bg + 1);
        if (is_bold) p.ncurses_pair |= A_BOLD;
        
        return p;
    }

    if (COLORS < 256) {
        p.ncurses_pair = COLOR_PAIR(0);
        if (is_bold) p.ncurses_pair |= A_BOLD;
        return p;
    }
    
    // Create color pair (above 64 regular ones plus 12 default = 72)
    static int color_pair_no = 72;
    color_pair_no++;
    if (color_pair_no >= COLOR_PAIRS) color_pair_no = 72;
    init_pair(color_pair_no - 1, fg, bg);
    
    p.ncurses_pair = COLOR_PAIR(color_pair_no - 1);
    if (is_bold) p.ncurses_pair |= A_BOLD);

    return p;
}

ColorPair Colors::pair(std::string foreground, std::string background, bool is_bold) {
    if (foreground.empty() || background.empty()) return ColorPair();
    
    Color f = Color::fromString(foreground);
    Color b = Color::fromString(background);
    
    return pair(f, b, is_bold);
}

void Colors::activate(WINDOW * window, Color& foregound, Color& background) {
    ColorPair p = pair(foregound, background);
    pairActivate(window, p);
}

void Colors::pairActivate(WINDOW * window, ColorPair& color) {
    wattron(window, color.ncurses_pair);
}

void Colors::pairDeactive(WINDOW * window, ColorPair& color) {
    wattroff(window, color.ncurses_pair);
}