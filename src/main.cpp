#include <bits/stdc++.h>

using namespace std;

int main() {
    ifstream fin("input.in");
    string ss;
    while (getline(fin, ss)) {
        if (ss.empty()) {
            puts("empty");
        } else if (ss.back() == '\n') {
            puts("new line");
        } else {
            puts("not empty");
        }
    }
    return 0;
}