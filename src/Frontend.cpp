#include <Frontend.hpp>
#include <Engine/Utils/String.hpp>
#include <Trie.hpp>

Frontend::Frontend() {
    //  Get name of documents
    ifstream fin("TextData2/___index.txt");
    string sub;
    while (getline(fin, sub)) {
        name.push_back(sub);
        size_t index = sub.find_last_of('.');
        if (index != std::string::npos)
            type.push_back(sub.substr(index+1));
    }
    fin.close();
}

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

void draw_rectangle(int x1, int y1, int height, int width, bool is_bold = true) {
    if (is_bold) attron(A_BOLD);
    int x2 = x1 + height, y2 = y1 + width;
    for (int i = x1; i <= x2; ++i) {
        mvaddch(i, y1, ACS_VLINE);
        mvaddch(i, y2, ACS_VLINE);
    }
    for (int i = y1; i <= y2; ++i) {
        mvaddch(x1, i, ACS_HLINE);
        mvaddch(x2, i, ACS_HLINE);
    }

    mvaddch(x1, y1, ACS_ULCORNER);
    mvaddch(x1, y2, ACS_URCORNER);
    mvaddch(x2, y1, ACS_LLCORNER);
    mvaddch(x2, y2, ACS_LRCORNER);
    refresh();
    if (is_bold) attroff(A_BOLD);
}


void Frontend::draw_logo(int x1, int x2) {  //  x1, x2 is the coordinate according to the center of the screen
    attron(A_BOLD);
    vector<string> logo = {
        "   ___                                            ",
        "  /   |                                           ",
        " / /| | _ __  __ _  _ __    __ _   ___  _ __  ___ ",
        "/ /_| || '__|/ _` || '_ \\  / _` | / _ \\| '__|/ __|",
        "\\___  || |  | (_| || | | || (_| ||  __/| |   \\__ \\",
        "    |_/|_|   \\__,_||_| |_| \\__, | \\___||_|   |___/",
        "                            __| |                 ",
        "                           |____/                 "
    };
    for (int i = 0; i < (int)logo.size(); ++i) {
        //  Draw 4
        attron(COLOR_PAIR(BLUE));
        for (int j = 0; j < 7; ++j) {
            mvaddch(LINES/2 - logo.size() + x1 + i, COLS/2 - logo[0].size()/2 + x2 + j, logo[i][j]);
        }
        attroff(COLOR_PAIR(BLUE));

        //  Draw r
        attron(COLOR_PAIR(RED));
        for (int j = 7; j < 13; ++j) {
            mvaddch(LINES/2 - logo.size() + x1 + i, COLS/2 - logo[0].size()/2 + x2 + j, logo[i][j]);
        }
        attroff(COLOR_PAIR(RED));

        //  Draw a
        attron(COLOR_PAIR(YELLOW));
        for (int j = 13; j < 19; ++j) {
            mvaddch(LINES/2 - logo.size() + x1 + i, COLS/2 - logo[0].size()/2 + x2 + j, logo[i][j]);
        }
        attroff(COLOR_PAIR(YELLOW));

        //  Draw n
        attron(COLOR_PAIR(GREEN));
        for (int j = 19; j < 26; ++j) {
            mvaddch(LINES/2 - logo.size() + x1 + i, COLS/2 - logo[0].size()/2 + x2 + j, logo[i][j]);
        }
        attroff(COLOR_PAIR(GREEN));

        //  Draw g
        attron(COLOR_PAIR(BLUE));
        for (int j = 26; j < 33; ++j) {
            mvaddch(LINES/2 - logo.size() + x1 + i, COLS/2 - logo[0].size()/2 + x2 + j, logo[i][j]);
        }
        attroff(COLOR_PAIR(BLUE));

        //  Draw e
        attron(COLOR_PAIR(RED));
        for (int j = 33; j < 39; ++j) {
            mvaddch(LINES/2 - logo.size() + x1 + i, COLS/2 - logo[0].size()/2 + x2 + j, logo[i][j]);
        }
        attroff(COLOR_PAIR(RED));

        //  Draw r
        attron(COLOR_PAIR(YELLOW));
        for (int j = 39; j < 45; ++j) {
            mvaddch(LINES/2 - logo.size() + x1 + i, COLS/2 - logo[0].size()/2 + x2 + j, logo[i][j]);
        }
        attroff(COLOR_PAIR(YELLOW));

        //  Draw s
        attron(COLOR_PAIR(GREEN));
        for (int j = 45; j < 50; ++j) {
            mvaddch(LINES/2 - logo.size() + x1 + i, COLS/2 - logo[0].size()/2 + x2 + j, logo[i][j]);
        }
        attroff(COLOR_PAIR(GREEN));
    }
    attron(COLOR_PAIR(YELLOW));
    mvaddch(LINES/2 - logo.size() + x1 + 4, COLS/2 - logo[0].size()/2 + x2 + 12, logo[4][12]);
    attroff(COLOR_PAIR(YELLOW));
        //mvprintw(LINES/2 - logo.size() + x1 + i, COLS/2 - logo[0].size()/2 + x2, logo[i].c_str());
    refresh();
    attroff(A_BOLD);
}


