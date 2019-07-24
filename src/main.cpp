#include <ncurses.h>
#include <bits/stdc++.h>

#include <Engine/Utils/String.hpp>

using namespace std;

// void view_document(vector <string> query, string file) {
//     //clear screeb
//     //clear_scr()
    
//     //TITLE

//     ifstream fin("input.in");
//     vector <string> content;
//     string ss;
//     while (getline(fin, ss))
//       content.push_back(ss);
// }

int main() {
    // initscr();
    // noecho();
    // cbreak();
    // keypad(stdscr, TRUE);
    // curs_set(0);    //  Set cursor invisible

    // vector <string> query = {
    //   "nam", "ngoi", "khoc"
    // };
    // view_document(query, "input.in");

    string s; getline(cin, s, '\n');
    vector <string> cur = String::split(String::to_lower(s));
    for (auto it : cur) cout << it << "\n";
    return 0;
}