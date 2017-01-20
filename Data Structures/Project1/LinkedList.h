/*
Name: Rocio Salguero
Date: Sept 19 2015

Description: Linklist using a front pointer and a end pointer. The add function adds the elements to the end of the list. 
*/

#ifndef LinkedList_H
#define LinkedList_H

#include "List.h"
#include <cmath>

using namespace std;
typedef unsigned int Index;
template <typename T>


class LinkedList : public List<T> {
private:
	class Node {
	public: 
		Node(Node* p, T i, Node* n) {
			prevLink = p;
			item = i; 
			nextLink = n;
		}
		Node* prevLink;
		T item; 
		Node* nextLink; 
	};

	Node* firstElement; 
	Node* lastElement; 
	Index arraySize; //number of elements in the array

public:
	LinkedList() : arraySize(0), firstElement(NULL), lastElement(NULL) {}
	//Copy constructor 
	LinkedList(LinkedList& copy) {
		Node* ptrIndex = this->firstElement;
		for (int i = 0; i < this->arraySize; i++) {
			copy.Add(ptrIndex.item);
			ptrIndex = ptrIndex->nextLink;
		}
	}
	//Deconstructor
	~LinkedList() {
		Clear();
	}
	//Returns a new LinkList with both other lists combined
	friend LinkedList operator+(const LinkedList& rhs) {
		LinkedList<T> lst1;
		Node* ptrIndex = this->firstElement;
		for (int i = 0; i < this->arraySize; i++) {
			lst1.Add(ptrIndex.item);
			ptrIndex = ptrIndex->nextLink;
		}
		ptrIndex = rhs.firstElement;
		for (int i = 0; i < rhs.arraySize; i++) {
			lst1.Add(ptrIndex.item);
			ptrIndex = ptrIndex->nextLink;
		}
		return lst1;
	}
	//Adds to the end of the list 
	virtual void Add(const T& ele) {
		if (arraySize == 0) {
			Node * newNode = new Node(NULL, ele, NULL);
			firstElement = newNode;
		}
		else if (arraySize == 1) {
			Node * newNode = new Node(firstElement, ele, NULL);
			firstElement->nextLink = newNode;
			lastElement = newNode;
		}
		else {
			Node * newNode = new Node(lastElement, ele, NULL);
			lastElement->nextLink = newNode;
			lastElement = newNode;
		}		
		arraySize++;
	}

	//Traverses the array either from the begining or from the end depending on the index
	virtual void Set(Index i, const T& val) {
		if (arraySize <= i || i < 0)
			throw List<T>::BAD_INDX;
		Index middleIndex = ceil(arraySize / 2);
		Node * ptrIndex;
		if (i <= middleIndex) {
			ptrIndex = firstElement;
			for (Index j = 0; j < i; ++j) {
				ptrIndex = ptrIndex->nextLink;
			}
		}
		else {
			ptrIndex = lastElement;
			for (Index j = 0; j < (arraySize - i - 1); ++j) {
				ptrIndex = ptrIndex->prevLink;
			}
		}
		ptrIndex->item = val; //set indexed item as value
	}

	//traverses array then stops at element before index then reassigns pointers and deletes index Node
	virtual void Remove(Index i) {
		if (arraySize <= i || i < 0)
			throw List<T>::BAD_INDX;
		Index middleIndex = ceil(arraySize / 2);
		Node * ptrIndex;

		if (i == 0) { //if first element
			ptrIndex = firstElement;
			if (arraySize == 1) {
				delete ptrIndex;
				firstElement = NULL;
			}
			else {
				firstElement = firstElement->nextLink;
				firstElement->prevLink = NULL;
				delete ptrIndex;
			}
		}
		else if (i == (arraySize-1)) { //if last element
			ptrIndex = lastElement;
			lastElement = lastElement->prevLink;
			lastElement->nextLink = NULL;
			delete ptrIndex;
		}
		else if (i < middleIndex) { //traverses same as Set()
			ptrIndex = firstElement;
			for (Index j = 0; j < (i-1); ++j) {
				ptrIndex = ptrIndex->nextLink;
			}
			Node * oldNode = ptrIndex->nextLink; 
			Node * nextNode = oldNode->nextLink;
			ptrIndex->nextLink = oldNode->nextLink;
			nextNode->prevLink = oldNode->prevLink;
			delete oldNode; 
		}
		else {
			ptrIndex = lastElement;
			for (Index j = 0; j < (arraySize - i - 2); ++j) {
				ptrIndex = ptrIndex->prevLink;
			}
			Node * oldNode = ptrIndex->prevLink;
			Node * nextNode = oldNode->prevLink;
			ptrIndex->prevLink = oldNode->prevLink;
			nextNode->nextLink = oldNode->nextLink;
			delete oldNode;
		}

		arraySize--;
	}

	virtual void Clear() {
		while (Size() > 0) {
			Remove(0);
		}
	}

	//traverses same as Set()
	virtual T& Get(Index i) const {
		if (arraySize <= i || i < 0)
			throw List<T>::BAD_INDX;
		Index middleIndex = ceil(arraySize / 2);
		Node * ptrIndex;
		if (i <= middleIndex) {
			ptrIndex = firstElement;
			for (Index j = 0; j < i; ++j) {
				ptrIndex = ptrIndex->nextLink;
			}
		}
		else {
			ptrIndex = lastElement;
			for (Index j = 0; j < (arraySize-i-1); ++j) {
				ptrIndex = ptrIndex->prevLink;
			}
		}
		return ptrIndex->item;
	}

	virtual unsigned int Size() const {
		return arraySize;
	}

};

#endif