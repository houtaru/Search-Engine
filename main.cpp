#include <iostream>
#include "Trie.hpp"

using namespace std;

int main() {
    Trie trie(256, 1);
    // trie.Insert("Beautiful", 0);
    // trie.Export();
    trie.Import();
    cout << "Oh yeah\n";
    cout << trie.Search("beautiful", 0);
}