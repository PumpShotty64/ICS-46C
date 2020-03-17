#include "proj1.hpp"
#include <map>
#include <string>
#include <iostream>
#include <stack>
#include <list>
#include <set>

// possible solution size of map
int maxSolutions(std::string & s1, std::string & s2, std::string & s3) {
	std::set<char> keys;
	for (unsigned int i = 0; i < s1.size(); ++i) {
		keys.insert(s1[i]);
	}
	for (unsigned int i = 0; i < s2.size(); ++i) {
		keys.insert(s2[i]);
	}
	for (unsigned int i = 0; i < s3.size(); ++i) {
		keys.insert(s3[i]);
	}
	return keys.size();
}

// checks the remainder of the word sum once mapping is complete
bool finalCheck(std::string & s1, std::string & s2, std::string & s3, std::map<char, unsigned> & mapping, std::stack<int> & numStack) {
	if (s1.size() == 0 && s2.size() == 0 && s3.size() == 0 && numStack.empty()) { 
		return true;
	} else {
		if (s1.size() != 0) numStack.push(mapping.at(s1.back()));
		if (s2.size() != 0) numStack.push(mapping.at(s2.back()));
		if (s3.size() != 0) numStack.push(mapping.at(s3.back()));
		
		if (checkSolution(numStack)) {
			s1.pop_back();
			s2.pop_back();
			s3.pop_back();
			return finalCheck(s1, s2, s3, mapping, numStack);
		} else {
			return false;
		}
	}
}

// checks if value exists in map
bool hasMapValue(int value, std::map<char, unsigned> & mapping) {
	for (const std::pair<char, unsigned>& k: mapping) {
		if (k.second == value) {
			return true;
		}
	}
	return false;
}

// checks if key exists in map
bool hasMapKey(char key, std::map<char, unsigned> & mapping) {
	for (const std::pair<char, unsigned>& k: mapping) {
		if (k.first == key) {
			return true;
		}
	}
	return false;
}

// prints the mapping of the characters and integers
void printMap(std::map<char, unsigned> & mapping) {
	for (const std::pair<char, unsigned>& k: mapping) {
		std::cout << k.first << "==> " << k.second << std::endl;
	}
}

// checks the solution by popping values out of stack and adding them together
bool checkSolution(std::stack<int> & numStack) {
	
	bool carry = false;
	int v3 = numStack.top();
	int v1v2 = 0;
	numStack.pop();


	while (numStack.size() != 0) {
		v1v2 += numStack.top();
		numStack.pop();
	}

	if (v1v2 >= 10) {
		v1v2 -= 10;
		carry = true;
	}

	if (v1v2 == v3) {
		if (carry) {
			numStack.push(1);
		}
		return true;
	}
	return false;
}

// might need to return a map object
void createMap(std::string s1, std::string s2, std::string s3, std::map<char, unsigned> & mapping, std::stack<int> & numStack, std::set<int> & numSet, const int max) {

	if (s1.size() == 0 && s2.size() == 0 && s3.size() == 0 && numStack.size() == 0) { 
		throw mapping;	

	} else {

		for (int i : numSet) {
		
			for (int j : numSet){
				
				for (int k : numSet) {

					if (i != j && i != k && j != k) {

						// maintains the original map for repetitive use
						std::map<char, unsigned> newMapping = mapping;
						std::set<int> newSet = numSet;
						std::stack<int> newStack = numStack;
						std::string c1 = s1;
						std::string c2 = s2;
						std::string c3 = s3;

						// maps chars to int
						// translates values and moves into stack
						if (c1.size() != 0) {
							if (!hasMapKey(c1.back(), newMapping)) newMapping.insert({c1.back(), i});
							newStack.push(newMapping.at(c1.back()));
						}
						if (c2.size() != 0) {
							if (!hasMapKey(c2.back(), newMapping)) newMapping.insert({c2.back(), j});
							newStack.push(newMapping.at(c2.back()));
						}
						if (c3.size() != 0) {
							if (!hasMapKey(c3.back(), newMapping)) newMapping.insert({c3.back(), k});
							newStack.push(newMapping.at(c3.back()));
						}

						// checks the solution and if true, recursion
						if (checkSolution(newStack)) {

							// what if value already been used in map
							if (c1.size() != 0) {
								c1.pop_back();
								if (hasMapValue(i, newMapping) && newSet.find(i) != newSet.end()) newSet.erase(i);
							}
							if (c2.size() != 0) {
								c2.pop_back();
								if (hasMapValue(j, newMapping) && newSet.find(j) != newSet.end()) newSet.erase(j);
							}
							if (c3.size() != 0) {
								c3.pop_back();
								if (hasMapValue(k, newMapping) && newSet.find(k) != newSet.end()) newSet.erase(k);
							}

							if (newMapping.size() == max) {
								// check with remaining thing
								if (finalCheck(c1, c2, c3, newMapping, newStack)) {
									throw newMapping;	
								}
							} else {
								createMap(c1, c2, c3, newMapping, newStack, newSet, max);
							}
							
						}

					}

				}
			
			}
			
		}

	}

}



bool puzzleSolver(std::string s1, std::string s2, std::string s3, std::map<char, unsigned> & mapping)
{

	std::stack<int> numStack; // create empty stack for adding purposes
	std::set<int> numSet = {0,1,2,3,4,5,6,7,8,9};
	int maxSize = maxSolutions(s1, s2, s3);

	try {
		createMap(s1, s2, s3, mapping, numStack, numSet, maxSize);
	} catch(std::map<char, unsigned> finalMap) {
		mapping = finalMap; // change
		printMap(mapping);
		return true;
	} 
	return false;
}


