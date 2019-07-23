#include <Frontend.hpp>

void Frontend::draw_rectangle(int x1, int y1, int height, int width) {
    attron(A_BOLD);
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
    attroff(A_BOLD);
}


void Frontend::draw_logo(int x1, int x2) {  //  x1, x2 is the coordinate according to the center of the screen
    attron(A_BOLD);
    vector<string> logo = {
        "   ___                                             ",
        "  /   |                                            ",
        " / /| | _ __   __ _  _ __    __ _   ___  _ __  ___ ",
        "/ /_| || '__| / _` || '_ \\  / _` | / _ \\| '__|/ __|",
        "\\___  || |   | (_| || | | || (_| ||  __/| |   \\__ \\",
        "    |_/|_|    \\__,_||_| |_| \\__, | \\___||_|   |___/",
        "                             __| |                 ",
        "                            |____/                 "
    };
    for (int i = 0; i < (int)logo.size(); ++i)
        mvprintw(LINES/2 - logo.size() + x1 + i, COLS/2 - logo[0].size()/2 + x2, logo[i].c_str());
    refresh();
    attroff(A_BOLD);
}


void get_query(char *input_search) {
    move(LINES/2, (COLS - 75)/2 + 1);   //  Set the cursor to be in the Search rectangle
    curs_set(1);    //  Set cursor visible
    echo();
    getstr(input_search);
    noecho();
    curs_set(0);
}


void reset() {
    for (int i = 0; i < 74; ++i)
        mvaddch(LINES/2, (COLS - 75)/2 + i+1, ' ');
    refresh();
}


void clear_scr(int x1, int x2) {
    for (int i = x1; i <= x2; ++i)
        for (int j = 5; j <= COLS - 5; ++j)
            mvaddch(i, j, ' ');
}


void view_document(vector<string> query, string name_document) {
    clear_scr(12, LINES - 10);
    attron(A_BOLD);

    mvprintw(13, (COLS - name_document.size())/2, name_document.c_str());
    mvprintw(LINES-8 + 1, (COLS - 9)/2 + 1, "  BACK  ");

    attroff(A_BOLD);

    ifstream fin("TextData2/" + name_document);
    vector<string> content;
    string sub;
    while (fin >> sub)
        content.push_back(sub);
    fin.close();

    //  row: current row
    //  length_row: the current length on the current row
    //  index: current index in content
    //  position: next position to print content[i]
    int row = 1, length_row = 0, position = 54, index = 0;
    while (index < content.size() && row < 23) {
        length_row = position + content[index].size()+1 - 49;

        if (length_row > 100) {
            ++row;
            if (row >= 23) 
                break;
            length_row = 0;
            position = 49;
        }

        bool compare = false;
        //  Compare content[index] to query. If it is, bolding it
        for (auto i : tokenizer(content[index]))
            for (auto j : query)
                if (i.compare(j) == 0) {
                    compare = true;
                    attron(A_BOLD); attron(A_REVERSE);
                    break;
                }
        mvprintw(15 + row, position, content[index].c_str());
        position += content[index].size() + 1;
        ++index;
        if (compare) {
            attroff(A_BOLD); attroff(A_REVERSE);
        }
    }

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
            if (x == 13 + 5*i && y >= 70 && y <= 70 + result[i].size()-1) {
                current_pointer = i;
                break;
            }
    }

}


