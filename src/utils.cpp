#include <utils.h>


std::vector < std::string > tokenizer(std::string text, int flag) {
    std::vector <std::string> result;
    if (flag == 0) {
        std::vector <std::string> cur;
        boost::split(cur, text, [](char c){ return c == ' '; });

        for (auto it : cur) {
            boost::to_lower(it) ; 
            bool ok = true;
            for (auto jt : std::vector <std::string> {"i", "a", "about", "an", "are", "as", "at", "be", "by", "com", "for", "from", "how", "in", "is", "it", "of", "on", "or", "that", "the", "this", "to", "was", "what", "when", "where", "who", "will", "with", "the", "www"})
                if (it == jt) {
                    ok = false;
                    break;
                }
            if (ok) result.push_back(it);
        }
    } else {
        
    }
    return result;
}
void delete_char(std:: string &s){
 
    for(int i = 0; i < s.size(); ++i)
    {
        if (!((s[i] >= 'a' && s[i]<='z') || (s[i] >= '1' && s[i]<='9') || s[i]=='#' || s[i]=='-'||s[i]=='$'))
        {
            s[i] = '\0';
        }
    }
    for (int i=1;i<s.length();++i)
        if (s[i]=='$' || s[i]=='-' ||s[i]=='#') 
            s[i]='\0'; 
}
void preprocess_data(std::vector <std::string> &k){
    for (auto &it : k){
        boost::to_lower(it) ;
    }
    for (auto &i : k)
        delete_char(i) ; 
}

