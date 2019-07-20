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
    echo();
    getstr(input_search);
    noecho();
}


void reset() {
    for (int i = 0; i < 74; ++i)
        mvaddch(LINES/2, (COLS - 75)/2 + i+1, ' ');
    refresh();
}


void clear_scr(int x1, int x2) {
    for (int i = x1; i <= x2; ++i)
        for (int j = 5; j <= 195; ++j)
            mvaddch(i, j, ' ');
}


void view_document(string name_document) {
    clear_scr(12, LINES - 10);
    attron(A_BOLD);

    attron(A_UNDERLINE); 
    mvprintw(13, 70, name_document.c_str());
    attroff(A_UNDERLINE);

    attron(A_REVERSE);
    mvprintw(LINES-8 + 1, (COLS - 9)/2 + 1, "  BACK  ");
    attroff(A_REVERSE);

    attroff(A_BOLD);

    while (true) {
        int input = getch();
        if (input == '\n')
            break;
    }

    clear_scr(12, LINES - 10);
}


void Frontend::search_scr(Trie &trie, char *input_search) {
    clear_scr(3, 47); 
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


    int current_pointer = 0, size = (int)result.size();
    while (true) {
        draw_rectangle(LINES - 8, (COLS - 9)/2, 2, 9) ;   //  Draw BACK 
        //  Print result and BACK content
        for (int i = 0; i < size; ++i) {
            if (i == current_pointer)
                attron(A_REVERSE);

            attron(A_BOLD);
            if (i == size - 1)
                mvprintw(LINES-8 + 1, (COLS - 9)/2 + 1, result[i].c_str());
            else {
                attron(A_UNDERLINE);
                mvprintw(13 + 5*i, 70, result[i].c_str());
                attroff(A_UNDERLINE);
            }
            attroff(A_BOLD); 

            if (i == current_pointer)
                attroff(A_REVERSE);
        }


        int input = getch();
        bool exit_while = false;
        switch (input) {
            case KEY_DOWN:
                current_pointer = (current_pointer + 1) % size;
                break;
            case KEY_UP:
                current_pointer = (current_pointer + size - 1) % size;
                break;
            case '\n': {
                if (current_pointer == size - 1) {   //  If user choose BACK
                    exit_while = true;
                    break;
                }

                switch (current_pointer) {
                    case 0:
                        view_document(result[0]);
                        break;
                    case 1:
                        view_document(result[1]);
                        break;
                    case 2:
                        view_document(result[2]);
                        break;
                    case 3:
                        view_document(result[3]);
                        break;
                    case 4:
                        view_document(result[4]);
                        break;
                }
            }
        }

        if (exit_while) //  If user choose BACK
            break;

        refresh();
    }
    clear_scr(3, 47);
}


void Frontend::main_scr() {
    Trie trie(256);
    trie.Import();

    initscr();
    noecho();
    cbreak();
    keypad(stdscr, TRUE);

    enum {
    SEARCH_BAR,
    SEARCH_BUTTON,
    RESET,
    QUIT
    };  
    vector<string> content{
        "",
        "   SEARCH   ",
        "   RESET    ",
        "    QUIT    "
    };
    int current_pointer = 0, size = 4;   //  size is the number of rectangles
    while (true) {
        draw_rectangle(0, 0, LINES - 1, COLS - 1);  //  Draw main window
        draw_logo(-2, 0);
        draw_rectangle(LINES/2 - 1, (COLS - 75)/2, 2, 75);  //  Draw SEARCH_BAR
        draw_rectangle(LINES/2 - 1, (COLS + 75 + 5)/2, 2, 13);  //  Draw SEARCH_BUTTON
        draw_rectangle(LINES/2 + 4, COLS/2 - 20, 2, 13);    //  Draw RESET
        draw_rectangle(LINES/2 + 4, COLS/2 + 7, 2, 13);    //  Draw QUIT

        //  Print content for rectangles
        curs_set(0);    //  Set cursor invisible
        attron(A_BOLD);
        if (current_pointer == SEARCH_BUTTON)
            attron(A_REVERSE);
        mvprintw(LINES/2, (COLS + 75 + 5)/2 + 1, content[SEARCH_BUTTON].c_str());
        if (current_pointer == SEARCH_BUTTON)
            attroff(A_REVERSE);

        if (current_pointer == RESET)
            attron(A_REVERSE);
        mvprintw(LINES/2 + 5, COLS/2 - 19, content[RESET].c_str());
        if (current_pointer == RESET)
            attroff(A_REVERSE);

        if (current_pointer == QUIT)
            attron(A_REVERSE);
        mvprintw(LINES/2 + 5, COLS/2 + 8, content[QUIT].c_str());
        if (current_pointer == QUIT)
            attroff(A_REVERSE);
        attroff(A_BOLD);

        if (current_pointer == SEARCH_BAR) {
            curs_set(1);    //  Set cursor visible
            move(LINES/2, (COLS - 75)/2 + 1);   //  Set the cursor to be in the Search rectangle
        }


        int input = getch();
        bool exit_while = false;
        switch (input) {
            case KEY_DOWN:
                current_pointer = (current_pointer + 1) % size;
                break;
            case KEY_UP:
                current_pointer = (current_pointer + size - 1) % size;
                break;
            case '\n': {
                if (current_pointer == QUIT) {   //  If user choose QUIT
                    exit_while = true;
                    break;
                }

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
                        break;
                }
            }
        }

        if (exit_while) //  If user choose QUIT
            break;

        refresh();
    }
    endwin();
}

