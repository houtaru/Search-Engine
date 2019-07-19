#include <Engine/Utils/String.hpp>

#include <iostream>

using namespace std;

int main() {
    string s; std::getline(std::cin, s);
    std::vector < std::string > cur = String::split(s, ' ', 0);
    for (auto it : cur)
        std::cout << it << "\n";
    return 0;
}