void Frontend::search_scr(Trie &trie, char *input_search) {
    clear_scr(3, LINES - 3); 
    MEVENT mouse;
    mousemask(ALL_MOUSE_EVENTS, NULL);

    draw_logo(- LINES/2 + 8 + 3, - COLS/2 + 51/2 + 15); //  8 == logo.size() and 51 == logo[0].size()
    draw_rectangle(6, 76, 2, 75);    //  Draw SEARCH_BAR besides the logo
    for (int i = 0; i < strlen(input_search); ++i)
        mvaddch(7, 76+1 + i, input_search[i]);

    vector<string> query = tokenizer(input_search);

    //  Get name of documents
    vector<string> name;
    ifstream fin("TextData2/___index.txt");
    string sub;
    while (getline(fin, sub))
        name.push_back(sub);
    fin.close();


    Ranking ranking;
    vector<string> result;
    for (auto i : ranking.output(trie, query, 5))
        result.push_back(name[i]);
    result.push_back("  BACK  ");


    int current_pointer = -1, size = (int)result.size();
    while (true) {
        draw_rectangle(LINES - 8, (COLS - 9)/2, 2, 9) ;   //  Draw BACK 
        //  Print result and BACK content
        for (int i = 0; i < size; ++i) {
            attron(A_BOLD);
            if (i == size - 1)
                mvprintw(LINES-8 + 1, (COLS - 9)/2 + 1, result[i].c_str());
            else {
                attron(A_UNDERLINE);
                mvprintw(13 + 5*i, 70, result[i].c_str());
                attroff(A_UNDERLINE);
            }
            attroff(A_BOLD); 
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
                                view_document(query, result[0]);
                                break;
                            case DOCUMENT2:
                                view_document(query, result[1]);
                                break;
                            case DOCUMENT3:
                                view_document(query, result[2]);
                                break;
                            case DOCUMENT4:
                                view_document(query, result[3]);
                                break;
                            case DOCUMENT5:
                                view_document(query, result[4]);
                                break;
                            case BACK:
                                exit_while = true;
                                break;
                        }

                        current_pointer = -1;   //  Reset current pointer
                    }
                }
            }
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
    RESET,
    QUIT
}; 

void mouse_main_scr(int &current_pointer, int x, int y) {
    if (x == LINES/2 + 5) {
        if (y >= COLS/2 - 19 && y <= COLS/2 - 8)
            current_pointer = RESET;
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


void Frontend::main_scr(Trie &trie) {
    MEVENT mouse;
    mousemask(ALL_MOUSE_EVENTS, NULL);

    vector<string> content{
        "",
        "   SEARCH   ",
        "   RESET    ",
        "    QUIT    "
    };
    int current_pointer = -1, size = 4;   //  size is the number of rectangles
    while (true) {
        draw_logo(-2, 0);
        draw_rectangle(LINES/2 - 1, (COLS - 75)/2, 2, 75);  //  Draw SEARCH_BAR
        draw_rectangle(LINES/2 - 1, (COLS + 75 + 5)/2, 2, 13);  //  Draw SEARCH_BUTTON
        draw_rectangle(LINES/2 + 4, COLS/2 - 20, 2, 13);    //  Draw RESET
        draw_rectangle(LINES/2 + 4, COLS/2 + 7, 2, 13);    //  Draw QUIT

        //  Print content for rectangles
        attron(A_BOLD);
        mvprintw(LINES/2, (COLS + 75 + 5)/2 + 1, content[SEARCH_BUTTON].c_str());
        mvprintw(LINES/2 + 5, COLS/2 - 19, content[RESET].c_str());
        mvprintw(LINES/2 + 5, COLS/2 + 8, content[QUIT].c_str());
        attroff(A_BOLD);
        refresh();


        int input = getch();
        bool exit_while = false;
        switch (input) {
            case KEY_MOUSE: {
                if (getmouse(&mouse) == OK)
                    if (mouse.bstate & BUTTON1_CLICKED) {
                        mouse_main_scr(current_pointer, mouse.y, mouse.x);

                        char input_search[100];
                        switch (current_pointer) {
                            case SEARCH_BAR:
                                get_query(input_search);
                                break;
                            case SEARCH_BUTTON:
                                search_scr(trie, input_search);
                                input_search[0] = '\0';
                                break;
                            case RESET:
                                reset();
                                input_search[0] = '\0';
                                break;
                            case QUIT:
                                exit_while = true;
                                break;
                        }
                    }
            }
        }

        if (exit_while) //  If user choose QUIT
            break;

        refresh();
    }
    endwin();
}


void Frontend::loading_scr() {
    //  Initializing for ncurses
    initscr();
    noecho();
    cbreak();
    keypad(stdscr, TRUE);
    curs_set(0);    //  Set cursor invisible

    
    draw_rectangle(0, 0, LINES - 1, COLS - 1);  //  Draw main window
    draw_logo(-2, 0);
    attron(A_BLINK); attron(A_BOLD);
    mvprintw(LINES/2, (COLS - 7)/2, "LOADING");
    attroff(A_BLINK); attroff(A_BOLD);
    refresh();

    Trie trie(256);
    trie.Import();

    clear_scr(3, LINES - 3);
    refresh();
    main_scr(trie);
}