void clear_scr(int x1, int x2) {    //  Clear row x1 to x2
    for (int i = x1; i <= x2; ++i)
        for (int j = 5; j <= COLS - 5; ++j)
            mvaddch(i, j, ' ');
}


void view_document(vector<string> query, string name_document, bool is_intitle) {
    clear_scr(12, LINES - 10);
    attron(A_BOLD);

    attron(COLOR_PAIR(MAGENTA));
    mvprintw(13, (COLS - name_document.size())/2, name_document.c_str());
    attroff(COLOR_PAIR(MAGENTA));
    attron(COLOR_PAIR(CYAN));
    mvprintw(LINES-8 + 1, (COLS - 9)/2 + 1, "  BACK  ");
    attroff(COLOR_PAIR(CYAN));

    attroff(A_BOLD);

    ifstream fin("TextData2/" + name_document);

    vector <string> cur;
    string curl; while (getline(fin, curl, '\n')) cur.push_back(curl);
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
    bool is_end_title = false;
    vector < vector <int> > nxt(content.size());
    for (int i = 0; i < content.size(); ++i) {
        nxt[i].assign(content[i].size(), 0);
        for (int k = 0; k < content[i].size(); ++k) {
            if (std::string("?!.\n").find(content[i][k]) != std::string::npos) is_end_title = true;

            for (auto it : query) if (String::to_lower(content[i].substr(k, it.size())) == it) {
                nxt[i][k] = max(nxt[i][k], int(it.size() + k));
                if (is_end_title && is_intitle) nxt[i][k] = 0;
                if ((k > 0 && std::string(".,!?").find(content[i][k - 1]) == std::string::npos)) nxt[i][k] = 0;
                if (k + it.size() < content[i].size() && std::string("!.,? ").find(content[i][k + it.size()]) == std::string::npos) nxt[i][k] = 0;
            }
        }
    }

    // Update content when client press KEY_UP or KEY_DOWN
    auto update = [&](int l, int r) {
        r = min(r, (int) content.size());
        
        clear_scr(16, LINES - 10);
        for (int i = l; i < r; ++i) {
            if (content[i].empty()) continue;
            int pos = 54;
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
            if (x > 0) x--;
        }
        if (input == KEY_DOWN) {
            if (x + 23 < content.size()) x++;
        }
        if (input == '\n')
            break; 
        update(x, x + 23);
    }

    clear_scr(12, LINES - 10);
}

enum {
    DOCUMENT1,
    DOCUMENT2,
    DOCUMENT3,
    DOCUMENT4,
    DOCUMENT5,
    BACK
};


void mouse_search_scr(int &current_pointer, int x, int y, vector<string> result) {
    if (x == LINES-8 + 1 && y >= (COLS - 9)/2 + 1 && y <= (COLS - 9)/2 + 8)
        current_pointer = BACK;
    else {
        for (int i = DOCUMENT1; i <= DOCUMENT5; ++i) 
            if (!result[i].empty())
                if (x == 13 + 5*i && y >= 70 && y <= 70 + result[i].size()-1) {
                    current_pointer = i;
                    break;
                }
    }
}


