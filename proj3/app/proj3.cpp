#include "proj3.hpp"
#include "Wordset.hpp"
#include <iostream>
#include <set>
#include <sstream>
#include <map>
#include <stack>
#include <queue>

const bool DEBUG = false;

// You should not need to change this function.
void loadWordsIntoTable(WordSet & words, std::istream & in)
{
	std::string line, word;
	std::stringstream ss;

	while(	getline(in, line) )
	{
		ss.clear();
		ss << line;
		while( ss >> word )
		{
			words.insert( word );
		}
	}

}

// print queue
void printQu(std::queue< std::string > qu) {
	std::cout << "QUEUE---------" << std::endl;
	for (unsigned i = 0; i < qu.size(); ++i) {
		std::cout << qu.front() << "\t";
		qu.pop();
	}
	std::cout << "\n-------------" << std::endl;
}

// print map
void printMap(std::map< std::string, std::string > map) {
	for (auto p: map) {
		std::cout << p.first << "--> " << p.second << std::endl;
	}
}

// finds the final path
std::string findPath(std::string & start, std::string & finish, std::map< std::string, std::string > map) {
	std::string pathStr = finish;
	std::stack< std::string > pathStack;
	std::string current = start;
	while (current != finish) {
		pathStack.push(current);
		current = map.at(current);
	}

	while (pathStack.size() != 0) {
		pathStr += " --> " + pathStack.top();
		pathStack.pop();
	}
	return pathStr;
}

std::string convert(std::string s1, std::string s2, const WordSet & words)
{

	// declarations and initializations
	std::string sOrigin = s1;
	std::map< std::string, std::string> wordMap;
	std::queue< std::string > wordQu;
	wordMap.insert( std::pair< std::string, std::string>(s1, ""));
	wordQu.push(s1);

	while (s1 != s2 && wordQu.size() != 0) {


		for (unsigned i = 0; i < s1.size(); ++i) {

			// maintain original string
			std::string tempStr = s1;
				
			for (unsigned j = 0; j < 26; ++j) { // generates word
				char c = j + 'a'; 
				tempStr[i] = c;

				if (DEBUG) std::cout << tempStr << std::endl;

				if ( words.contains(tempStr) && wordMap.count(tempStr) == 0) {
					wordMap.insert( std::pair< std::string, std::string>(tempStr, s1) );
					wordQu.push(tempStr);
				}
			}

		}

		
		wordQu.pop();
		s1 = wordQu.front();

		if (DEBUG) {
			std::cout << "Front value: " << s1 << std::endl;
			std::cout << "Queue Size: " << wordQu.size() << std::endl;
			printQu(wordQu);
			printMap(wordMap);
		}

	}
	if (DEBUG) std::cout << "PATH:" << findPath(s2, sOrigin, wordMap) << std::endl;

	return findPath(s2, sOrigin, wordMap);
}
