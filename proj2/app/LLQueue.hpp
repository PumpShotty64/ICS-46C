#ifndef __PROJ2_QUEUE_HPP
#define __PROJ2_QUEUE_HPP

#include "runtimeexcept.hpp"
#include <iostream> 

class QueueEmptyException : public RuntimeException 
{
public:
	QueueEmptyException(const std::string & err) : RuntimeException(err) {}
};


template<typename Object>
class LLQueue
{
private:
	
	struct Node {
		Object value;
		Node * next;
	};

	unsigned count;
	Node * begin;
	Node * end;

public:
	LLQueue();

//	In principle, you should have copy constructors and 
// assignment operators implemented.
// I am not going to require it for this assignment.
	// LLQueue(const LLQueue & st);
	// LLQueue & operator=(const LLQueue & st);

	~LLQueue()
	{
		// You do need to implement the destructor though.
		while (begin != end->next) {
			Node * temp = begin;
			begin = begin->next;
			delete temp;
		}

	}

	size_t size() const noexcept;
	bool isEmpty() const noexcept;

	// We have two front() for the same reason the Stack in lecture week 2 had two top() functions.
	// If you do not know why there are two, your FIRST step needs to be to review your notes from that lecture.

	Object & front();
	const Object & front() const;

	void enqueue(const Object & elem);

// does not return anything.  Just removes. 
	void dequeue();
};

template<typename Object>
LLQueue<Object>::LLQueue()
	: count(0), begin(nullptr), end(nullptr) { // why this can't be curly braces
}

template<typename Object>
size_t LLQueue<Object>::size() const noexcept {
	return count;
}

template<typename Object>
bool LLQueue<Object>::isEmpty() const noexcept {
	return count == 0;
}

template<typename Object>
Object & LLQueue<Object>::front() {
	if ( isEmpty() ) {
		throw QueueEmptyException("Queue is empty!");
	}
	return begin->value;
}

template<typename Object>
const Object & LLQueue<Object>::front() const { // remember to throw exception in this case. 
	if ( isEmpty() ) {
		throw QueueEmptyException("Queue is empty!");
	}
	return begin->value;
}

template<typename Object>
void LLQueue<Object>::enqueue(const Object & elem) {
	if (count == 0) {
		begin = new Node{elem};
		end = begin;
	} else {
		end->next = new Node{elem};
		end = end->next;
	}
	count++;
}

template<typename Object>
void LLQueue<Object>::dequeue() {
	if ( isEmpty() ) {
		throw QueueEmptyException("Queue is empty!");
	}
	Node * temp = begin;
	begin = begin->next;
	delete temp;
	count--;
}

#endif 
