#ifndef NCURSES_H_DEFINED
#define NCURSES_H_DEFINED

namespace Ncurses {
    // Initializes ncurses mode.
    // @warm the whole `Engine` depend on this.
    bool init();

    // Quits ncurses mode.
    // @warning Make sure to call it at the end of the game, otherwise the terminal will be left at a strange site.
    void exit();

    // Return a pressed character within a timespan of #delay_ms (miliseconds).
    // @note If you spend -1, it'll block execution, waiting for the input indefinitely.

    // @note It's #int because ncurses uses some other values that don't fit on a #char variable.
    int getInput(int delay_ms = -1);
};

#endif