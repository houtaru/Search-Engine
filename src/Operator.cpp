#include <Operator.hpp>

vector<int> Operator::_And(Trie &trie, vector<string> query, int k)
{
    return ranking.output(trie, query, 5);
}
vector<int> Operator::_Or(Trie &trie, vector<string> query1, vector<string> query2, int k)
{
    vector<int> result1 = ranking.output(trie, query1, k);
    vector<int> result2 = ranking.output(trie, query2, k);
    result1.insert(result1.end(), result2.begin(), result2.end());
    sort(result1.begin(), result1.end(), greater<int>());
    int _min = min(k, (int)result1.size());
    result1.resize(_min);
    return result1;
}
vector<int> Operator::_Synonym(Trie &trie, string s, int k)
{
    ifstream fin;
    string temp;
    vector<string> synonym;
    vector<int> result;
    fin.open(("Synonym_data/" + s).c_str());
    //if string s doesn't have synonym, return vector 0
    if (!fin.is_open())
    {
        result.push_back(0);
        return result;
    }
    while (!fin.eof())
    {
        getline(fin, temp);
        synonym.push_back(temp);
    }
    for (auto i : synonym)
    {
        vector<string> tempo;
        tempo.push_back(i);
        vector<int> result1 = ranking.output(trie, tempo, k);
        result.insert(result.end(), result1.begin(), result1.end());
        tempo.clear();
        result1.clear();
    }
    sort(result.begin(), result.end(), greater<int>());
    int _min = min(k, (int)result.size());
    result.resize(_min);
    return result;
}
vector<int> Operator::_Minus(Trie &trie, vector<string> query, int k)
{
    return ranking.output(trie, query, 5);
}
vector<int> Operator::_FullyAppear(Trie &trie, vector<string> query, int k)
{
    return ranking.output(trie, query, 5);
}
vector<int> Operator::_range(Trie &trie, string s, int k)
{
    string s1, s2;
    int i;
    for (i = 0; i < s.length(); i++)
        if (s[i] == '.')
            break;
    s1 = s.substr(0, i);
    s2 = s.substr(i + 2, s.length() - 2 - i);
    if (s1[0] == '$')
        s1.erase(0);
    if (s2[0] == '$')
        s2.erase(0);
    vector<string> query;
    vector<int> result;
    int first = stoi(s1), second = stoi(s2);
    for (int i = first; i <= second; ++i)
        query.push_back(to_string(i));
    for (auto i : query)
    {
        vector<string> tempo;
        tempo.push_back(i);
        vector<int> result1 = ranking.output(trie, tempo, k);
        result.insert(result.end(), result1.begin(), result1.end());
        tempo.clear();
        result1.clear();
    }
    sort(result.begin(), result.end(), greater<int>());
    auto last = unique(result.begin(),result.end()) ;
    result.erase(last,result.end())  ;
    int _min = min(k, (int)result.size());
    result.resize(_min);
    return result;
}
