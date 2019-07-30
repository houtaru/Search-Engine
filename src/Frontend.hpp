#ifndef __FRONTEND__
#define __FRONTEND__

#include <bits/stdc++.h>
#include <ncurses.h>
#include <Ranking.hpp>
#include <Operator.hpp>
#include <Trie.hpp>

#include <aho_ver2.hpp>

using namespace std;

struct Frontend {
private:
    clock_t Clock;
    vector<string> name;
    vector<string> type;

public:
    Frontend();
    //void draw_rectangle(int x1, int y1, int x2, int y2, bool is_bold = true);
    void draw_logo(int x1, int x2);
    
    void search_scr(Trie &trie, string input_search, Trie& trie_title);
    void main_scr(Trie &trie, Trie& trie_title);
    void loading_scr();
};

#endif //__FRONTEND__