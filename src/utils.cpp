#include <utils.h>

std::vector < std::string > tokenizer(std::string text, int flag) {
    std::vector <std::string> result;
    if (flag == 0) {
        std::vector <std::string> cur;
        boost::split(cur, text, [](char c){ return c == ' '; });

        for (auto it : cur) {
            bool ok = true;
            std::string s;
            for (char c : it) if (isalnum(c)) s.push_back(c);
            for (auto jt : std::vector <std::string> {"I", "a", "about", "an", "are", "as", "at", "be", "by", "com", "for", "from", "how", "in", "is", "it", "of", "on", "or", "that", "the", "this", "to", "was", "what", "when", "where", "who", "will", "with", "the", "www"})
                if (s == jt) {
                    ok = false;
                    break;
                }
            if (ok && !s.empty()) result.push_back(s);
        }
    } {
        
    }
    return result;
}
