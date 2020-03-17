#ifndef __PROJ5_PRIORITY_QUEUE_HPP
#define __PROJ5_PRIORITY_QUEUE_HPP

#include "runtimeexcept.hpp"
#include <vector>
#include <iostream>

class PriorityQueueEmptyException : public RuntimeException 
{
public:
	PriorityQueueEmptyException(const std::string & err) : RuntimeException(err) {}
};

template<typename Object>
class MyPriorityQueue
{
private:
	std::vector<Object> minHeap;

public:

	MyPriorityQueue(); // constructor

 	size_t size() const noexcept;
	bool isEmpty() const noexcept;

	void insert(const Object & elem);


	// Note:  no non-const version of this one.  This is on purpose because
	// the interior contents should not be able to be modified due to the
	// heap property.  This isn't true of all priority queues but 
	// for this project, we will do this.
	// min and extractMin should throw PriorityQueueEmptyException if the queue is empty.
	const Object & min() const; 

	void extractMin(); 

};

template<typename Object>
MyPriorityQueue<Object>::MyPriorityQueue() 
	: minHeap{Object()}
{
}

template<typename Object>
size_t MyPriorityQueue<Object>::size() const noexcept
{
	return minHeap.size() - 1;
}

template<typename Object>
bool MyPriorityQueue<Object>::isEmpty() const noexcept
{
	return minHeap.size() == 1;
}

template<typename Object>
void MyPriorityQueue<Object>::insert(const Object & elem) 
{
	minHeap.push_back(elem);
	unsigned index = minHeap.size() - 1;
	
	// insert at end, swap until heap is fixed
	while (index > 1) {
		if (index % 2 == 0) { 	// even
			if (minHeap[index] < minHeap[index/2]) {
				std::swap(minHeap[index], minHeap[index/2]);
			} else {
				break;
			}
			index = index/2;
		} else { 					// odd
			if (minHeap[index] < minHeap[(index-1)/2]) {
				std::swap(minHeap[index], minHeap[(index-1)/2]);
			} else {
				break;
			}
			index = (index-1)/2;
		}
	}
}

template<typename Object>
const Object & MyPriorityQueue<Object>::min() const
{
	if (isEmpty()) throw PriorityQueueEmptyException("Priority Queue is empty!");
	return minHeap[1];
}

template<typename Object>
void MyPriorityQueue<Object>::extractMin() 
{	
	std::swap(minHeap[1], minHeap.back()); // swap last element with first
	minHeap.pop_back(); // remove last element
	unsigned index = 1;

	// swap until heap is fixed
	while (true) {
		if (index*2 <= minHeap.size()-1 && minHeap[index*2] <= minHeap[index*2+1] && minHeap[index*2] < minHeap[index]) { // even side swap
			std::swap(minHeap[index*2], minHeap[index]);
			index = index*2;
		} else if (index*2+1 <= minHeap.size()-1 && minHeap[index*2] > minHeap[index*2+1] && minHeap[index*2+1] < minHeap[index]) { // odd side swap
			std::swap(minHeap[index*2+1], minHeap[index]);
			index = index*2+1;
		} else {
			break;
		}
	}
}

#endif
