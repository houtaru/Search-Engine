#include <Ranking.hpp>

double Ranking::weight_query(Trie &trie, string term, int count) {
    
    //  Get the number of documents containing term
    map<int, int> df = trie.Search(term);
    int df_term = df.size();
    // cerr << "Query " << term << ' ' << count << ' ' << df_term << ' ' << nText << '\n';
    return (1.0 + log(count * 1.0)) * log(1.0 + nText * 1.0 / df_term);
}

vector<int> Ranking::output(Trie &trie, vector<string> query, int k) {
    nText = trie.NumberOfText();
    // MAP is the list of distinct terms in query
    map<string, int> MAP;
    for (int i = 0; i < (int)query.size(); ++i)
        MAP[query[i]]++;
    
    //  Compute cosine between vector q (query) and vector d (document) ~ Score of documents
    //  We use ltl (logarithm - idf - length) for vector q and l1l (logarithm - 1 - legnth) for vector d
    vector<double> score(nText, 0);
    for (auto i : MAP) {
        double w_tq = weight_query(trie, i.first, i.second);
        //  Get the number of documents containing term and number of terms in those documents
        map<int, int> df = trie.Search(i.first);
        for (auto j : df) {
            //  Compute dot producgt of vector q and vector d
            score[j.first] += w_tq * (1 + log(j.second * 1.0));
        }
    }

    cout << endl;
    //  Divide the score[i] by the length of document i and push it to a Heap
    Heap heap;
    for (int i = 0; i < nText; ++i) {
        double length = sqrt(trie.SumSquareLength(i));
        if (length > 0.00001)
            score[i] /= length;
        //cerr << "Text " << i << " with Score " << score[i] << ' ' << trie.SumSquareLength(i) << '\n'; 
        if (score[i] > 0.00001) {
            heap.insert(pair<double, int>(score[i], i));
            //cerr << "Insert text " << i << '\n';
        }
    }

    return heap.topk_result(k);
}
