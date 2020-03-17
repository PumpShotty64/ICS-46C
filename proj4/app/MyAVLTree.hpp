#ifndef __PROJ_THREE_AVL_HPP
#define __PROJ_THREE_AVL_HPP

#include "runtimeexcept.hpp"
#include <string>
#include <vector>
#include <iostream>

const bool DEBUG = false;


class ElementNotFoundException : public RuntimeException 
{
public:
	ElementNotFoundException(const std::string & err) : RuntimeException(err) {}
};


template<typename Key, typename Value>
class MyAVLTree
{
private:
	// fill in private member data here
	// If you need to declare private functions, do so here too.

	// variable declarations and initialization
	struct Node {
		Key key;
		Value value;
		int balanceFactor = 0;
		unsigned lheight = 0;
		unsigned rheight = 0;
		Node * lnext = nullptr;
		Node * rnext = nullptr;
	};

	unsigned count = 0;
	Node * root;

	// function declaration
	void deleteTree(Node * parent);
	void updateBalanceFactor(Node * parent);
	void findPivot(Node * parent);
	void printOrder(std::vector<Key> & orderedVect) const;
	void inOrderTraversal(Node * parent, std::vector<Key> & orderedVect) const;
	void preOrderTraversal(Node * parent, std::vector<Key> & orderedVect) const;
	void postOrderTraversal(Node * parent, std::vector<Key> & orderedVect) const;
	void printTree(Node * parent, unsigned layer);

public:
	MyAVLTree();

	// In general, a copy constructor and assignment operator
	// are good things to have.
	// For this quarter, I am not requiring these. 
	//	MyAVLTree(const MyAVLTree & st);
	//	MyAVLTree & operator=(const MyAVLTree & st);


	// The destructor is, however, required. 
	~MyAVLTree()
	{
		deleteTree(root);
	}

	// size() returns the number of distinct keys in the tree.
	size_t size() const noexcept;

	// isEmpty() returns true if and only if the tree has no values in it. 
	bool isEmpty() const noexcept;

	// contains() returns true if and only if there
	//  is a (key, value) pair in the tree
	//	that has the given key as its key.
	bool contains(const Key & k) const; 

	// find returns the value associated with the given key
	// If !contains(k), this will throw an ElementNotFoundException
	// There needs to be a version for const and non-const MyAVLTrees.
	Value & find(const Key & k);
	const Value & find(const Key & k) const;

	// Inserts the given key-value pair into 
	// the tree and performs the AVL re-balance
	// operation, as described in lecture. 
	// If the key already exists in the tree, 
	// you may do as you please (no test cases in
	// the grading script will deal with this situation)
	void insert(const Key & k, const Value & v);

	// in general, a "remove" function would be here
	// It's a little trickier with an AVL tree
	// and I am not requiring it for this quarter's ICS 46.
	// You should still read about the remove operation
	// in your textbook. 

	// The following three functions all return
	// the set of keys in the tree as a standard vector.
	// Each returns them in a different order.
	std::vector<Key> inOrder() const;
	std::vector<Key> preOrder() const;
	std::vector<Key> postOrder() const;

};


template<typename Key, typename Value>
MyAVLTree<Key,Value>::MyAVLTree()
	: root{nullptr}
{
}

template<typename Key, typename Value>
size_t MyAVLTree<Key, Value>::size() const noexcept
{
	return count;
}

template<typename Key, typename Value>
bool MyAVLTree<Key, Value>::isEmpty() const noexcept
{
	return count == 0; 
}


template<typename Key, typename Value>
bool MyAVLTree<Key, Value>::contains(const Key &k) const
{
	// start at root and binary search
	Node * current = root;
	while (current != nullptr) {
		if (k == current->key) {
			return true;
		} else if (k > current->key) { // right
			current = current->rnext;
		} else if (k < current->key) { // left
			current = current->lnext;
		}
	}
	return false;
}



template<typename Key, typename Value>
Value & MyAVLTree<Key, Value>::find(const Key & k)
{
	// start at root and binary search
	Node * current = root;
	while (current != nullptr) {
		if (k == current->key) {
			return current->value;
		} else if (k > current->key) { // right
			current = current->rnext;
		} else if (k < current->key) { // left
			current = current->lnext;
		}
	}
	throw ElementNotFoundException("Element not found!");
}

template<typename Key, typename Value>
const Value & MyAVLTree<Key, Value>::find(const Key & k) const
{
	// start at root and binary search
	Node * current = root;
	while (current != nullptr) {
		if (k == current->key) {
			return current->value;
		} else if (k > current->key) { // right
			current = current->rnext;
		} else if (k < current->key) { // left
			current = current->lnext;
		}
	}
	throw ElementNotFoundException("Element not found!");
}

