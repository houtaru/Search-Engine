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
    Ranking ranking ;
    //  AND, $, #, " " Operator 
    vector<int> _And(Trie &trie, vector<string> &query, int k, set<int> &minus, set<int> &plus);

    //  OR Operator
    vector<int> _Or(Trie &trie, vector<string> &query1, vector<string> &query2, int k );

    //  Synonym Operator
    vector<int> _Synonym(Trie &trie, vector<string> &query, int index, int k, set<int> &minus, set<int> &plus); 

    //  Minus or Plus case 
    set<int> _Minus_Plus(Trie &trie, string s, int k);

    //  Query processing
    vector<int> _Processing(Trie &trie, vector<string> &query, int k);
};


#endif
