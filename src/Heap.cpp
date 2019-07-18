#include <Heap.hpp>

int Heap::parent(int i) { return (i - 1)/2; }

int Heap::left(int i) { return 2*i + 1; }

int Heap::right(int i) { return 2*i + 2; }

int Heap::size() { return (int)HEAP.size(); }

void Heap::insert(pair<int, int> x) {
    HEAP.push_back(x);
    int cur = size() - 1;
    
    // Upheap
    while (cur > 0 && HEAP[cur].first > HEAP[parent(cur)].first) {
        swap(HEAP[cur], HEAP[parent(cur)]);
        cur = parent(cur);
    }
}

void Heap::heapify(int i, int size_sub) {
    int r = right(i), l = left(i);
    int biggest = i;
    
    // If left child > biggest, then swap index
    if (l < size_sub && HEAP[biggest].first < HEAP[l].first)
        biggest = l;
    // Similar to right child
    if (r < size_sub && HEAP[biggest].first < HEAP[r].first)
        biggest = r;
    
    // If index of the biggest is not this node, swap and heapify that index
    if (biggest != i) {
        swap(HEAP[biggest], HEAP[i]);
        heapify(biggest, size_sub);
    }
}

vector<int> Heap::topk_result(int k) {
    vector<int> result;
    
    for (int i = 0; i < k; ++i) {
        result.push_back(HEAP[0].second);
        swap(HEAP[0], HEAP[(size()-1) - i]);
        heapify(0, (size()-1) - (i+1));
    }
    
    return result;
}