template<typename Key, typename Value>
void MyAVLTree<Key, Value>::insert(const Key & k, const Value & v)
{
	
	// initial condition
	if (root == nullptr) {
		root = new Node{k, v};
		count++;
	} 

	Node * current = root;

	while (true) {

		if (k == current->key) {
			current->value = v; // update to new value
			break;
		}

		if (k > current->key) { // right
			if (current->rnext == nullptr) {
				current->rnext = new Node{k, v};
				count++;
				break;
			}
			current = current->rnext;
			
		} else if (k < current->key) { // left
			if (current->lnext == nullptr) {
				current->lnext = new Node{k, v};
				count++;
				break;
			}
			current = current->lnext;
		}
	}

	// update balance factor
	updateBalanceFactor(root);
	
	
	// find pivot
	try {
		findPivot(root);
	} catch (Node * pivot){
		Node * prev = nullptr;
		Node * child0 = nullptr;
		Node * child1 = nullptr;

		// find pointer that points to the pivot
		Node * current = root;
		while (current->key != pivot->key) {
			prev = current;
			if (pivot->key > current->key) current = current->rnext;
			else if (pivot->key < current->key) current = current->lnext;
		}

		// find nodes that need to be rearranged
		if (pivot->balanceFactor > 0) child0 = pivot->lnext;
		else child0 = pivot ->rnext;
		if (child0->balanceFactor > 0) child1 = child0->lnext;
		else child1 = child0->rnext;

		if (DEBUG && prev != nullptr) std::cout << "\t\tPrev: " << prev->key << " Pivot: " << pivot->key << " Mid: " << child0->key << " Bot: " << child1->key << std::endl;
		else if (DEBUG) std::cout << "\t\tPivot: " << pivot->key << " Mid: " << child0->key << " Bot: " << child1->key << std::endl;

		// 4 possible conditions,  update map.
		if (child1->key > child0->key && child1->key > pivot->key) { // RR - L tranformation
			if (prev != nullptr) {
				if (prev->key < pivot->key) prev->rnext = child0;
				else prev->lnext = child0;
				pivot->rnext = child0->lnext;;
				child0->lnext = pivot;
			} else {
				root = child0;
				pivot->rnext = child0->lnext;
				child0->lnext = pivot;
			}
		} else if (child1->key < child0->key && child1->key > pivot->key) { // RL - RL transformation
			if (prev != nullptr) {
				if (prev->key < pivot->key) prev->rnext = child1;
				else prev->lnext = child1;
				child0->lnext = child1->rnext;
				pivot->rnext = child1->lnext;
				child1->lnext = pivot;
				child1->rnext = child0;
			} else {
				root = child1;
				pivot->rnext = child1->lnext;
				child0->lnext = child1->rnext;
				child1->lnext = pivot;
				child1->rnext = child0;
			}
		} else if (child1->key < child0->key && child1->key < pivot->key) { // LL - R transformation
			if (prev != nullptr) {
				if (prev->key < pivot->key ) prev->rnext = child0;
				else prev->lnext = child0;
				pivot->lnext = child0->rnext;
				child0->rnext = pivot;
			} else {
				pivot->lnext = child0->rnext;
				root = child0;
				child0->rnext = pivot;
			}
		} else if (child1->key > child0->key && child1->key < pivot->key) { // LR - LR transformation
			if (prev != nullptr) {
				if (prev->key < pivot->key) prev->rnext = child1;
				else prev->lnext = child1;
				child0->rnext = child1->lnext;
				pivot->lnext = child1->rnext;
				child1->lnext = child0;
				child1->rnext = pivot;
			} else {
				root = child1;
				pivot->lnext = child1->rnext;
				child0->rnext = child1->lnext;
				child1->rnext = pivot;
				child1->lnext = child0;
			}
		}
		std::cout << "--------" << std::endl;
		printTree(root, 0);
		std::cout << "--------" << std::endl;
		if (DEBUG) updateBalanceFactor(root);
	}

	if (DEBUG) std::cout << "--------------" << std::endl;
}

// tree orderings
template<typename Key, typename Value>
std::vector<Key> MyAVLTree<Key, Value>::inOrder() const
{
	std::vector<Key> orderedVect;
	inOrderTraversal(root, orderedVect);
	if (DEBUG) printOrder(orderedVect);
	return orderedVect; 
}


