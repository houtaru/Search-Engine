#include <Heap.hpp>

int Heap::parent(int i) { return (i - 1)/2; }

int Heap::left(int i) { return 2*i + 1; }

int Heap::right(int i) { return 2*i + 2; }

int Heap::size() { return (int)HEAP.size(); }

void swap_mode(pair<double, int> &a, pair<double, int> &b) {
    pair<double, int> c;
    c.first = a.first; c.second = a.second;
    a.first = b.first; a.second = b.second;
    b.first = c.first; b.second = c.second;
}

void Heap::insert(pair<double, int> x) {
    HEAP.push_back(x);
    int cur = size() - 1;
    
    // Upheap
    while (cur > 0 && HEAP[cur].first - HEAP[parent(cur)].first > 0.00001) {
        swap_mode(HEAP[cur], HEAP[parent(cur)]);
        cur = parent(cur);
    }
}

void Heap::heapify(int i, int size_sub) {
    int r = right(i), l = left(i);
    int biggest = i;
    
    // If left child > biggest, then swap index
    if (l < size_sub && HEAP[biggest].first - HEAP[l].first < 0.00001)
        biggest = l;
    // Similar to right child
    if (r < size_sub && HEAP[biggest].first - HEAP[r].first < 0.00001)
        biggest = r;
    
    // If index of the biggest is not this node, swap and heapify that index
    if (biggest != i) {
        swap_mode(HEAP[biggest], HEAP[i]);
        heapify(biggest, size_sub);
    }
}

vector<di> Heap::topk_result(int k) {
    vector<di> result;
    
    for (int i = 0; i < k; ++i) { 
        if (i >= size())
            break;
        result.push_back(di(HEAP[0].first, HEAP[0].second));
        //system(("echo " + to_string(result.back().first) + " " + to_string(result.back().second) + " >> log").c_str());
        swap_mode(HEAP[0], HEAP[(size()-1) - i]);
        heapify(0, (size()-1) - i);
    }
    
    return result;
}
