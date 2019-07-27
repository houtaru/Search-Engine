#include <Engine/Utils/String.hpp>

const char trim_blanks[] = " \t\r\n";

std::string String::ltrim(const std::string &str) {
    size_t stpos = str.find_first_not_of(trim_blanks);

    if (stpos == std::string::npos) return "";

    return str.substr(stpos);
}

std::string String::rtrim(const std::string &str) {
    size_t endpos = str.find_last_not_of(trim_blanks);
    if (endpos == std::string::npos) return "";

    return str.substr(0, endpos + 1);
}

std::string String::trim(const std::string &str) {
    return ltrim(rtrim(str));
}

std::vector < std::string > String::split(const std::string& str, char delim, bool flag) {
    //std::string stopwords = "I a about an are as at be by com for from how in is it of on or that the this to was what when where who will with the www";

    std::vector < std::string > result;
    std::string cur;
    
    for (int i = 0; i < str.size(); ++i) {
        if (i + 2 < str.size() && str[i] == 'A' && str[i + 1] == 'N' && str[i + 2] == 'D') {
            result.push_back(str.substr(i, 3));
            i += 2;
        } else if (i + 1 < str.size() && str[i] == 'O' && str[i + 1] == 'R') {
            result.push_back(str.substr(i, 2));
            i += 1;
        } else if (str[i] == '\"') {
            if (!cur.empty()) {
                result.push_back(to_lower(cur));
            }
            cur = str[i];
            while (++i < str.size() && str[i] != '\"') cur += str[i];
            cur += str[i];
            if (!cur.empty()) result.push_back(to_lower(cur));
            cur.clear();
        } else if (str[i] == ' ') {
            if (!cur.empty()) {
                result.push_back(to_lower(cur));
            }
            cur.clear();
        } else if (i + 2 < str.size() && str[i] == '.' && str[i + 1] == '.') {
            cur += str[i]; cur += str[++i];
        } else if (isalnum(str[i]) || std::string("!?~+:-$#*\".").find(str[i]) != std::string::npos) {
            cur += str[i];
        }
    }
    if (!cur.empty()) result.push_back(to_lower(cur));
    return result;
}

std::string String::to_lower(std::string str) {
    boost::algorithm::to_lower(str);
    return str;
}


bool String::isAlNum(char c) {
    return ('A' <= c && c <= 'Z') || ('a' <= c && c <= 'z') || ('0' <= c && c <= '9');
}
