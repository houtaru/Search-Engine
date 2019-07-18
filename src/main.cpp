#include <Trie.hpp>
#include "Ranking.hpp"
#include "utils.h"
#include <iostream>
#include <fstream>
#include <Heap.hpp>

using namespace std;

int main() {
    Trie trie(256);
    trie.Import();
    for (int i = 0; i < 3; ++i) {
        string filename = "TextData/";
        filename.push_back(char('0' + i));
        ifstream fin(filename + ".txt");
        //cerr << filename + ".txt" << endl;
        string st;
        string text;
        while (getline(fin, st)) {
            for (char c : st) text.push_back(c);
            text.push_back(' '); 
        }
        trie.AddText(i, text);
    }
    trie.Export();
    cout << "Count " << trie.Search("love", 0) << endl;
    exit(0);
    string query;
    getline(cin, query);
    //trie.Export();
    Ranking ranking;
    vector<int> Result = ranking.output(trie, tokenizer(query), 3);
    for (int x : Result) {
        cout << x << ' ';
    }
}