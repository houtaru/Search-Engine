#include <bits/stdc++.h>
#include <Engine/Graphics/Ncurses.hpp>
#include <Engine/Utils/String.hpp>
#include <ncurses.h>

using namespace std;

enum {
    BLACK,
    RED,
    GREEN,
    YELLOW,
    BLUE,
    MAGENTA,
    CYAN,
    WHITE
};

void clearScr(int x1, int x2) {    //  Clear row x1 to x2
    for (int i = x1; i <= x2; ++i)
        for (int j = 5; j <= COLS - 5; ++j)
            mvaddch(i, j, ' ');
}

void viewDocument(vector<string> query, string name_document) {
    clearScr(12, LINES - 10);
    attron(A_BOLD);

    attron(COLOR_PAIR(MAGENTA));
    mvprintw(13, (COLS - name_document.size())/2, name_document.c_str());
    attroff(COLOR_PAIR(MAGENTA));
    attron(COLOR_PAIR(CYAN));
    mvprintw(LINES-8 + 1, (COLS - 9)/2 + 1, "  BACK  ");
    attroff(COLOR_PAIR(CYAN));

    attroff(A_BOLD);

    ifstream fin("input.in");

    vector <string> cur;
    string curl; while (getline(fin, curl, '\n'))
        cur.push_back(curl);
    vector <string> content;
    for (auto it : cur) {
        string tmp = it;
        while (tmp.size() > 100) {
            int pos = 99; while (tmp[pos] != ' ' && tmp[pos] != '.' && tmp[pos] != ',') pos--;
            content.push_back(tmp.substr(0, pos + 1));
            tmp.erase(0, pos + 1);
        }
        content.push_back(tmp);
    }

    // Pre-calculate #nxt array - the rightmost position that 
    // content[i][k...nxt[i][k] - 1] equal to one of element in #query.
    vector < vector <int> > nxt(content.size());
    for (int i = 0; i < content.size(); ++i) if (!content[i].empty()) {
        nxt[i].resize(content[i].size());
        for (int k = 0; k < content[i].size(); ++k) {
            nxt[i][k] = 0;
            for (auto it : query) if (String::to_lower(content[i].substr(k, it.size())).compare(it) == 0) {
                nxt[i][k] = max(nxt[i][k], int(it.size() + k));
            }
        }
    }

    // Update content when client press KEY_UP or KEY_DOWN
    auto update = [&](int l, int r) {
        clearScr(16, LINES - 10);
        for (int i = l; i < r; ++i) {
            if (content[i].empty()) continue;
            int pos = 54, b = 1;
            for (int k = 0; k < nxt[i].size(); ++k) {
                if (!nxt[i][k]) mvaddch(15 + (i - l + 1), pos++, content[i][k]);
                else {
                    int sz = nxt[i][k] - k;
                    attron(A_BOLD | A_REVERSE);
                    mvaddstr(15 + (i - l + 1), pos, content[i].substr(k, sz).c_str());
                    attroff(A_BOLD | A_REVERSE);
                    k = nxt[i][k] - 1;
                    pos += sz;
                }
            }
        }
        refresh();
    };

    int x = 0;
    update(x, x + 23);
    while (true) {
        MEVENT mouse;
        mousemask(ALL_MOUSE_EVENTS, NULL);

        int input = getch();
        if (input == KEY_MOUSE) {
            if (getmouse(&mouse) == OK) {
                if (mouse.bstate & BUTTON1_CLICKED) {
                    if (mouse.y == LINES-8 + 1 && mouse.x >= (COLS - 9)/2 + 1 && mouse.x <= (COLS - 9)/2 +8)
                        break;
                }
            }
        }
        if (input == KEY_UP) {
            if (x + 23 < content.size()) x--;
        }
        if (input == KEY_DOWN) {
            if (x > 0) x++;
        }
        if (input == '\n')
            break; 
        update(x, x + 23);
    }

    clearScr(12, LINES - 10);
}

int main() {
    try {
        Ncurses::init();
        vector <string> query = {"administration"};
        viewDocument(query, "input.in");
        Ncurses::exit();
    } catch (...) {
        Ncurses::exit();
        throw "Error";
    }
    
    return 0;
}

// #include <Frontend.hpp>

// int main() {
//     Frontend frontend;
//     frontend.loading_scr();
//     return 0;
// }