template<typename Key, typename Value>
std::vector<Key> MyAVLTree<Key, Value>::preOrder() const
{
	std::vector<Key> orderedVect;
	preOrderTraversal(root, orderedVect);
	if (DEBUG) printOrder(orderedVect);
	return orderedVect; 
}


template<typename Key, typename Value>
std::vector<Key> MyAVLTree<Key, Value>::postOrder() const
{
	std::vector<Key> orderedVect;
	postOrderTraversal(root, orderedVect);
	if (DEBUG) printOrder(orderedVect);
	return orderedVect; 
}

template<typename Key, typename Value>
void MyAVLTree<Key, Value>::deleteTree(Node * parent) {
	if (parent != nullptr) {
		if (parent->lnext != nullptr) deleteTree(parent->lnext);
		if (parent->rnext != nullptr) deleteTree(parent->rnext);
		delete parent;
	}
}

template<typename Key, typename Value>
void MyAVLTree<Key, Value>::updateBalanceFactor(Node * parent) {
	
	if (parent != nullptr) {
		parent->lheight = 0;
		parent->rheight = 0;

		// iterate through tree
		if (parent->lnext != nullptr) {
			parent->lheight++;
			updateBalanceFactor(parent->lnext);
		}
		if (parent->rnext != nullptr) {
			parent->rheight++;
			updateBalanceFactor(parent->rnext);
		}

		// finding max value for left
		if (parent->lnext != nullptr) {
			if (parent->lnext->lheight > parent->lnext->rheight) {
				parent->lheight += parent->lnext->lheight;
			} else {
				parent->lheight += parent->lnext->rheight;
			}
		}
		// finding max value for right
		if (parent->rnext != nullptr) {
			if (parent->rnext->lheight > parent->rnext->rheight) {
				parent->rheight += parent->rnext->lheight;
			} else {
				parent->rheight += parent->rnext->rheight;
			}
		}
		

		parent->balanceFactor = parent->lheight - parent->rheight;

		if (DEBUG) std::cout << "Key: " << parent->key << " | Lheight: " << parent->lheight << " | Rheight: " << parent->rheight << " | Factor: " << parent->balanceFactor << std::endl;
	}	
}

template<typename Key, typename Value>
void MyAVLTree<Key, Value>::findPivot(Node * parent) {
	if (parent != nullptr) {
		if (parent->lnext != nullptr) findPivot(parent->lnext);
		if (parent->rnext != nullptr) findPivot(parent->rnext);
		if (parent->balanceFactor < -1 || parent->balanceFactor > 1) {
			throw parent;
		}
	}
}

template<typename Key, typename Value>
void MyAVLTree<Key, Value>::inOrderTraversal(Node * parent, std::vector<Key> & orderedVect) const {
	if (parent != nullptr) {
		if (parent->lnext != nullptr) inOrderTraversal(parent->lnext, orderedVect);
		orderedVect.push_back(parent->key);
		if (parent->rnext != nullptr) inOrderTraversal(parent->rnext, orderedVect);
	}
}

template<typename Key, typename Value>
void MyAVLTree<Key, Value>::preOrderTraversal(Node * parent, std::vector<Key> & orderedVect) const {
	if (parent != nullptr) {
		orderedVect.push_back(parent->key);
		if (parent->lnext != nullptr) preOrderTraversal(parent->lnext, orderedVect);
		if (parent->rnext != nullptr) preOrderTraversal(parent->rnext, orderedVect);
	}
}

template<typename Key, typename Value>
void MyAVLTree<Key, Value>::postOrderTraversal(Node * parent, std::vector<Key> & orderedVect) const {
	if (parent != nullptr) {
		if (parent->lnext != nullptr) postOrderTraversal(parent->lnext, orderedVect);
		if (parent->rnext != nullptr) postOrderTraversal(parent->rnext, orderedVect);
		orderedVect.push_back(parent->key);
	}
}

template<typename Key, typename Value>
void MyAVLTree<Key, Value>::printOrder(std::vector<Key> & orderedVector) const {
	for(Key i: orderedVector) {
		std::cout << i << " ";
	}
	std::cout << std::endl;
}

template<typename Key, typename Value>
void MyAVLTree<Key, Value>::printTree(Node * parent, unsigned layer) {
	std::string a = "";
	for (unsigned i = 0; i < layer; ++i) {
		a += "   ";
	}
	if (parent != nullptr) {
		if (parent->rnext != nullptr) printTree(parent->rnext, layer + 1);
		std::cout << a << parent->key << std::endl;
		if (parent->lnext != nullptr) printTree(parent->lnext, layer + 1);
	}
}




#endif 