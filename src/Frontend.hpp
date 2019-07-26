#ifndef __FRONTEND__
#define __FRONTEND__

#include <ncurses.h>
#include <Ranking.hpp>
#include <Engine/Graphics/Colors.hpp>
#include <Operator.hpp>
#include <Trie.hpp>

using namespace std;

struct Frontend {
    void draw_rectangle(int x1, int y1, int x2, int y2);
    void draw_logo(int x1, int x2);
    
    void search_scr(Operator &op, string input_search);
    void main_scr(Operator &op);
    void loading_scr();
};

#endif //__FRONTEND__
