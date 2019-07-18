#include "Trie.hpp"

#include <iostream>
#include <fstream>
#include <queue>

#include <utils.h>

Trie::Node::Node() {}
Trie::Node::Node(int nChild) {
    child.resize(nChild, nullptr);
}

Trie::Node::~Node() {}

Trie::Trie(int nChild):nChild(nChild){
    root = new Node(nChild);
}

Trie::~Trie() {}

void Trie::AddText(int idText, std::string text) {
    if (UsedText.count(idText)) {
        std::cerr << "Have add " << idText << "already\n";
        return;
    }
    std::vector<std::string> words = tokenizer(text);
    for (std::string word : words) {
        Insert(word, idText);
    }
    UsedText.insert(idText);
}

void Trie::Insert(std::string word, int id) {
    Node * p = root;
    for (char c : word) {
        if (!p -> child[c]) p -> child[c] = new Node(nChild);
        p = p -> child[c];
    }   
    ++p -> distribution[id];
}

int Trie::Search(std::string word, int id) {
    Node * p = root;
    for (char c : word) {
        std::cerr << c << ' ' << p ->child.size() << ' ' << p -> distribution.size() << '\n';
        if (!p -> child[c]) return 0;
        p = p -> child[c];
    }
    return p -> distribution[id];
}

std::map<int, int> Trie::Search(std::string word) {
    Node * p = root;
    for (char c : word) {
        if (!p -> child[c]) {
            std::map<int, int> zero;
            return zero;
        }
        p = p -> child[c];
    }
    return p -> distribution;
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
        int nChild, activeChild, nText;
        fin >> nChild >> activeChild >> nText;
        if (!p) p = new Node(nChild);
        for (int i = 0; i < activeChild; ++i) {
            int id;
            fin >> id;
            p -> child[id] = new Node(nChild);
        }
        for (int i = 0; i < nText; ++i) {
            int id, val;
            fin >> id >> val;
            UsedText.insert(id);
            p -> distribution[id] = val;
        }
        for (int i = 0; i < nChild; ++i) if (p -> child[i]) q.push(p -> child[i]);
    }
}

void Trie::Export() {
    system("mkdir Data/");
    std::ofstream fout("Data/Trie.data");
    if (!root) {
        fout << 0 << ' ' << 0 << '\n';
        return;
    }
    std::queue<Node *> q;
    q.push(root);
    while (!q.empty()) {
        Node * p = q.front();
        q.pop();
        std::vector<int> ActiveChild;
        for (int i = 0; i < p -> child.size(); ++i) if (p -> child[i]) {
            ActiveChild.push_back(i);
        }
        fout << p -> child.size()  << ' ' << ActiveChild.size() << ' ' << p -> distribution.size() << '\n';
        for (int id : ActiveChild) fout << id << ' '; fout << '\n';
        for (auto dist : p -> distribution) fout << dist.first << ' ' << dist.second << ' ';
        fout << '\n'; 
        for (int i = 0; i < p -> child.size(); ++i) if (p -> child[i]) q.push(p -> child[i]);
    }
}

std::vector < std::string > Trie::auto_suggestion(std::string text, int lim) {
    Node * p = root;
    for (int w : text) {
        if (p->child[w] == NULL) return {"null"};
        p = p->child[w];
    }

    std::vector < std::string > result;

    std::function<void(Node *, std::string)> suggestion = [&](Node * p, std::string s) {
        if (p == NULL || result.size() >= lim) return;
        if (!p->distribution.empty()) {
            result.push_back(text + s);
        }
        for (int i = 0; i < nChild; ++i) if (p->child[i] != NULL) {
            suggestion(p->child[i], s + (char) i);
        }
    };
    suggestion(p, "");

    return result;
}
