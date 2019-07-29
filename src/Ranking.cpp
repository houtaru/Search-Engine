#include <Ranking.hpp>

double Ranking::weight_query(Trie &trie, string term, int count) {
    
    //  Get the number of documents containing term
    map<int, int> df = trie.Search(term);
    int df_term = df.size();

    return df_term ? log(1 + count * 1.0) * log(1 + nText * 1.0 / df_term) : 0;
}

vector<int> Ranking::FullyAppearance(Trie & trie, vector<string> query) {
    if (!query.size()) 
        return vector<int>(0);
    const int nText = trie.NumberOfText();
    vector<int> appear, res;
    map<int, int> MAP = trie.Search(query.back());
    for (auto x : MAP) appear.push_back(x.first); 
    for (int i = 0; i < appear.size(); ++i) {
        bool isFullyAppearance = true;
        for (int j = 0; j < (int) query.size(); ++j) {
            if (!trie.Search(query[j], appear[i])) {
                isFullyAppearance = 0;
                break;
            }
        }
        if (isFullyAppearance) {
            res.push_back(appear[i]); 
        }
    }
    return res;
}


// Convert all text to a string
string Ranking::AllText(int idText) {
    vector<string> filename;
    ifstream fin("TextData2/___index.txt");
    string st;
    while (getline(fin, st)) filename.push_back(st);
    ifstream data("TextData2/" + filename[idText]);
    string result;
    while (getline(data, st)) {
        for (char c : st) result.push_back(c);
        result.push_back(' ');
    }
    return result;
}


vector<di> Ranking::output(Trie &trie, vector<string> query, int k, set<int> &minus, set<int> &plus) {
    nText = trie.NumberOfText();
    vector<string> quote;
    for (auto it : query)
        system(("echo " + it + " >> log").c_str());
    exit(0);
    //  Split all quotes and store them separeately
    for (int i = 0; i < (int)query.size(); ++i) {
        if (query[i][0] == '"' && query[i].back() == '"') {
            quote.push_back(query[i]);
            query.erase(query.begin() + i);
            query.insert(query.begin() + i, tokenizer(quote.back()).begin(), tokenizer(quote.back()).end());
        }
    }
    for (auto it : query)
        system(("echo " + it + " >> log").c_str());
    exit(0);
    // MAP is the list of distinct terms in query
    map<string, int> MAP;
    for (int i = 0; i < (int)query.size(); ++i)
        MAP[query[i]]++;
    double length_query = 0;
    for (auto i : MAP)
        length_query += i.second * i.second;
    length_query = sqrt(length_query);

    //  Compute cosine between vector q (query) and vector d (document) ~ Score of documents
    //  We use ltl (logarithm - idf - length) for vector q and l1l (logarithm - 1 - legnth) for vector d

    //  Get number of terms appear in document i
    vector<int> number_terms(nText, 0);
    vector<double> score(nText, 0);
    for (auto i : MAP) {
        double w_tq = weight_query(trie, i.first, i.second);
        string word = i.first;
        
        map<int, int> df = trie.Search(word);
        
        //  Get the number of documents containing term and number of terms in those documents
        for (auto j : df) {
            //  Compute dot product of vector q and vector d
            ++number_terms[j.first];
            if (minus.find(j.first) == minus.end() && (plus.empty() || (!plus.empty() && plus.find(j.first) != plus.end())))
                score[j.first] += w_tq * (1 + log(j.second * 1.0));\
        }
        
    }
    //  Divide the score[i] by the length of document i and push it to a Heap
    Heap heap;
    for (int i = 0; i < nText; ++i) {
        double length = sqrt(trie.SumSquareLength(i));
        if (length > 0) {
            score[i] /= length*1.0;
        }
        if (score[i] > 0) {
            score[i] *= pow(number_terms[i] * 1.0 / (int)query.size(), 5) * 1.0 / length_query;
            heap.insert(di(score[i], i));
        }
    }
    if (quote.empty())
        return heap.topk_result(k);
    else {
        //  Case "Manchester United"
        score.clear();
        number_terms.clear();
        exit(0);
        //  Get top 50 results for Aho
        vector<di> temp = heap.topk_result(50);
        vector<int> text_sub;
        for (auto it : temp)
            text_sub.push_back(it.second);
        for (auto it : quote) {   
            map<int, int> df;
            double w_tq;
            if (it.size() >= 2) {
                Aho_Corasick Aho(256);
                string word = it.substr(1, it.size() - 2);
                Aho.Insert(word); 
                for (int idText : text_sub) {
                    system(("echo " + std::to_string(idText) + ' ' + std::to_string(0) + " >> log.txt").c_str());
                    int val = Aho.Value(String::to_lower(AllText(idText)));
                    if (val) {
                        //system(("echo " + std::to_string(idText) + ' ' + std::to_string(val) + " >> log.txt").c_str());
                        df[idText] = val;
                    }
                }
                w_tq = nText;
            }

            //  Get the number of documents containing term and number of terms in those documents
            for (auto j : df) {
                //  Compute dot product of vector q and vector d
                ++number_terms[j.first];
                if (minus.find(j.first) == minus.end() && (plus.empty() || (!plus.empty() && plus.find(j.first) != plus.end())))
                    score[j.first] += w_tq * (1 + log(j.second * 1.0));\
            }
        }
        //  Divide the score[i] by the length of document i and push it to a Heap
        for (int i = 0; i < nText; ++i) {
            double length = sqrt(trie.SumSquareLength(i));
            if (length > 0) {
                score[i] /= length*1.0;
            }
            if (score[i] > 0) {
                score[i] *= pow(number_terms[i] * 1.0 / (int)query.size(), 5) * 1.0 / length_query;
                heap.insert(di(score[i], i));
            }
        }
        return heap.topk_result(k);
    }
}