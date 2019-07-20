#ifndef WINDOW_H_DEFINED
#define WINDOW_H_DEFINED

#include <string>
#include <vector>
#include <ncurses.h>

#include <Engine/Graphics/Colors.hpp>


// Handy alias to make child Windows stretch their size to the maximum allowed by the parent.
#define WINDOW_FILL 0

// A segment of the terminal screen (2D char matrix).
class Window {
    public:
        enum BorderType {
            BORDER_NONE, BORDER_REGULAR, BORDER_FANCY
        };

        Window(int x, int y, int w, int h);

        Window(Window * parent, int x, int y, int width, int height);

        virtual ~Window();

        virtual void resize(int w, int h);

        // Show the text #str at #x, #y on the window with the color #pair.

        // @note It defaults to white and text on black background.
        void print(std::string str, int x, int y, ColorPair p = ColorPair());

        // Show multiple text lines #lines at #x, #y on the window with color #pair

        // @note It defaults to white and text on black background.
        // @note Use it together eith `Utils::String::split()`
        void print(std::vector < std::string > lines, int x, int y, ColorPair p = ColorPair());

        // Show #c at #x #y with color pair.
        // @note It also defaults to white text on the black ground.
        void printChar(int c, int x, int y, ColorPair p = ColorPair());

        void setBackground(chtype ch, ColorPair p);

        void refresh();

        void clear();

        int getW() const;
        int getH() const;
        int getX() const;
        int getY() const;

        // Applies border of #type to this Window
        void borders(BorderType type);

        // Apllies a board style dependent on the EngineGlobals settings
        void setBorders();

        void horizontalLine(int x, int y, int c, int width, ColorPair p);

protected:
    WINDOW * win;

    int x;
    int y;
    int width;
    int height;

    BorderType borderType;
};

#endif      // WINDOW_H_DEFINED