#include <Frontend.hpp>

int main() {
    Frontend frontend;
    frontend.loading_scr();
}

// #include <Engine/EngineGlobals.hpp>
// #include <Engine/Graphics/Ncurses.hpp>
// #include <Engine/Graphics/Colors.hpp>

// #include <Engine/Utils/String.hpp>

// #include <iostream>

// void run() {
//     // Window * window = new Window(2, 2, 10, 10);
//     // window->clear();
//     // window->print("hello", 1, 1, Colors::pair("yellow", "default", true));
//     // window->refresh();

//     Color x = Colors::rgb(100, 150, 100);
//     Color y = Colors::name("black");
//     ColorPair q = Colors::pair(x, y);
//     ColorPair p = Colors::pair("yellow", "black", true);
//     Colors::pairActivate(stdscr, q);
//     mvprintw(2, 2, "aaa");
//     Colors::pairDeactivate(stdscr, q);
//     refresh();

//     Ncurses::getInput();
// }

// int main(int argc, char **argv) {
//     try {
//         // Settings
//         EngineGlobals::init();
//         Ncurses::init();
//         Colors::init();

//         run();

//         Ncurses::exit();
//     } catch (...) {
//         Ncurses::exit();
//         throw "Error!!";
//         return 1;
//     }

// }


// #include <ncurses.h>
// #include <bits/stdc++.h>

// using namespace std;

// void print_in_middle(WINDOW *win, int starty, int startx, int width, char *string);
// int main(int argc, char *argv[])
// {	initscr();			/* Start curses mode 		*/
// 	if(has_colors() == FALSE)
// 	{	endwin();
// 		printf("Your terminal does not support color\n");
// 		exit(1);
// 	}
// 	start_color();			/* Start color 			*/
// 	init_pair(1, COLOR_RED, COLOR_BLACK);

// 	attron(COLOR_PAIR(1));
// 	print_in_middle(stdscr, LINES / 2, 0, 0, "Viola !!! In color ...");
// 	attroff(COLOR_PAIR(1));
//     	getch();
// 	endwin();
// }
// void print_in_middle(WINDOW *win, int starty, int startx, int width, char *string)
// {	int length, x, y;
// 	float temp;

// 	if(win == NULL)
// 		win = stdscr;
// 	getyx(win, y, x);
// 	if(startx != 0)
// 		x = startx;
// 	if(starty != 0)
// 		y = starty;
// 	if(width == 0)
// 		width = 80;

// 	length = strlen(string);
// 	temp = (width - length)/ 2;
// 	x = startx + (int)temp;
// 	mvwprintw(win, y, x, "%s", string);
// 	refresh();
// }