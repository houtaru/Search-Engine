#include <utils.h>

std::vector < std::string > tokenizer(std::string text, int flag) {
    std::vector <std::string> result;
    if (flag == 0) {
        std::vector <std::string> cur;
        boost::split(cur, text, [](char c){ return c == ' '; });

        for (auto it : cur) {
            bool ok = true;
            std::string s;
            for (char c : it) if (String::isAlNum(c) || c == '$' || c == '#')
                s.push_back(c);
            if (ok && !s.empty()) result.push_back(s);
        }
    }
    return result;
}

std::string Lowercase(std::string st) {
    for(char & c: st) {
        if ('A' <= c && c <= 'Z') c += 32;
    }
    return st;
}


// Convert all text to a string
string AllText(int idText) {
    vector<string> filename;
    ifstream fin("TextData2/___index.txt");
    string st;
    while (getline(fin, st)) filename.push_back(st);
    fin.close();
    ifstream data("TextData2/" + filename[idText]);
    string result;
    while (getline(data, st)) {
        for (char c : st) result.push_back(c);
        result.push_back(' ');
    }
    data.close();
    return result;
}
