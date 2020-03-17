#include "Wordset.hpp"
#include <string>
#include <iostream> // testing purposes

const int BASE_TO_USE = 37; 
const double LOAD_LIMIT = 0.25;
const bool DEBUG = false;


// returns s, as a number in the given base, mod the given modulus
int hashFunction(std::string s, int base, int mod)
{
	// similar to bit shifting
	unsigned sum = 0;
	for (char c: s) {
		sum = (base * sum + (c - 'a')) % mod;
	}
	return sum;

}

// adds value to set
void addValue(std::string *& arr, std::string s1, unsigned capacity) {
	const unsigned index = hashFunction(s1, BASE_TO_USE, capacity);
	unsigned varInd = index;
	unsigned var = 1;
	while (arr[varInd] != "") { // check collision
		varInd = (index + var * var) % capacity;
		var++;
	}
	arr[varInd] = s1;
}

WordSet::WordSet()
	: count{0}, capInd{0}, cap(SIZES[capInd]), hashArr{new std::string [cap]}
{

}

WordSet::~WordSet()
{
	delete[] hashArr; 
}

void WordSet::insert(std::string s)
{
	if (!contains(s)) {
		if ( (count + 1)/double(cap) > LOAD_LIMIT) {

			std::string * oldHash = hashArr;
			cap = SIZES[++capInd];
			hashArr = new std::string [cap];

			// rehash values
			for (unsigned i = 0; i < SIZES[capInd - 1]; ++i) {
				if (oldHash[i] != "") {
					addValue(hashArr, oldHash[i], cap);
				}
			}

			if (DEBUG) {
				for (unsigned i = 0; i < cap; ++i) {
					std::cout << i << ": " << hashArr[i] << std::endl;
				}
				std::cout << "===========" << std::endl;
			}

			delete[] oldHash;
		}
		addValue(hashArr, s, cap);
		count++;	
	}
}

bool WordSet::contains(std::string s) const
{
	const unsigned index = hashFunction(s, BASE_TO_USE, cap);
	unsigned varInd = index;
	unsigned var = 1;

	while (hashArr[varInd] != "") {
		if (hashArr[varInd] == s) {
			return true;
		}
		varInd = (index + var * var) % cap;
		var++;
	}

	return false; 
}

// return how many distinct strings are in the set
int WordSet::getCount() const
{
	return count;
}

// return how large the underlying array is.
int WordSet::getCapacity() const
{
	return cap;
}