void Frontend::search_scr(Trie &trie, string input_search, Trie& trie_title) {
    //Add queries to history
    system(("echo " + input_search + " >> Data/history.data").c_str());
    
    clear_scr(3, LINES - 3); 
    MEVENT mouse;
    mousemask(ALL_MOUSE_EVENTS, NULL);

    draw_logo(- LINES/2 + 8 + 3, - COLS/2 + 51/2 + 15); //  8 == logo.size() and 51 == logo[0].size()
    draw_rectangle(6, 76, 2, 75);    //  Draw SEARCH_BAR besides the logo
    mvprintw(7, 76+1, input_search.c_str());

    Clock = clock();
    vector<string> query =  String::split(input_search);

    bool is_intitle = false;
    Operator OPERATOR(type);
    vector<string> result;
    for (auto i : OPERATOR._Processing(trie, query, 5, trie_title, is_intitle))
        result.push_back(name[i]);
    result.push_back("  BACK  ");
    Clock = clock() - Clock;

    //  Print the Searching time
    attron(A_BOLD | COLOR_PAIR(YELLOW));
    mvprintw(9, 77, "Searching time: %.3f ms", (double)Clock*1000/CLOCKS_PER_SEC);
    attroff(A_BOLD | COLOR_PAIR(YELLOW));


    for (string & term : query) {
        if (term[0] == '"' && term.back() == '"' && term.size() >= 2) {
            term = term.substr(1, (int)term.size() - 2);
        }
    }

    int current_pointer = -1, size = (int)result.size();
    while (true) {
        draw_rectangle(LINES - 8, (COLS - 9)/2, 2, 9) ;   //  Draw BACK 
        //  Print result and BACK content
        for (int i = 0; i < size; ++i) {
            attron(A_BOLD);
            if (i == size - 1) {
                attron(COLOR_PAIR(CYAN));
                mvprintw(LINES-8 + 1, (COLS - 9)/2 + 1, result[i].c_str());
                attroff(COLOR_PAIR(CYAN));
            }
            else {
                attron(A_UNDERLINE | COLOR_PAIR(MAGENTA));
                mvprintw(13 + 5*i, 70, result[i].c_str());
                attroff(A_UNDERLINE | COLOR_PAIR(MAGENTA));
            }
            attroff(A_BOLD); 
        }
        if (size == 1) { //  No matching result
            attron(A_BLINK | A_BOLD | COLOR_PAIR(RED));
            mvprintw(LINES/2, (COLS - 21)/2, "NO MATCHING RESULT!!!");
            attroff(A_BLINK | A_BOLD | COLOR_PAIR(RED));
        }

          // Show some thing
        Aho_Corasick Aho(256);
        for (auto x : query) {
     //       system(("echo " + x + " >> log.txt").c_str());
            Aho.Insert(x);
        }
        for (int i = 0; i < size - 1; ++i) {
            int numchar = 210;
            ifstream data("TextData2/" + result[i]);
            string st, temp;
            while (data >> temp) {
                for (char c : temp) if (0 <= c && c < 256) {
                    if ('A' <= c && c <= 'Z') c += 32;
                    st.push_back(c);
                }
                st.push_back(' ');
            }
            vector<int> appear(st.size(), 0);
            int r = Aho.ValueTrace(st, appear, numchar) + 1;
            int l = max(0, r - numchar);
            int cnt = is_intitle ? 1 : 1e5;
            for (int _ = l; _ < r; _ += 70) {
                bool can_high_light = cnt > 0;
                for (int j = _; j < min(_ + 70, r); ++j) {
                    string c; c.push_back(st[j]);
                    if (appear[j] && can_high_light) { attron(A_BOLD); attron(A_REVERSE); }
                    mvprintw(14 + (_ - l) / 70 + 5 * i, 75 + (j - _), c.c_str());
                    if (appear[j] && can_high_light) { attroff(A_BOLD); attroff(A_REVERSE); }
                }
                cnt--;
            }
        }


        int input = getch();
        bool exit_while = false;
        switch (input) {
            case KEY_MOUSE: {
                if (getmouse(&mouse) == OK) {
                    if (mouse.bstate & BUTTON1_CLICKED) {
                        mouse_search_scr(current_pointer, mouse.y, mouse.x, result);
                        switch (current_pointer) {
                            case DOCUMENT1:
                                if (size > 1)
                                    view_document(query, result[0], is_intitle);
                                break;
                            case DOCUMENT2:
                                if (size > 2)
                                    view_document(query, result[1], is_intitle);
                                break;
                            case DOCUMENT3:
                                if (size > 3)
                                    view_document(query, result[2], is_intitle);
                                break;
                            case DOCUMENT4:
                                if (size > 4)
                                    view_document(query, result[3], is_intitle);
                                break;
                            case DOCUMENT5:
                                if (size > 5)
                                    view_document(query, result[4], is_intitle);
                                break;
                            case BACK:
                                exit_while = true;
                                break;
                        }

                        current_pointer = -1;   //  Reset current pointer
                    }
                }
                break;
            }
            case '\n':
                exit_while = true;
                break;
        }

       
        if (exit_while) //  If user choose BACK
            break;

        refresh();
    }
    clear_scr(3, LINES - 3);
}


enum {
    SEARCH_BAR,
    SEARCH_BUTTON,
    HISTORY,
    QUIT
}; 

