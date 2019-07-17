#include "utils.h"

std::vector < std::string > tokenizer(std::string text) {
    std::vector <std::string> cur, result;
    boost::split(cur, text, [](char c){ return c == ' '; });

    for (auto it : cur) {
        bool ok = true;
        for (auto jt : std::vector <std::string> {"I", "a", "about", "an", "are", "as", "at", "be", "by", "com", "for", "from", "how", "in", "is", "it", "of", "on", "or", "that", "the", "this", "to", "was", "what", "when", "where", "who", "will", "with", "the", "www"})
            if (it == jt) {
                ok = false;
                break;
            }
        if (ok) result.push_back(it);
    }
    return result;
}