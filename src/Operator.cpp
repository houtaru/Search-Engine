#include <Operator.hpp> 

Operator::Operator(vector<string> sub) { type = sub; }

//  Merge 2 results into a single result
vector<int> merge(vector<int> result1, vector<int> result2, int k) {
    result1.insert(result1.end(),result2.begin(),result2.end()) ; 
    sort(result1.begin(),result1.end(),greater<int>()) ; 
    int _min =  min(k,(int) result1.size())  ; 
    result1.resize(_min) ; 
    return result1 ;
}


//  AND, $, #, " " operator
vector<int> Operator::_And(Trie &trie, vector<string> &query, int k){
    return ranking.output(trie, query, k, minus, plus) ;
}


//  List of documents when combining query1 OR query 2
vector<int> Operator::_Or(Trie &trie, vector<string> &query1, vector<string> &query2, int k, Trie& trie_title, bool& is_intitle) {
    vector<int> result1= _Processing(trie,query1,k, trie_title, is_intitle) ;
    vector<int> result2 = _Processing(trie,query2,k, trie_title, is_intitle) ;
    return merge(result1, result2, k);
}


//  List of documents of synonym of string s
vector<int> Operator:: _Synonym(Trie &trie, vector<string> &query, int index, int k) {
    ifstream fin ; 
    string temp ; 
    vector <string> synonym ; 
    vector <int> result ; 
    fin.open(("Synonym_data/"+query[index]).c_str());
    //if string s doesn't have synonym, return vector 0 
    if (!fin.is_open())
        return result ; 
    while (!fin.eof()){
        getline(fin,temp) ;
        synonym.push_back(temp) ; 
    }
    for (auto i: synonym) 
        {
            vector<string> tempo;
            tempo.push_back(i) ; 
            vector<int>result1 = ranking.output(trie,tempo,k,minus,plus) ; 
            if (!result1.empty())
                query.insert(query.begin()+index+1, i);
            result = merge(result, result1, k);
            tempo.clear() ; 
            result1.clear() ;
        }
    return result ; 
}


//  List of documents containing minus word
set<int> Operator::_Minus_Plus(Trie &trie, string s, int k ) {
    set<int> result;
    for (auto it : trie.Search(s))
        result.insert(it.first);
    return result;
}


vector<int> Operator::_Processing(Trie &trie, vector<string> &query, int k, Trie& trie_title, bool& is_intitle) {
    vector<int> result;

    for (int i = 0; i < (int)query.size(); ++i) {
        if (query[i] == "OR") { //  If query contains "OR", split it and implement the OR operator
            vector<string> query2(query.begin()+i+1, query.end());
            vector<string> query1(query.begin(), query.begin()+i);
            query.erase(query.begin()+i);

            return result = merge(result, _Or(trie, query1, query2, k, trie_title, is_intitle), k);
        }
    }

    int count = 0, index_type = 0;
    for (int i = 0; i < (int)query.size(); ++i) {
        if (query[i].substr(0, 9) == "filetype:") {
            ++count;
            index_type = i; 
        }
        if (count > 1)
            return result;
    }
    if (count == 1) {
        query[index_type].erase(query[index_type].begin(), query[index_type].begin() + 9);
        for (int i = 0; i < (int)type.size(); ++i) {
            if (type[i] == query[index_type]) {
                plus.insert(i);
            }
        }
        query.erase(query.begin()+index_type);
        if (query.empty()) {
            auto it = plus.begin();
            for (int i = 0; i < min(5, (int)plus.size()); ++i) {
                result.push_back(*it);
                ++it;
            }
            return result;
        }
    }

    for (int i = 0; i < (int) query.size(); ++i) 
        if (query[i].size() > 8 && query[i].substr(0, 8) == "intitle:") {
        query[i].erase(query[i].begin(), query[i].begin() + 8);
        system(("echo " + query[i] + " >> log").c_str());
        return _Processing(trie, query, k, trie_title, is_intitle = true);
    }

    int index = 0;
    while (index < (int)query.size()) {
        if (query[index] == "AND") {    //  If query contains "AND", delete that term
            query.erase(query.begin() + index);
            --index;
        }


        if (query[index][0] == '-' || query[index][0] == '+' || query[index][0] == '~') {   //  If query[index] begins with sign operator
            char temp_char = query[index][0];
            query[index].erase(query[index].begin());   //  Remove the '-' or '+' or '~'

            if (temp_char == '-' || temp_char == '+') {   //  The Minus or Plus operator case
                set<int> temp_set = _Minus_Plus(trie, query[index], k);
                for (auto it : temp_set) {
                    if (temp_char == '-')
                        minus.insert(it);
                    if (temp_char == '+')
                        plus.insert(it);
                }
            }

            if (temp_char == '~') {   //  The Synonym operator case
                result = merge(result, _Synonym(!is_intitle ? trie : trie_title, query, index, k), k);
                query.erase(query.begin() + index);
                --index;
            }
        }
        ++index;
    }
    result = merge(result, _And(!is_intitle ? trie : trie_title, query, k), k);
    return result;
}