void mouse_main_scr(int &current_pointer, int x, int y) {
    if (x == LINES/2 + 5 + 4) {
        if (y >= COLS/2 - 20 && y <= COLS/2 - 8)
            current_pointer = HISTORY;
        else if (y >= COLS/2 + 8 && y <= COLS/2 + 19)
            current_pointer = QUIT;
    }
    else if (x == LINES/2) {
        if (y >= (COLS - 75)/2 + 1 && y <= (COLS - 75)/2 + 74)
            current_pointer = SEARCH_BAR;
        else if (y >= (COLS + 75 + 5)/2 + 1 && y <= (COLS + 75 + 5)/2 + 12)
            current_pointer = SEARCH_BUTTON;
    }
}


void get_query(string &input_search, int &current_pointer, int x, int y, int width, Trie& trie) {
    move(x, y);   //  Set the cursor to be in the Search rectangle
    curs_set(1);    //  Set cursor visible
    keypad(stdscr, true);

    string word, pre_word;
    std::vector < std::string > suggests;
    
    MEVENT mouse;
    mousemask(ALL_MOUSE_EVENTS, NULL);
    int a = x, b = y, ptr = 0, lim = 6;
    bool can_suggest = false;

    auto updateSuggest = [&] (int ptr) {
        // clear auto suggest screen
        for (int i = LINES / 2 + 2; i <= LINES / 2 + 2 + 4; ++i)
            for (int j = (COLS - 75) / 2 + 1; j < (COLS - 75) / 2 + 75; ++j)
                mvaddch(i, j, ' ');

        curs_set(0);
        for (int i = 1; i <= suggests.size(); ++i) {
            string temp = input_search.substr(0, input_search.size() - word.size()) + suggests[i - 1];
            if (i == ptr) attron(A_REVERSE);
            for (int j = (COLS - 75) / 2 + 1; j < (COLS - 75) / 2 + 75; ++j) mvaddch(LINES / 2 + i + 1, j, ' ');
            mvprintw(LINES / 2 + i + 1, y, temp.c_str());
            if (i == ptr) attroff(A_REVERSE);
        }
        refresh();
        move(a, b);
        curs_set(1);
    };
    
    while (true) {
        //Display auto suggestion 
        if (!word.empty() && word != pre_word) {
            system(("echo " + pre_word + " " + word + " >> log").c_str());
            suggests = trie.auto_suggestion(word, lim - 1);
            if (suggests[0].compare("null") != 0) {
                ptr = 0;
                lim = suggests.size() + 1;
                can_suggest = true;
                
                curs_set(0);
                draw_rectangle(LINES/2 + 1, (COLS - 75)/2, 6, 75, false);
                updateSuggest(ptr);

            } else can_suggest = false;
            curs_set(1);
            pre_word = word;
        }

        int temp = getch();
        if (temp == '\n') {
            if (ptr != 0) {
                input_search = input_search.substr(0, input_search.size() - word.size()) + suggests[ptr - 1];
            }
            current_pointer = SEARCH_BUTTON;
            break;
        }
        if (temp == KEY_MOUSE) {
            if (getmouse(&mouse) == OK) {
                if (mouse.bstate & BUTTON1_CLICKED) {
                    mouse_main_scr(current_pointer, mouse.y, mouse.x);
                    if (current_pointer != SEARCH_BAR)
                        break;
                    else
                        continue;
                }
            }
        }
        if (temp == KEY_UP) {
            ptr = (ptr - 1 + lim) % lim;
            if (can_suggest) updateSuggest(ptr);
        } else if (temp == KEY_DOWN) {
            ptr = (ptr + 1) % lim;
            if (can_suggest) updateSuggest(ptr);
        }
        if ((temp == 127 || temp == 263) && b > y) {   //  If user press BACKSPACE
            // clear auto suggest screen
            for (int i = LINES / 2 + 2; i <= LINES / 2 + 2 + 4; ++i)
                for (int j = (COLS - 75) / 2 + 1; j < (COLS - 75) / 2 + 75; ++j)
                    mvaddch(i, j, ' ');
            
            mvaddch(a, --b, ' ');
            if (!input_search.empty()) input_search.pop_back();
            if (!word.empty()) word.pop_back();
            else {
                int x = input_search.find_last_of(' ');
                if (x != string::npos) word = input_search.substr(x + 1);
                else if (input_search.size()) {
                    word = input_search;
                    if (!word.empty() && word[0] != '#') word.erase(word.begin());
                }
            }
            move(a, b);
        } else if ((temp >= 32 && temp <= 126) && b < y + 75) {    //  User have to input a query with length < 75
            ptr = 0;
            input_search.push_back((char)temp);
            if (temp == ' ') {
                word.clear();
            } else if (temp != '#' && temp != '\"') {
                word += char(temp);
            }
            mvaddch(a, b++, temp);
        }
    }
    curs_set(0);
}

