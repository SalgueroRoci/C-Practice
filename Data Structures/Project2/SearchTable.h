#ifndef SEARCHTABLE_H
#define SEARCHTABLE_H
/**
 * A class that implements the Map.h interface.
 * This implements the Map ADT using a search table
 * T1 is the type of the key T2 is the type of the 
 * value in a (key, value) pair.
 */
template <typename T1, typename T2>
class SearchTable : public Map<T1, T2>
{
public:	 
	
	virtual void Erase(const T1& k) 
	{
		if (n == 0)
			throw ELE_DNE;

		quickSort(0, n-1);
		int index = BinarySearch(k);

		if (index == -1) {
			throw ELE_DNE;
		}
		else {
			arr[index].key = arr[n - 1].key;
			arr[index].value = arr[n - 1].value;
		}
		n--;

	}
	 
	virtual T2& Find(const T1& k) const
	{
		if (n == 0)
			throw ELE_DNE;

		int index = 0;
		index = BinarySearch(k);

		if (index == -1) {
			throw ELE_DNE;
		}

		return arr[index].value; 
	}
	
	virtual void Put(const T1& k, const T2& v)
	{	
		//Check if resize is necessary
		if ((n + 1) == max)
			ResizeArr(max*2);
		arr[n].key = k;
		arr[n].value = v;
		n++;
		quickSort(0, n-1);

	}

	virtual unsigned int Size() const
	{
		return n;
	}

	SearchTable& operator=(const SearchTable& rhs)
	{
		//copy items
		this->Clear();
		for (unsigned int i = 0; i < rhs.Size(); ++i)
			Put(rhs.arr[i].key, rhs.arr[i].value);
		return *this;
	}

	//Default constructor
	SearchTable()
	{
		max = DEF_CAPC;
		arr = new KeyValue[DEF_CAPC];
		n = 0;
	}

	//Copy constructor
	SearchTable(const SearchTable& st)
	{
		n = max = 0;
		arr = NULL;
		if (this.arr == &st.arr)
			return;
		this.Clear();
		for (unsigned int i = 0; i < st.Size(); ++i)
			Add(st.arr[i]);
	}
	
	/**
	* Takes as argument an array of keys and
	* and array of values. Copies of the key value pairs
	* are internally and then sorted. Both arrays
	* must have the same size
	* @param keys The array of keys
	* @param vals The array of values
	* @param numEle The number of key-value pairs
	*/
	SearchTable(const T1* keys, const T2* vals, unsigned int numEle)
	{
		arr = new KeyValue[numEle];
		max = numEle;
		for (int i = 0; i < numEle; i++) {
			Put(keys[i], vals[i]);
		}
	}

	//Virtual destructor
	virtual ~SearchTable()
	{
		delete[] arr;
	}
	
private:
	//Default capacity
	const static int DEF_CAPC = 10;

	class KeyValue
	{	//Make the data members public for easy access
	public:
		KeyValue() {}
		KeyValue(T1 k, T2 v) {
			key = k;
			value = v;
		}
		T1 key;
		T2 value;
	};
	
	int BinarySearch(const T1& k) const
	{
		int s = 0;
		int e = n - 1;
		int mid = -1;
		while (s <= e) {
			mid = s + (e - s) / 2;
			if (k == arr[mid].key)
				return mid;
			else if (k > arr[mid].key)
				s = mid + 1;
			else
				e = mid - 1;
		}
		return -1;
	}
	
//---------sorting algorithm------------------------------------
	void quickSort(int s, int e) {

		int i = s, j = e;
		KeyValue tmp;
		KeyValue pivot = arr[s + (e - s) / 2];

		/* partition */
		while (i <= j) {

			while (arr[i].key < pivot.key)
				i++;

			while (arr[j].key > pivot.key)
				j--;

			//swap
			if (i <= j) {
				tmp = arr[i];
				arr[i] = arr[j];
				arr[j] = tmp;
				i++;
				j--;
			}

		};

		/*------------recursion---------------- */
		if (s < j)
			quickSort(s, j);
		if (i < e)
			quickSort(i, e);
	}
//------sorting algorithm--------------------------	

	void ResizeArr(unsigned int cap)
	{
		max = cap;
		//copy items
		KeyValue* tmp = new KeyValue[n];
		int tmpMax = n;
		for (int i = 0 ; i < tmpMax ; i++) {
				tmp[i].key = arr[i].key;
				tmp[i].value = arr[i].value;
		}

		//Delete and remake array
		delete[] arr;
		n = 0; max = cap;
		arr = new KeyValue[max];

		//copy all the values and delete tmp array
		for (int i = 0; i < tmpMax; i++) {
			Put(tmp[i].key, tmp[i].value);
		}
		delete[] tmp;
	}

	virtual void Clear()
	{
		delete[] arr;
		n = 0;
		max = DEF_CAPC;
		arr = new KeyValue[max];
	}

	//Number of elements in the SearchTable
	unsigned int n;
	//Capacity of arr
	unsigned int max;
	//The underlying array
	KeyValue* arr;
};
#endif