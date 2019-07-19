#include <Trie.hpp>
#include <Heap.hpp>
#include <Ranking.hpp>
#include <utils.h>


int main() {
    Trie trie(256);
    for (int i = 0; i < 3; ++i) {
        ifstream fin("Data/" + to_string(i) + ".txt");
        vector<string> ss;
        string sub;
        while (fin >> sub)
            ss.push_back(sub);

        trie.AddText(i, ss);
        fin.close();
    }

    string query_init;
    getline(cin, query_init);
    vector<string> query = tokenizer(query_init);


    cout << endl;
    Ranking ranking;
    for (auto i : ranking.output(trie, query, 3))
        cout << i << endl;


    return 0;
}