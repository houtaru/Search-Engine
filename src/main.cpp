#include <Frontend.hpp>

int main() {
    Frontend frontend;
    //frontend.loading_scr();
    
    string ss; getline(cin, ss, '\n');
    for (auto it : String::split(ss)) cout << it << "\n";
    
    return 0;
}