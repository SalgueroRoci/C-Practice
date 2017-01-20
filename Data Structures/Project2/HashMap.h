#ifndef HASHMAP_H
#define HASHMAP_H
#include <cstdlib>
#include "Map.h"
typedef unsigned int Index;

/**
 * A map implementation that uses a  hash table
 * with a multiplicative hash function internally. 
 */
template <typename T1, typename T2>
class HashMap : public Map<T1, T2>
{

public:
	HashMap()
	{
		max = DEF_CAPC;
		arr = new KeyValue[DEF_CAPC];
		n = 0;
		a = 2; b = 1;
	}


	HashMap(unsigned int capc)
	{
		max = capc;
		arr = new KeyValue[max];
		n = 0;
		a = 2; b = 1;
	}

	//Copy constructor
	HashMap(const HashMap& hm)
	{
		n = 0;  max = hm.max; 
		arr = new KeyValue[max];
		a = hm.a; b = hm.b; rehashCount = 0;

		//copies all the values
		for (int i = 0; i < max; i++) {
			if (!arr[i].open)  //If there is an item there then add 
				Put(hm.arr[i].key, hm.arr[i].val);
		}
	
	}

	//Desctructor 
	virtual ~HashMap()
	{
		delete[] arr; //deletes array
		n = 0;
		max = 0;
	}

	HashMap& operator=(const HashMap& rhs)
	{
		if (this == &rhs)
			return *this;
		delete[] arr; n = 0; max = rhs.max;  //reset number count, and arr array; set max to be the same
		a = rhs.a; b = rhs.b; //set the random variables to be the same for hashfunction

		//copies all the values
		arr = new KeyValue[max];
		for (int i = 0; i < rhs.max; i++) {
			if (!rhs.arr[i].open) //If there is an item there then add 
				Put(rhs.arr[i].key, rhs.arr[i].val);
		}
		return *this;
	}

	virtual void Erase(const T1& k)
	{
		int index = F(k);
		int i = index;
		
		while (true) {
			if (arr[i].open) {
				throw ELE_DNE;
				break;
			}
			else if (arr[i].key == k) {
				arr[i].open = true;
				n--;
				Rehash(max);
				break;
			}

			i = (i + 1) % max;
			if (i == index) //searched thru all the array and DNE
				throw ELE_DNE;
		}
	
	}

	virtual T2& Find(const T1& k) const
	{
		int index = F(k);
		int i = index; 

		while (true) {
			if (arr[i].open)
				throw ELE_DNE;
			else if (arr[i].key == k)
				return arr[i].val; 

			i = (i + 1) % max; 
			if (i == index) //searched thru all the array
				throw ELE_DNE;
		}
	}


	virtual void Put(const T1& k, const T2& v)
	{
		//resizes if load factor exceeds 50% 
		if ( (double)(n+1) / max >= 0.5) 
			Rehash(max * 2);

		//makes a new keyvalue pair
		KeyValue newPair;
		newPair.key = k; newPair.val = v;
		Index i = F(k);

		while (true) {
			if (arr[i].open) { //checks if open
				arr[i] = newPair;
				arr[i].open = false; //marks space as closed. 
				n++; //increase size by one
				break;
			}
			i = (i + 1) % max; //loops around the array
		}
	}

	virtual unsigned int Size() const
	{
		return n; //Size of array
	}

	class KeyValue
	{
	public:
		KeyValue()
		{
			open = true;
		}

		T1 key;
		T2 val;
		bool open;
	};

	private:
		//private data members
		Index n, max, a, b;
		KeyValue * arr;

		//Default capacity of the underlying array
		const static int DEF_CAPC = 10;

		void Rehash(int newCapc) {
			//create a new hash function
			a = rand() % 100 + 1;
			b = rand() % 100 + 1;

			//copy items
			KeyValue* tmp = new KeyValue[n];
			int tmpMax = n; 
			for (int i = 0, j = 0; i < max; i++) {
				if (!arr[i].open) {
					tmp[j].key = arr[i].key;
					tmp[j].val = arr[i].val;
					j++;
				}
			}

			//Delete and remake array
			delete[] arr; 
			n = 0; max = newCapc; 
			arr = new KeyValue[max];

			//copy all the values and delete tmp array
			for (int i = 0; i < tmpMax; i++) {
				Put(tmp[i].key, tmp[i].val);
			}
			delete[] tmp;
			
		}

		Index F(const T1& ele) const {
			return (a * ele + b) % max;
		}

};
#endif