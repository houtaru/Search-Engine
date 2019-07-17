#include "Trie.hpp"

#include <iostream>
#include <fstream>
#include <queue>

Node::Node() {}
Node::Node(int nChild, int nText) {
    child.resize(nChild, nullptr);
    cntAppear.resize(nText, 0);
}

Node::~Node() {}

Trie::Trie(int nChild, int nText):nChild(nChild), nText(nText) {
    root = new Node(nChild, nText);
}

Trie::~Trie() {}

void Trie::Insert(std::string word, int id) {
    Node * p = root;
    for (char c : word) {
        if (!p -> child[c]) p -> child[c] = new Node(nChild, nText);
        p = p -> child[c];
    }   
    ++p -> cntAppear[id];
}

int Trie::Search(std::string word, int id) {
    Node * p = root;
    for (char c : word) {
        std::cerr << c << ' ' << p ->child.size() << ' ' << p ->cntAppear.size() << '\n';
        if (!p -> child[c]) return 0;
        p = p -> child[c];
    }
    return p -> cntAppear[id];
}

std::vector<int> Trie::Search(std::string word) {
    Node * p = root;
    for (char c : word) {
        if (!p -> child[c]) return std::vector<int>(0);
        p = p -> child[c];
    }
    return p -> cntAppear;
}

void Trie::Import() { //Bug
    //system("mkdir Data/");
    std::ifstream fin("Data/Trie.data");
    if (!fin.is_open()) {
        return;
    }
    std::queue<Node *> q;
    q.push(root);
    int cnt = 0;
    while (!q.empty()) {
        Node * &p = q.front();
        q.pop();
        int nChild, nText;
        fin >> nChild >> nText;
        if (!nText) continue;
        p = new Node(nChild, nText);
        std::cerr << "Sayhi";
        for (int i = 0; i < nChild; ++i) q.push(p -> child[i]);
        for (int i = 0; i < nText; ++i) fin >> p -> cntAppear[i];
    }
}

void Trie::Export() {
    //system("mkdir Data/");
    std::ofstream fout("Data/Trie.data");
    std::queue<Node *> q;
    q.push(root);
    while (!q.empty()) {
        Node * p = q.front();
        q.pop();
        if (!p) fout << 0 << ' ' << 0 << '\n';
        else {
            fout << p -> child.size() << ' ' << p -> cntAppear.size() << ' ';
            for (int i = 0; i < p -> cntAppear.size(); ++i) 
                fout << p -> cntAppear[i] << ' ';
            fout << '\n';
            for (int i = 0; i < p -> child.size(); ++i) q.push(p -> child[i]);
        }
    }
}


