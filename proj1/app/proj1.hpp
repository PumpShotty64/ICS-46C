#ifndef __PROJ_1__HPP
#define __PROJ_1__HPP

#include <map>
#include <stack>
#include <list>
#include <set>

/* 
 * Project 1:  you need to implement this function.
 I promise that any of my test cases will have an empty 
 	map as the fourth parameter when called.
 If the puzzle IS solvable, return true AND make the mapping indicate the solution.
 If the puzzle is NOT solvable, it is enough to return false.

 See the project 1 write-up for a better description. 
 */

int maxSolutions(std::string & s1, std::string & s2, std::string & s3);
bool finalCheck(std::string & s1, std::string & s2, std::string & s3, std::map<char, unsigned> & mapping, std::stack<int> & numStack);
bool checkSolution(std::stack<int> & numStack);
void printMap(std::map<char, unsigned> & mapping);
bool hasMapValue(int value, std::map<char, unsigned> & mapping);
bool hasMapKey(char key, std::map<char, unsigned> & mapping);
void createMap(std::string s1, std::string s2, std::string s3, std::map<char, unsigned> & mapping, std::stack<int> & numStack, std::set<int> & numList, const int max);


bool puzzleSolver(std::string s1, std::string s2, std::string s3, std::map<char, unsigned> & mapping);


#endif