void reset() {
    for (int i = 0; i < 74; ++i)
        mvaddch(LINES/2, (COLS - 75)/2 + i+1, ' ');
    refresh();
}

void Frontend::main_scr(Trie &trie, Trie& trie_title) {
    MEVENT mouse;
    mousemask(ALL_MOUSE_EVENTS, NULL);

    attron(A_BOLD | COLOR_PAIR(YELLOW));
    mvprintw(LINES/2 + 2, (COLS - 75)/2 + 1, "Loading time: %.3f ms", (double)Clock*1000/CLOCKS_PER_SEC);
    attroff(A_BOLD | COLOR_PAIR(YELLOW));
    vector<string> content{
        "",
        "   SEARCH   ",
        "   HISTORY   ",
        "    QUIT    "
    };
    int current_pointer = SEARCH_BAR;
    while (true) {
        draw_logo(-4, 0);
        draw_rectangle(LINES/2 - 1, (COLS - 75)/2, 2, 75);  //  Draw SEARCH_BAR
        draw_rectangle(LINES/2 - 1, (COLS + 75 + 5)/2, 2, 13);  //  Draw SEARCH_BUTTON
        draw_rectangle(LINES/2 + 4 + 4, COLS/2 - 21, 2, 14);    //  Draw HISTORY
        draw_rectangle(LINES/2 + 4 + 4, COLS/2 + 7, 2, 13);    //  Draw QUIT

        //  Print content for rectangles
        attron(A_BOLD | COLOR_PAIR(CYAN)); //Colors::pairActivate(stdscr, YELLOW);
        mvprintw(LINES/2, (COLS + 75 + 5)/2 + 1, content[SEARCH_BUTTON].c_str());
        mvprintw(LINES/2 + 5 + 4, COLS/2 - 20, content[HISTORY].c_str());
        mvprintw(LINES/2 + 5 + 4, COLS/2 + 8, content[QUIT].c_str());
        attroff(A_BOLD | COLOR_PAIR(CYAN)); //Colors::pairDeactivate(stdscr, YELLOW);
        refresh();


        bool exit_while = false;
        string input_search; 
        Loop:switch (current_pointer) {
            case SEARCH_BAR: {
                get_query(input_search, current_pointer, LINES/2, (COLS-75)/2 + 1, 74, trie);
            }
            goto Loop;
            case SEARCH_BUTTON: {
                search_scr(trie, input_search, trie_title);
                current_pointer = SEARCH_BAR;
                input_search.clear();
                break;
            }
            case HISTORY: {
                reset();
                current_pointer = SEARCH_BAR;
                input_search.clear();
                break;
            }
            case QUIT: {
                exit_while = true;
                break;
            }
        }

        if (exit_while) //  If user choose QUIT
            break;

        refresh();
    }
    endwin();
}


void Frontend::loading_scr() {
    //Clear old history data
    system("rm -f Data/history.data");

    //  Initializing for ncurses
    initscr();
    noecho();
    cbreak();
    keypad(stdscr, TRUE);
    curs_set(0);    //  Set cursor invisible

    //  Initialize color
    start_color();
    init_pair(BLACK, COLOR_BLACK, COLOR_BLACK);
    init_pair(RED, COLOR_RED, COLOR_BLACK);
    init_pair(GREEN, COLOR_GREEN, COLOR_BLACK);
    init_pair(YELLOW, COLOR_YELLOW, COLOR_BLACK);
    init_pair(BLUE, COLOR_BLUE, COLOR_BLACK);
    init_pair(MAGENTA, COLOR_MAGENTA, COLOR_BLACK);
    init_pair(CYAN, COLOR_CYAN, COLOR_BLACK);
    init_pair(WHITE, COLOR_WHITE, COLOR_BLACK);
    
    draw_rectangle(0, 0, LINES - 1, COLS - 1);  //  Draw main window
    draw_logo(-4, 0);
    attron(A_BLINK | A_BOLD | COLOR_PAIR(MAGENTA));
    mvprintw(LINES/2, (COLS - 7)/2, "LOADING");
    attroff(A_BLINK | A_BOLD | COLOR_PAIR(MAGENTA));
    refresh();

    Clock = clock();
    Trie trie(256);
    Trie trie_title(256);
    trie_title.Intitle();
    trie.Import();
    if (trie.Loading()) trie.Export();
    Clock = clock() - Clock;
    clear_scr(LINES/2, LINES - 3);  //  7 is the logo.size()
    refresh();
    main_scr(trie, trie_title);
}