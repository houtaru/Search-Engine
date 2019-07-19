#ifndef COLORS_H_DEFINED
#define COLORS_H_DEFINED

// #include <engine/utils/String.hpp>

// #include <string>
// #include <vector>
// #include <ncurses.h>

// struct Color {
//     // Color name.
//     // @note If it's empty, means use rbg color.
//     std::string name;

//     // Basic color components of the color, from 0 to 255.
//     // @note If it's -1,means use the name string.
//     int red, green, blue;

//     // Internal value for the ncurses library.
//     short ncurses_color;

//     // Create a new color from its human-readable name.
//     // @note If you want to create a color from its RGB values, use Colors::rgb().
//     Color(std::string name = "white");

//     // Return a string representation of this Color.
//     // @note It can be convert back using `fromString`.
//     // 
//     // The format is "red,green,blue".
//     std::string toString();

//     // Make a color according to a string representation of a Color.
//     // @note it must be a value returned from `toString`.
//     static Color fromString(std::string str);
// };

// struct ColorPair {
//     Color foreground, background;

//     // Is it bold? 
//     // Or, Is it brighter than its normal counterpart?
//     bool bold;

//     // Internal ncurses value for a color pair.
//     chtype ncurses_pair;

//     // Create an empty ColorPair.
//     // @note Default to `white` over `black`
//     ColorPair();

//     // Create a ColorPair from borth colors.
//     ColorPair(Color foreground, Color background);

//     // Create a string represent for a ColorPair
//     // @note Use later with `fromString`
//     // 
//     // The format is `foreground+background`
//     // If the color is bold, its has `!` at the end.    
//     std::string toString();

//     // Make a ColorPair be according to a string representation returned by `toString`.
//     static ColorPair fromString(std::string str);
// };

// namespace Colors {
//     // Tells if this terminal has support for colors (most like it does).
//     // @note It only gets update after calling `Colors::init()`.
//     extern bool hasColors;

//     // Initialize support for colors on the terminal.
//     bool init();

//     // Return a new color with red, green and blue components.
//     // @note They go from 0(none) to 255(full).
//     Color rgb(short red, short green, short blue);

//     // Return a new Color with hex notation.
//     Color hex(std::string str);

//     // Return a new Color from a human-readable string.
//     // @note It is very limited, only have 8 basic ncurses colors.
//     Color name(std::string str);

//     // Return a new `ColorPair` made with #foreground and #background colors.
//     // @note #is_bold usually brightens the color.
//     ColorPair pair(Color& foreground, Color& background, bool is_bold = false);

//     // Return a new `ColorPair` made with human-readable strings.
//     //
//     // @see Colors::pair()
//     // @see Colors::fromString()
//     ColorPair pair(std::string foreground, std::string background, bool is_bold = false);

//     // Activates the color #foreground and #background on a ncurses #window.
//     // It has the effect of makeing all subsequent prints having this color pair.
//     //
//     // @note Default of #window is ncurses default window
//     void activate(WINDOW * window, Color& foregound, Color& background);

//     // Activates the color pair #color on a ncurses #window
//     // @note Default of #window is ncurses default window
//     // 
//     // @see Colors::activate()
//     void pairActivate(WINDOW * window, ColorPair& color);

//     // De-actives the color pair #color on a ncurses #window
//     // @note Default of #window is ncurses default window
//     void pairDeactive(WINDOW *window = stdscr, ColorPair& color);
// }

#endif