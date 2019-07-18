#ifndef __RANKING__
#define __RANKING__

#include <bits/stdc++.h>
#include <Heap.hpp>
#include <Trie.hpp>
//#include <>

using namespace std;

struct Ranking{
    vector<int> output(Trie &trie, vector<string> query, int k);
    double weight_query(Trie &trie, string term, int count, int lenght_vector);
};

#endif //__RANKING__