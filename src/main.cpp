#include <Trie.hpp>
#include "Ranking.hpp"
#include "utils.h"
#include <iostream>
#include <fstream>
#include <Heap.hpp>

using namespace std;

int main() {
    double stime = clock();
    Trie trie(256);
    trie.Import();
    cerr << "Importing TRIE takes " << (clock() - stime) / CLOCKS_PER_SEC * 1000 << "ms.\n";
    stime = clock();
    ifstream fin("TextData/___index.txt");
    string filename;
    int cnt = 0;
    int totalChar = 0;
    while (getline(fin, filename)) {
        if (trie.HasText(cnt)) {
       //     std::cerr << "Have added " << cnt << "already\n";
            ++cnt;
            continue;
        }
        ifstream data("TextData/" + filename);
        string st;
        string text;
        while (getline(data, st)) {
            for (char c : st) {
                if ('A' <= c && c <= 'Z') c += 32;
                if (('a' <= c && c <= 'z') || ('0' <= c && c <= '9') || c == ' ')
                    text.push_back(c);
            }
            text.push_back(' '); 
        }
        trie.AddText(cnt, text);
        totalChar += text.size();
        // cerr << "Done file " << cnt << ' ' << text.size() << '\n'; 
        ++cnt;
    }
    cerr << "Adding all texts takes " << (clock() - stime) / CLOCKS_PER_SEC * 1000 << "ms.\n";
    stime = clock();
    trie.Export();
    cerr << "Exporting TRIE takes " << (clock() - stime) / CLOCKS_PER_SEC * 1000 << "ms.\n";
    stime = clock();
    // cerr << "totalChar : " << totalChar << '\n';
}