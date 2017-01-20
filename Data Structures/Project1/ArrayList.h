#ifndef ArrayList_H
#define ArrayList_H

#include "List.h"

using namespace std;
typedef unsigned int Index;
template <typename T>

class ArrayList : public List<T> {
	private: 
		Index sizeofArray;
		Index max; 
		T* arr; 
public: 
	ArrayList() {
		max = 5;
		sizeofArray = 0;
		arr = new T[max];
	}
	//copy constructor
	ArrayList(ArrayList& copyArray) {
		this->sizeofArray = copyArray.sizeofArray;
		this->max = copyArray.max;
		this->arr = copyArray.arr; 
	}

	//Overloaded constructor
	ArrayList(int size) {
		max = size * 1.5; 
		sizeofArray = size; 
		arr = new T[max];
	}

	~ArrayList() {
		Clear();
	}

	//returns a new array with both elements from both arrays
	friend ArrayList operator+(const ArrayList& rhs) {
		newMax = this->max + rhs.max;
		newArray = new T[newMax];
		for (Index i = 0; i < this->sizeofArray; i++)
			newArray[i] = this->arr[i];
		for (Index i = 0; i < rhs.sizeofArray; i++)
			newArray[i+rhs.max] = rhs.arr[i];
		return newArray;
	}

	ArrayList operator=(const ArrayList& rhs) {
		this->sizeofArray = rhs.sizeofArray;
		this->max = rhs.max;
		this->arr = rhs.arr;
		for (Index i = 0; i < this->sizeofArray; i++)
			this->arr[i] = rhs.arr[i];
	}

	virtual void Add(const T& ele) {
		if (sizeofArray == max)
			Resize(); 
		arr[sizeofArray] = ele; 
		sizeofArray++; 
	}

	void Resize() {
		max = max * 2; 
		if (max == 0)
			max = 10;
		T* temp = new T[max];
		for (Index i = 0; i < sizeofArray; i++)
			temp[i] = arr[i]; 
		delete [] arr; 
		arr = temp; 
	}

	virtual void Set(Index i, const T& val) {
		if (sizeofArray <= i || i < 0)
			throw List<T>::BAD_INDX;
		arr[i] = val; 
	}

	virtual void Remove(Index i) {
		if (sizeofArray <= i || i < 0)
			throw List<T>::BAD_INDX;
		for (Index j = i + 1; j < sizeofArray; ++j)
			arr[j - 1] = arr[j];
		sizeofArray--; 
	}

	virtual void Clear() {
		delete[] arr; 
		max = sizeofArray = 0; 
	}

	virtual T& Get(Index i) const {
		if (sizeofArray <= i || i < 0)
			throw List<T>::BAD_INDX;
		return arr[i];
	}

	virtual unsigned int Size() const {
		return sizeofArray;
	}

};

#endif