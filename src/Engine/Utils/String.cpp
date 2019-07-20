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
    std::stringstream ss(str);          // buffers
    std::string item;                   // current thing
    std::vector < std::string > elements;  // all things

    while (std::getline(ss, item, delim)) {
        std::string res = item;
        if (!flag) {
            res = "";
            for (int i = 0; i < item.size(); ++i) if (isalnum(item[i])) {
                res += item[i];
            } else {
                if (std::string("-$#*").find(item[i]) != std::string::npos) {
                    res += item[i];
                } else if (i + 2 < item.size() && item[i] == '.' && item[i + 1] == '.') {
                    res += item[i] + item[++i];
                }
            }
        }
        elements.push_back(res);
    }
    return elements;
}