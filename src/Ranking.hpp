#ifndef __RANKING__
#define __RANKING__

#include <bits/stdc++.h>
#include <Heap.hpp>
#include <Trie.hpp>
//#include <>

using namespace std;

struct Ranking{
    int nText;
    vector<int> output(Trie &trie, vector<string> query, int k);
    double weight_query(Trie &trie, string term, int count);
};

#endif //__RANKING__