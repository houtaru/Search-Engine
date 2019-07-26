#ifndef __RANKING__
#define __RANKING__

#include <bits/stdc++.h>
#include <Heap.hpp>
#include <Trie.hpp>
#include <Engine/Utils/String.hpp>

using namespace std;

struct Ranking{
    int nText;
    vector<int> output(Trie &trie, vector<string> query, int k);
    double weight_query(Trie &trie, string term, int count);
    vector<int> FullyAppearance(Trie & trie, vector<string> query);
    string AllText(int id);
};

#endif //__RANKING__