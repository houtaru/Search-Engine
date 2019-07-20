#include <Engine/Graphics/Ncurses.hpp>
#include <Engine/Graphics/Window.hpp>

int main() {
    Ncurses::init();
    mvprintw(1, 1, "%d %d", COLS, LINES);
    Ncurses::getInput();
    Ncurses::exit();
}