#include <Operator.hpp> 

Operator::Operator(vector<string> sub_type, vector<string> sub_name) { 
    type = sub_type; 
    name = sub_name;    
}

//  Merge 2 results into a single result
vector<di> merge(vector<di> result1, vector<di> result2, int k) {
    result1.insert(result1.end(),result2.begin(),result2.end()) ; 
    sort(result1.begin(),result1.end(),[&](di x, di y){
        if (x.first - y.first > 0.00001)
            return true;
        else 
            return false;
    }) ; 
    int _min =  min(k,(int) result1.size())  ; 
    result1.resize(_min) ; 
    return result1 ;
}


//  AND, $, #, " " operator
vector<di> Operator::_And(Trie &trie, vector<string> &query, int k){
    return ranking.output(trie, query, k, minus, plus) ;
}


//  List of documents when combining query1 OR query 2
vector<di> Operator::_Or(Trie &trie, vector<string> &query1, vector<string> &query2, int k, Trie& trie_title, bool& is_intitle) {
    vector<di> result1= _Processing(trie,query1,k, trie_title, is_intitle) ;
    vector<di> result2 = _Processing(trie,query2,k, trie_title, is_intitle) ;
    return merge(result1, result2, k);
}


//  List of documents of synonym of string s
vector<di> Operator:: _Synonym(Trie &trie, vector<string> &query, int index, int k) {
    ifstream fin ; 
    string temp ; 
    vector <string> synonym ; 
    vector <di> result ; 
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
            vector<di>result1 = ranking.output(trie,tempo,k,minus,plus) ; 
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
    Ranking ranking ; 
    if (s[0] != '"') {
        for (auto it : trie.Search(s))
            result.insert(it.first);
        return result;
    }
    else {
        s.erase(s.begin()); s.pop_back() ; 
        vector<string> query = String::split(s) ;
        vector<int> result1 = FullyAppearance(trie, query) ;
        for (auto it :result1)
            result.insert(it) ; 
        return result ;  
    }
}


//  Range case
void Operator::_Range(vector<string> &query) {
    bool check = false;
    int i, j;
    vector<int> remove;
    for (i = 0 ; i < (int)query.size(); ++i) {
        int count_dot = 0;
        for (j = 0; j < query[i].length(); j++) {
            if (query[i][j] == '.')
                ++count_dot;
            if (count_dot > 2)
                remove.push_back(i);
        }
    }
    if (!remove.empty()) {
        for (int i = (int)remove.size()-1; i >=0; --i)
            query.erase(query.begin() + remove[i]);
    }

    for (i = 0 ; i < (int)query.size(); ++i) {
        for (j = 0; j < query[i].length()-1; j++)
            if (query[i][j] == '.' && query[i][j+1] == '.') {
                check = true;
                break;
            }
        if (check)
            break;
    }
    if (check) {
        query.erase(query.begin() + i);
        string s1, s2;
        s1 = query[i].substr(0, j);
        s2 = query[i].substr(j + 2, query[i].length() - 2 - j);
        for (int i = 1; i < (int)s1.size(); ++i)
            if (s1[i] > 57 || s1[i] < 48)
                return;
        for (int i = 1; i < (int)s2.size(); ++i)
            if (s2[i] > 57 || s2[i] < 48)
                return;
        if (s1[0] != '$' && (s1[0] > 57 || s1[0] < 48))
            return;
        if (s2[0] != '$' && (s2[0] > 57 || s2[0] < 48))
            return;

        bool check_dollar = false;
        if (s1[0] == '$') {
            s1.erase(s1.begin());
            check_dollar = true;
        }
        if (s1[0] == '$') {
            s2.erase(s2.begin());
            check_dollar = true;
        }
        
        int first = stoi(s1), second = stoi(s2);
        for (int i = first; i <= second; ++i) {
            query.push_back((check_dollar ? "$" : "") + to_string(i));
        }
    }
}


