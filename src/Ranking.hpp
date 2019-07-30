#ifndef __RANKING__
#define __RANKING__

#include <bits/stdc++.h>
#include <Heap.hpp>
#include <Trie.hpp>
#include <utils.h>
#include <Engine/Utils/String.hpp>

using namespace std;


vector<int> FullyAppearance(Trie &trie, vector<string> query);
struct Ranking{
    int nText;
    vector<di> output(Trie &trie, vector<string> query, int k, set<int> &minus, set<int> &plus);
    double weight_query(Trie &trie, string term, int count);
};

#endif //__RANKING__