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

    int nChild;
    // Store sum square of words
    std::map<int, long long> UsedText;
public:
    Node * root;
    Trie(int nChild);
    
    ~Trie();
    
    void Try(Node * p, std::string s);
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

class Aho_Corasick {
private:
    struct Node {
        std::vector<Node *> child, go; 
        Node * par, *link;
        int par_id;
        int cntLeaf;
        Node();
        Node(int nChild, Node * par, int par_id);
        ~Node();
    };
    Node * root;

    int nChild;
    // Store sum square of words

   
public:
    
    Aho_Corasick(int nChild);
    ~Aho_Corasick();

    Node * Go(Node * v, int id);
    Node * GetLink(Node * v);
    void BuildSumSuffix(Node * p);
    // Insert a word to tree
    void Insert(std::string word);
    // Find the number appear all words in text
    int Value(std::string text);
};

#endif // __TRIE__
