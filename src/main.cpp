#include <iostream>
#include <Trie.hpp>
#include <utils.h>

using namespace std;

int main() {
    string s; getline(cin, s);
    for (auto it : tokenizer(s))
        cout << it << "\n";
    // Trie trie(256);
    // // trie.Insert("beautiful", 0);
    // // trie.Insert("beautifully", 1);
    // // trie.Export();
    // trie.Import();
    // trie.Insert("beautifully", 1);
    // cout << "Oh yeah\n";
    // cout << trie.Search("beautifully", 1);
}
