#ifndef __TRIE__
#define __TRIE__ 

#include <vector>
struct Node {
    std::vector<Node *> child; 
    std::vector<int> cntAppear; // number word X appear in text[i]
    Node();
    Node(int nChild, int nText);
    ~Node();
};

class Trie {
private:
    Node * root;
    int nChild, nText;
public:
    Trie(int nChild, int nText);
    ~Trie();
    // Import Trie from file
    void Import();
    // Export Trie to file
    void Export();
    // Insert word in text[id]
    void Insert(std::string word, int id);
    // Return the number of word appear in text[id]
    int Search(std::string word, int id);
    // Return vector cntAppear of word 
    std::vector<int> Search(std::string word);
};

#endif // __TRIE__