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
struct Operator {
private:
    Ranking ranking;
    set<int> file_type;
    set<int> minus, plus;
    vector<string> type;

    bool is_intitle = false;

public:
    Operator(vector<string> sub);

    //  AND, $, #, " " Operator 
    vector<di> _And(Trie &trie, vector<string> &query, int k);

    //  OR Operator
    vector<di> _Or(Trie &trie, vector<string> &query1, vector<string> &query2, int k, Trie& trie_title, bool& is_intitle);

    //  Synonym Operator
    vector<di> _Synonym(Trie &trie, vector<string> &query, int index, int k); 

    //  Minus or Plus case 
    set<int> _Minus_Plus(Trie &trie, string s, int k);

    //  Range case
    void _Range(vector<string> &query);

    //  Query processing
    vector<di> _Processing(Trie &trie, vector<string> &query, int k, Trie& trie_title, bool &is_intitle);
};


#endif