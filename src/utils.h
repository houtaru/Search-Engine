#ifndef UTILS_H_DEFINED
#define UTILS_H_DEFINED

#include <string>
#include <vector>
#include <iostream>
#include <boost/algorithm/string.hpp>
#include <Engine/Utils/String.hpp>

std::vector < std::string > tokenizer(std::string s, int flag = 0);
std::string Lowercase(std::string st);

#endif