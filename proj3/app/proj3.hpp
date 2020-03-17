#ifndef ___PROJECT_3_HPP
#define ___PROJECT_3_HPP

#include <string>
#include <map>
#include "Wordset.hpp"

void loadWordsIntoTable(WordSet & words, std::istream & in);
std::string findPath(std::string & start, std::string & finish, std::map< std::string, std::string > map);

std::string convert(std::string s1, std::string s2, const WordSet & words);



#endif
