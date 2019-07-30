#ifndef AHO_H_DEFINED
#define AHO_H_DEFINED

using namespace std;
#include <algorithm>
#include <iostream>
#include <cstring>
#include <cstdio>
#include <vector>
#include <queue>
#include <map>

namespace Aho {
    // Aho-Corasick from SuprDewd
    struct aho_corasick {
        map<string,int> all;
        struct out_node {
            string keyword; out_node *next;
            inline out_node(string k, out_node *n) : keyword(k), next(n) { }
        };
        struct go_node {
            map<char, go_node*> next;
            out_node *out; go_node *fail;
            inline go_node() { out = NULL; fail = NULL; }
        };
        go_node *go;
        int N;

        aho_corasick(vector<string> keywords);

        vector < pair <int, int> >  search(string s);
        
        vector < vector <int> > find_position_in(std::string s);
    };
}

#endif