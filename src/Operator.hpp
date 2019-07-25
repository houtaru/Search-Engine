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
    //And Operator 
    vector<int>_And(Trie &trie, vector<string> query,int k);

    //Or Operator
    vector<int>_Or(Trie &trie, vector<string> query1,vector<string> query2,int k );

    //Synonym Operator
    vector<int>_Synonym(Trie &trie, string s,int k ) ; 

    //Minus case 
    vector<int>_Minus(Trie &trie,vector<string> query,int k) ;

    //" " case
    vector<int> _FullyAppear(Trie &trie,vector<string> query,int k) ;
 
};


#endif
