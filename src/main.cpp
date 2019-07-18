#include <Trie.hpp>
#include <iostream>

int main() {
    Trie ss(200);
    for (int i = 0; i < 5; ++i) {
        std::string s;
        std::cin >> s;
        ss.Insert(s, 0);
    }

    int cnt = 5;
    for (auto it : ss.auto_suggestion("me")) {
        cnt--;
        std::cout << it << "\n";
        if (cnt == 0) break;
    }

    return 0;
}