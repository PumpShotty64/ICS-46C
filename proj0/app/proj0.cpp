#include <map>
#include <string>
#include "proj0.hpp"
#include <iostream>

unsigned int carry = 0;

bool verifySolution(std::string s1, std::string s2, std::string s3, const std::map<char, unsigned> & mapping)
{

    if (s1.length() == 0) {
        return true;
    } else {

        unsigned int index = s1.length() - 1;

        // adding
        int sum = mapping.at(s1[index]) + mapping.at(s2[index]);
        if (carry == 1) {
            sum++;
            carry--;
        }

        // carry
        if (sum >= 10) {
            carry++;
            sum -= 10;
        }

        // checking
        if (sum == mapping.at(s3[index])) {
            s1.pop_back();
            s2.pop_back();
            s3.pop_back();
            return verifySolution(s1, s2, s3, mapping);
        }
    }

    return false;
}





