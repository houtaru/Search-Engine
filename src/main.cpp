#include <Trie.hpp>
#include "Ranking.hpp"
#include "utils.h"
#include <iostream>
#include <fstream>
#include <Heap.hpp>

using namespace std;

int main() {
    //ios::sync_with_stdio(false);cin.tie(NULL);
    double stime = clock();
    Trie trie(256);
    //trie.Import();
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
        //cerr << "Done file " << cnt << ' ' << text.size() << '\n'; 
        ++cnt;
    }
    cerr << "Adding all texts takes " << (clock() - stime) / CLOCKS_PER_SEC * 1000 << "ms.\n";
    stime = clock();
    trie.Export();
    cerr << "Exporting TRIE takes " << (clock() - stime) / CLOCKS_PER_SEC * 1000 << "ms.\n";
    stime = clock();
    // cerr << "totalChar : " << totalChar << '\n';
    // for (auto x : trie.Search("VIETNAM")) {
    //     cerr << x.first << ' ' << x.second << '\n';
    // }
    //exit(0);
    // trie.Try(trie.root, "");
    exit(0);
    string query;
    getline(cin, query);
    //trie.Export();
    stime = clock();
    Ranking ranking;
    vector<int> Result = ranking.output(trie, tokenizer(query), 10);
    for (int x : Result) {
        cout << x << "\n";
    }
    cerr << "\nSearching TRIE takes " << (clock() - stime) / CLOCKS_PER_SEC * 1000 << "ms.\n";

    // // Trie trie(256);
    // // trie.Import();

    // // vector<string> nameFile;
    // // string sub;
    // // ifstream fin("TextData2/___index.txt");
    // // while (getline(fin, sub)) {
    // //     nameFile.push_back(sub);
    // // }
    // // fin.close();

    // // string query;
    // // getline(cin, query);

    // // Ranking ranking;
    // // vector<int> Result = ranking.output(trie, tokenizer(query), 5);
    // // cout << endl;
    // // for (int i : Result)
    // //     cout << nameFile[i] << endl;
    
    // return 0;
    // Aho_Corasick Aho(256);
    // Aho.Insert("you");
    // Aho.Insert("Love you");
    // Aho.Insert("you died");
    // Aho.BuildSumSuffix(nullptr);
    // cout << Aho.Value("Love you died");
    return 0;
}