#include "utils.h"
using namespace std;
int main() {
    string s="+-*" ;
    vector<string> k=tokenizer(s,0) ; 
    preprocess_data(k) ; 
    for (auto i :k)
       cout << i <<endl ; 

}
