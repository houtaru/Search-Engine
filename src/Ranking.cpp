#include <Ranking.hpp>

double Ranking::weight_query(Trie &trie, string term, int count, int length_vector) {
    //  Get the number of documents containing term
    map<int, int> df = trie.Search(term);
    int df_term = df.size();

    return (1 + log(count)) * log(3 / df_term) * (1 / length_vector);
}

vector<int> Ranking::output(Trie &trie, vector<string> query, int k) {
    // MAP is the list of distinct terms in query
    map<string, int> MAP;
    for (int i = 0; i < (int)query.size(); ++i) {
        auto it = MAP.find(query[i]);
        if (it != MAP.end())
            ++it->second;
    }

    
    //  Get length of vector q (query)
    double length_vector = 0;
    for (auto i = MAP.begin(); i != MAP.end(); i++) {
        length_vector += i->second * i->second;
    }
    length_vector = sqrt(length_vector);

    //  Compute cosine between vector q (query) and vector d (document) ~ Score of documents
    //  We use ltl (logarithm - idf - length) for vector q and l1l (logarithm - 1 - legnth) for vector d
    vector<double> score(3, 0);
    vector<double> length(3, 0);
    for (auto i = MAP.begin(); i != MAP.end(); i++) {
        double w_tq = weight_query(trie, i->first, i->second, length_vector);

        //  Get the number of documents containing term and number of terms in those documents
        map<int, int> df = trie.Search(i->first);
        for (auto j = df.begin(); j != df.end(); j++) {
            length[j->first] += j->second * j->second * 1.0;

            //  Compute dot producgt of vector q and vector d
            score[j->first] += w_tq * (1 + log(j->second * 1.0));
        }
    }

    //  Divide the score[i] by the length of document i and push it to a Heap
    Heap heap;
    for (int i = 0; i < 3; ++i) {
        length[i] = sqrt(length[i]);
        score[i] /= length[i];
        heap.insert(pair<int, int>(score[i], i));
    }

    return heap.topk_result(k);
}
