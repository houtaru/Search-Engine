#include <Ranking.hpp>

double Ranking::weight_query(Trie &trie, string term, int count) {
    
    //  Get the number of documents containing term
    map<int, int> df = trie.Search(term);
    int df_term = df.size();

    return df_term ? (1 + log(count * 1.0)) * log(nText * 1.0 / df_term) : 0;
}

vector<int> Ranking::output(Trie &trie, vector<string> query, int k) {
    nText = trie.NumberOfText();
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
    vector<int> number_terms(nText);
    vector<double> score(nText, 0);
    for (auto i : MAP) {
        double w_tq = weight_query(trie, i.first, i.second);
        //  Get the number of documents containing term and number of terms in those documents
        map<int, int> df = trie.Search(i.first);
        for (auto j : df) {
            //  Compute dot producgt of vector q and vector d
            ++number_terms[j.first];
            score[j.first] += w_tq * (1 + log(j.second * 1.0));
        }
    }

    //  Divide the score[i] by the length of document i and push it to a Heap
    Heap heap;
    for (int i = 0; i < nText; ++i) {
        double length = sqrt(trie.SumSquareLength(i));
        if (length > 0.00001)
            score[i] /= length;
        if (score[i] > 0.00001) {
            score[i] *= pow(number_terms[i] * 1.0 / (int)query.size(), 5) * 1.0 / length_query;
            heap.insert(pair<double, int>(score[i], i));
        }
    }

    return heap.topk_result(k);
}