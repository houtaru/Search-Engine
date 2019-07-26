#ifndef __OPERATOR__
#define __OPERATOR__

#include <bits/stdc++.h>
#include <Heap.hpp>
#include <Trie.hpp>
#include <Ranking.hpp>
#include <algorithm> 
#include <fstream> 
#include <Engine/Utils/String.hpp>
using namespace std;
struct Operator
{   
    // Trie stores 

    Ranking ranking;

    Trie trie;
    Trie trie_title;

    Operator::Operator(Trie _trie, Trie _trie_title) {
        trie = _trie;
        trie_title = _trie_title;
    }
    
    //  AND, $, #, " " Operator 
    vector<int> _And(Trie& trie, vector<string> &query, int k, set<int> &minus, set<int> &plus);

    //  OR Operator
    vector<int> _Or(vector<string> &query1, vector<string> &query2, int k );

    //  Synonym Operator
    vector<int> _Synonym(Trie &trie, vector<string> &query, int index, int k, set<int> &minus, set<int> &plus); 

    //  Minus or Plus case 
    set<int> _Minus_Plus(Trie &trie, string s, int k);

    //  Query processing
    vector<int> _Processing(vector<string> &query, int k, bool is_intitle = false);
};


#endif
