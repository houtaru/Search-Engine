#ifndef __FRONTEND__
#define __FRONTEND__

#include <ncurses.h>
#include <utils.h>
#include <Ranking.hpp>

using namespace std;

struct Frontend {
    void draw_rectangle(int x1, int y1, int x2, int y2);
    void draw_logo(int x1, int x2);
    void search_scr(Trie &trie, char *input_search);
    void main_scr();
};

#endif //__FRONTEND__