//  Wildcard case
vector<di> Operator::_Wildcard(Trie &trie, vector<string> query, int index_asterisk, int k) {
    vector<string> part1; part1.insert(part1.end(), query.begin(), query.begin() + index_asterisk);
    vector<string> part2; part2.insert(part2.end(), query.begin() + index_asterisk+1, query.end());

    vector<int> text1_vec = FullyAppearance(trie, part1);
    vector<int> text2_vec = FullyAppearance(trie, part2);

    set<int> text1, text2, text;
    for (int i = 0; i < (int)text1_vec.size(); ++i)
        text1.insert(text1_vec[i]);
    for (int i = 0; i < (int)text2_vec.size(); ++i)
        text2.insert(text2_vec[i]);
    for (auto i = text1.begin(); i != text1.end(); ++i)
        if (text2.find(*i) != text2.end())
            text.insert(*i);
    // for (auto it = text.begin(); it != text.end(); ++it) {
    //     system(("echo " + name[*it] + " >> log").c_str());
    // }
    // exit(0);
    string s1, s2;
    //s1.push_back('\"'); s2.push_back('\"');
    for (int i = 0; i < (int)part1.size(); ++i) {
        s1 += part1[i];
        s1.push_back(' ');
    }
    s1.pop_back(); //s1.push_back('\"');
    for (int i = 0; i < (int)part2.size(); ++i) {
        s2 += part2[i];
        s2.push_back(' ');
    }
    s2.pop_back(); //s2.push_back('\"');
    
    int nText = trie.NumberOfText();
    vector<double> score(nText);
    for (auto it = text.begin(); it != text.end(); ++it) {
        vector<string> query_mod;
        query_mod.push_back(s1);
        query_mod.push_back(s2);

        Aho::aho_corasick aho(query_mod);
        vector<vector<int>> result = aho.find_position_in(String::to_lower(AllText(*it)));
        int k1 = aho.all[query_mod[0]];
        int k2 = aho.all[query_mod[1]];
        for (int i = 0; i <(int)result[k1].size(); ++i) {
            for (int j = 0; j < (int)result[k2].size(); ++j) {
                int distance = result[k2][j] - result[k1][i] - (int)query[0].size();
                //system(("echo " + to_string(distance) + " >> log").c_str());
                if (distance >= 1 && distance < 50) {
                    score[*it] += 50 - distance;
                }

            }
            //exit(0);
        }
    }

    Heap heap;
    for (int i = 0; i < nText; ++i) 
        if (score[i] > 0.5) {
            heap.insert(di(score[i], i));
            //system(("echo " + to_string(score[i]) + " " + to_string(i) + " >> log").c_str());
    }

    return heap.topk_result(k);
}


vector<di> Operator::_Processing(Trie &trie, vector<string> &query, int k, Trie& trie_title, bool& is_intitle) {
    vector<di> result;

    for (int i = 0; i < (int)query.size(); ++i) {
        if (query[i] == "OR") { //  If query contains "OR", split it and implement the OR operator
            vector<string> query2(query.begin()+i+1, query.end());
            vector<string> query1(query.begin(), query.begin()+i);
            query.erase(query.begin()+i);

            return result = merge(result, _Or(trie, query1, query2, k, trie_title, is_intitle), k);
        }
    }

    int count = 0, index_type = 0;  //  Handle the filetype case
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
        if (query.empty()) {    //  If query contains only filetype:TYPE
            auto it = plus.begin();
            for (int i = 0; i < min(k, (int)plus.size()); ++i) {
                result.push_back(di(1,*it));
                ++it;
            }
            return result;
        }
    }
    bool check_title = false;   //  Handle the intitle case
    for (int i = 0; i < (int) query.size(); ++i) 
        if (query[i].size() > 8 && query[i].substr(0, 8) == "intitle:") {
        query[i].erase(query[i].begin(), query[i].begin() + 8);
        //system(("echo " + query[i] + " >> log").c_str());
        check_title = true;
    }

    if (check_title)    
        return _Processing(trie, query, k, trie_title, is_intitle = true);

    //  Handle case *
    int index_asterisk = 0;
    int count_asterisk = 0;
    for (int i = 0; i < (int)query.size(); ++i) {
        if (query[i] == "*") {
            ++count_asterisk;
            index_asterisk = i;
        }
    }
    if (count_asterisk > 1)
        return result;
    if (count_asterisk == 1)
        return _Wildcard(is_intitle ? trie_title : trie, query, index_asterisk, k);

    _Range(query);

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
    //for (auto it : result)
        //system(("echo " + to_string(it.second) + " >> log").c_str());
    return result;
}