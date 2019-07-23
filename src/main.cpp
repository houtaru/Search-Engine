#include <Engine/EngineGlobals.hpp>
#include <Engine/Graphics/Ncurses.hpp>
#include <Engine/Graphics/Colors.hpp>
#include <Engine/Graphics/Window.hpp>

#include <Engine/Utils/String.hpp>

#include <iostream>

void run() {
    // Window * window = new Window(2, 2, 10, 10);
    // window->clear();
    // window->print("hello", 1, 1, Colors::pair("yellow", "default", true));
    // window->refresh();

    ColorPair p = Colors::pair("yellow", "default", true);
    Colors::pairActivate(stdscr, p);
    mvprintw(2, 2, "aaa");
    Colors::pairDeactivate(stdscr, p);
    refresh();

    Ncurses::getInput();
}

int main(int argc, char **argv) {
    try {
        // Settings
        EngineGlobals::init();
        Ncurses::init();
        Colors::init();

        run();

        Ncurses::exit();
    } catch (...) {
        Ncurses::exit();
        throw "Error!!";
        return 1;
    }

    return 0;
}