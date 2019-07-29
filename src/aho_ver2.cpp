#include <aho_ver2.hpp>

#define iter(it,c) for (__typeof((c).begin()) it = (c).begin(); it != (c).end(); ++it)

typedef vector<vector<int> > vvi;
map<string,int> Aho::all;

Aho::aho_corasick::aho_corasick(vector<string> keywords) {
    N = keywords.size();
    go = new go_node();
    iter(k, keywords) {
        go_node *cur = go;
        iter(c, *k)
            cur = cur->next.find(*c) != cur->next.end() ? cur->next[*c] :
                (cur->next[*c] = new go_node());
        cur->out = new out_node(*k, cur->out);
    }
    queue<go_node*> q;
    iter(a, go->next) q.push(a->second);
    while (!q.empty()) {
        go_node *r = q.front(); q.pop();
        iter(a, r->next) {
            go_node *s = a->second;
            q.push(s);
            go_node *st = r->fail;
            while (st && st->next.find(a->first) == st->next.end())
                st = st->fail;
            if (!st) st = go;
            s->fail = st->next[a->first];
            if (s->fail) {
                if (!s->out) s->out = s->fail->out;
                else {
                    out_node* out = s->out;
                    while (out->next) out = out->next;
                    out->next = s->fail->out;
                }
            }
        }
    }
}
vector < pair <int, int> >  Aho::aho_corasick::search(string s){
    vvi ress(N);
    vector < pair <int, int> > pos(N, make_pair(-1, -1));
    go_node *cur = go;
    iter(c, s) {
        while (cur && cur->next.find(*c) == cur->next.end())
            cur = cur->fail;
        if (!cur) cur = go;
        cur = cur->next[*c];
        if (!cur) cur = go;
        for (out_node *out = cur->out; out; out = out->next){
            ress[all[out->keyword]].push_back(c-s.begin()-out->keyword.size()+1);
            if (pos[all[out->keyword]].first == -1) pos[all[out->keyword]].first = c-s.begin()-out->keyword.size()+1;
            pos[all[out->keyword]].second = max(pos[all[out->keyword]].second, int(c-s.begin()-out->keyword.size()+1));
        }
    }
    return pos;
}