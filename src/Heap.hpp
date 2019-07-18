#ifndef __HEAP__
#define __HEAP__

#include <bits/stdc++.h>

using namespace std;

struct Heap{
    vector<pair<double, int>> HEAP;
    
    int parent(int i);
    int left(int i);
    int right(int i);
    int size();
    
    void insert(pair<double, int> x);
    void heapify(int i, int size_sub);
    vector<int> topk_result(int k);
};

#endif //__HEAP__