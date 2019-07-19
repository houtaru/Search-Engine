#ifndef __TRIE__
#define __TRIE__ 

#include <vector>
#include <map> 
#include <set>
#include <utils.h>

class Trie {
private:
    struct Node {
        std::vector<Node *> child; 
        std::map<int, int> distribution; // number word X appear in text[i]
        Node();
        Node(int nChild);
        ~Node();
    };

    Node * root;
    int nChild;
    // Store sum square of words
    std::map<int, long long> UsedText;
public:
    Trie(int nChild);
    
    ~Trie();
    
    bool HasText(int id);
    int NumberOfText();
    long long SumSquareLength(int id);
    void AddText(int idText, std::string text);

    // Import Trie from file
    void Import();
    
    // Export Trie to file
    void Export();
    
    // Insert word in text[id]
    void Insert(std::string word, int id);
    
    // Return the number of word appear in text[id]
    int Search(std::string word, int id);
    
    // Return vector cntAppear of word 
    std::map<int, int> Search(std::string word);

    //Auto suggestion
    std::vector < std::string > auto_suggestion(std::string text, int lim = 5);
};

#endif // __TRIE__