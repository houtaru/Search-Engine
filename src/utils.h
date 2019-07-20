#ifndef UTILS_H_DEFINED
#define UTILS_H_DEFINED

#include <string>
#include <vector>
#include <iostream>
#include <boost/algorithm/string.hpp>

std::vector < std::string > tokenizer(std::string s, int flag = 0);
void delete_char(std:: string &s) ;
void preprocess_data(std::vector <std::string> &k) ; 


#endif