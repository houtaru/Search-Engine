#include "Trie.hpp"

#include <iostream>
#include <fstream>
#include <queue>

#include <utils.h>

Trie::Node::Node() {}
Trie::Node::Node(int nChild) {
    child.resize(nChild, nullptr);
}

Trie::Node::~Node() {
    for (int i = 0; i < child.size(); ++i) delete child[i];
}

Trie::Trie(int nChild):nChild(nChild){
    root = new Node(nChild);
}

Trie::~Trie() {
    delete root;
}

bool Trie::HasText(int id) {
    return UsedText.count(id);
}

int Trie::NumberOfText() {
    return (UsedText.rbegin()) -> first + 1;
}

long long Trie::SumSquareLength(int id) {
    return UsedText[id];
} 
void Trie::AddText(int idText, std::string text) {
    if (UsedText.count(idText)) {
        std::cerr << "Have add " << idText << "already\n";
        return;
    }
    UsedText[idText] = 0;
    std::vector<std::string> words = tokenizer(text);
    for (std::string word : words) {
        Insert(word, idText);
    }
}

void Trie::Insert(std::string word, int id) {
    Node * p = root;
    for (char c : word) {
        if (!p -> child[c]) p -> child[c] = new Node(nChild);
        p = p -> child[c];
    }
    // l^2 -> (l + 1) ^ 2 => Add to UsedText 2l + 1
    UsedText[id] += p ->distribution[id] * 2 + 1;
    ++p -> distribution[id];
}

int Trie::Search(std::string word, int id) {
    Node * p = root;
    for (char c : word) {
        //std::cerr << c << ' ' << p ->child.size() << ' ' << p -> distribution.size() << '\n';
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

void Trie::Import() {
    //system("mkdir Data/");
    std::ifstream fin("Data/Trie.data");
    if (!fin.is_open()) {
        return;
    }
    std::queue<Node *> q;
    q.push(root);
    int cnt = 0;
    while (!q.empty()) {
        //++cnt;
        //std::cout << cnt << '\n';
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
            UsedText[id] += 1ll * val * val;
         //   ++cnt;
            p -> distribution[id] = val;
        }
        for (int i = 0; i < nChild; ++i) if (p -> child[i]) q.push(p -> child[i]);
    }
    //std::cout << "All words = " << cnt << '\n';
}


bool Trie::Loading() {
    std::ifstream fin("TextData2/___index.txt");
    std::string filename;
    int cnt = 0;
    int totalChar = 0;
    bool isChanged = false; 
    while (getline(fin, filename)) {
        if (HasText(cnt)) {
       //     std::cerr << "Have added " << cnt << "already\n";
            ++cnt;
            continue;
        }
        std::ifstream data("TextData2/" + filename);
        std::string st;
        std::string text;
        while (getline(data, st)) {
            for (char c : st) {
                isChanged = true;
                if ('A' <= c && c <= 'Z') c += 32;
                if (('a' <= c && c <= 'z') || ('0' <= c && c <= '9') || c == ' ')
                text.push_back(c);
            }
            text.push_back(' '); 
        }
        AddText(cnt, text);
        totalChar += text.size();
        ++cnt;
    }
    return isChanged;
}

void Trie::Export() {
    std::ofstream fout("Data/Trie.data");
    if (!root) {
        fout << 0 << ' ' << 0 << '\n';
        return;
    }
    std::queue<Node *> q;
    q.push(root);
    int cnt = 0;
    while (!q.empty()) {
        Node * p = q.front();
        q.pop();
        if (p -> distribution.size()) ++cnt;
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
    //std::cerr << "Total Node on trie: " << cnt << '\n';
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


Aho_Corasick::Node::Node() {}
Aho_Corasick::Node::Node(int nChild, Node * par, int par_id): par(par), par_id(par_id) {
    child.resize(nChild, nullptr);
    go.resize(nChild, nullptr);
    cntLeaf = 0;
    if (par) depth = par -> depth + 1;
    else depth = 0;
}

Aho_Corasick::Node::~Node() {}

void Aho_Corasick::Insert(std::string word) {
    Node * p = root;
    for (char c : word) {
        if (!p -> child[c]) p -> child[c] = new Node(nChild, p, c);
        p = p -> child[c];
    }   
    p -> cntLeaf++;
   // std::cout << '\n';
}

Aho_Corasick::Node * Aho_Corasick::Go(Node * v, int id) {
    if (!v -> go[id]) {
        if (v -> child[id]) {
            v -> go[id] = v -> child[id];
        } else {
            v -> go[id] = (v == root ? root : Go(GetLink(v), id));
        }
    }
    return v -> go[id];
}

Aho_Corasick::Node * Aho_Corasick::GetLink(Node * v) {
    if (!v -> link) {
        if (v == root || v -> par == root) v -> link = root;
        else {
            v -> link = Go(GetLink(v -> par), v -> par_id);
        }
    }
    return v -> link;
}

int Aho_Corasick::Value(std::string text) {
    Node * p = root;
    int ans = 0;
    for (char c : text) {
        p = p -> child[c];
        if (!p) p = root;
        ans += p ->cntLeaf;
    }
    return ans;
}
using namespace std;

int Aho_Corasick::ValueTrace(std::string text, std::vector<int> &appear, int numchar) {
    Node * p = root;
    int id = 0;
    int ans = 0, now = 0, pos = std::min(numchar, (int)text.size());
    std::vector<int> disappear(appear.size() + 1, 0);
    // system(("echo " + std::to_string(appear.size()) + " >> log.txt").c_str());
    for (char c : text) if (0 <= c && c < nChild) {
        p = p -> child[c];
        if (!p) p = root;
        if (p -> cntLeaf) {
            system(("echo " + to_string(p -> cntLeaf) + ' ' + to_string(id) + ' ' + to_string(p -> depth) + " >> log.txt").c_str());
            appear[id - p -> depth + 1]++;
            disappear[id + 1]++;
        }
        now += p -> cntLeaf;
        if (id >= numchar) now -= appear[id - numchar];
        if (ans <= now) {
            ans = now;
            pos = id;
        }
        ++id;
    }
    if (appear.size()) appear[0] -= disappear[0];
    for (int i = 1; i < id; ++i) appear[i] += appear[i - 1] - disappear[i];
    return pos;
}


void Aho_Corasick::BuildSumSuffix(Node * p) {
    if (p == nullptr) p = root;
    Node * link = GetLink(p);
    p -> cntLeaf += link -> cntLeaf;
    for (int i = 0; i < nChild; ++i) if (p -> child[i])
        BuildSumSuffix(p -> child[i]);
}


Aho_Corasick::Aho_Corasick(int nChild):nChild(nChild){
    root = new Node(nChild, nullptr, -1);
}

Aho_Corasick::~Aho_Corasick() {
    delete root;
}