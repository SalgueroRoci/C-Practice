#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include "List.h"
#include "ArrayList.h"
#include "LinkedList.h"
#define LST_SIZE 20000
#define SPACING 1000
using namespace std;

/**
 * Testing the add function
 * @param numTrials The number of trials to perform
 * @param lst Is the list to test
 */
template <typename T>
void AddTest(unsigned int numTrials, List<T>& lst);

/**
 * Compares two list implementations to help ensure
 * they function identically
 * @param The number of trials
 * @param The first list
 * @param The second list
 * @return Pass or fail
 */
template <typename T>
bool CompareLists(unsigned int numTrials, List<T>& lst1, List<T>& lst2);

/**
 * Testing the get function
 * @param numTrials The number of trials to perform
 * @param lst Is the list to test
 */
template <typename T>
void GetTest(unsigned int numTrials, List<T>& lst);

/**
 * Testing the remove function
 * @param numTrials The number of trials to perform
 * Note: numTrials must be <= lst.Size()
 * @param lst Is the list to test
 */
template <typename T>
void RemoveTest(unsigned int numTrials, List<T>& lst);

/**
 * Run a timed test on a list
 * @param tst Pointer to test function to call
 * @param numTrials is the number of trials to perform
 * @param lst The list to test
 * @return The time elapsed in seconds
 */
template <typename T>
long double RunTest(void (*tst)(unsigned int, List<T>&), unsigned int numTrials, List<T>& lst);

/**
 * Testing the set function
 * @param numTrials The number of trials to perform
 * Note: numTrials must be <= lst.Size()
 * @param lst Is the list to test
 */
template <typename T>
void SetTest(unsigned int numTrials, List<T>& lst);

int main()
{	//Test list implementations
	LinkedList<int> lst1 = LinkedList<int>();
	ArrayList<int> lst2 = ArrayList<int>();
	if(CompareLists(LST_SIZE, lst1, lst2))
		cout << "All tests passed. Creating results...\n" << endl;
	else
	{	//Test fails; don't print results
		cout << "At least one test failed!\n" << endl;
		exit(1);
	}
	//Create the output CSV file
	ofstream csvFile;
	csvFile.open("al-out.csv");
	//Run tests on the ArrayList type
	ArrayList<int> arrLst = ArrayList<int>(LST_SIZE);
	for(unsigned int i = 1; i <= LST_SIZE; i += SPACING)
	{	//Run each test and append the results to the CSV file
		csvFile << i << ",";
		csvFile << RunTest(AddTest<int>, i, arrLst) << ",";
		csvFile << RunTest(GetTest<int>, i, arrLst) << ",";
		csvFile << RunTest(SetTest<int>, i, arrLst) << ",";
		csvFile << RunTest(RemoveTest<int>, i, arrLst) << "\n";
	}
	csvFile.close();
	csvFile.open("ll-out.csv");
	//Run tests on the LinkedList type
	LinkedList<int> lnkLst = LinkedList<int>();
	for(unsigned int i = 1; i <= LST_SIZE; i += SPACING)
	{	//Run each test and append the results to the CSV file
		csvFile << i << ",";
		csvFile << RunTest(AddTest<int>, i, lnkLst) << ",";
		csvFile << RunTest(GetTest<int>, i, lnkLst) << ",";
		csvFile << RunTest(SetTest<int>, i, lnkLst) << ",";
		csvFile << RunTest(RemoveTest<int>, i, lnkLst) << "\n";
	}
	csvFile.close();
	return 0;
}

template <typename T>
void AddTest(unsigned int size, List<T>& lst)
{	//Fill the list with random values
	for(unsigned int i = 0; i < size; ++i)
		lst.Add(T(rand()));
}

template <typename T>
bool CompareLists(unsigned int numTrials, List<T>& lst1, List<T>& lst2)
{	//Start by adding random values to the list
	for(int i = 0; i < numTrials; ++i)
	{
		int val = rand();
		lst1.Add(val);
		lst2.Add(val);
	}
	for(int i = 0; i < numTrials; ++i)
	{	//Test the lists by removing, setting, and getting elements
		unsigned int indx = rand() % lst1.Size();
		T val = T(rand());
		try
		{
			lst1.Set(indx, val);
			lst2.Set(indx, val);
			//Elements should always be equal
			if(lst1.Get(indx) != lst2.Get(indx))
				return false;
			lst1.Remove(indx);
			lst2.Remove(indx);
		}
		catch(int errCode)
		{	//Exception occurred; test failed
			if(errCode == List<T>::BAD_INDX)
			{	
				cout << "Error: Index out of bounds\n";
			}
			return false;
		}
		
	}
	//Passed
	return true;
}

template <typename T>
void GetTest(unsigned int numTrials, List<T>& lst)
{	//Get values at random indices
	unsigned int size = lst.Size();
	for(unsigned int i = 0; i < numTrials; ++i)
		lst.Get(rand() % size);
}

template <typename T>
void RemoveTest(unsigned int numTrials, List<T>& lst)
{	//Remove the random values from the list
	for(unsigned int i = 0; i < numTrials; ++i)
		lst.Remove(rand() % lst.Size());	
}

template <typename T>
void SetTest(unsigned int numTrials, List<T>& lst)
{	//Set random indices of the list to random values
	unsigned int size = lst.Size();
	for(unsigned int i = 0; i < numTrials; ++i)
		lst.Set(rand() % size, T(rand()));
}

template <typename T>
long double RunTest(void (*tst)(unsigned int, List<T>&), unsigned int numTrials, List<T>& lst)
{	//Start time and run tests
	clock_t strt, end;
	strt = clock();
	try
	{
		tst(numTrials, lst);
	}
	catch(int errCode)
	{
		if(errCode == List<T>::BAD_INDX)
		{
			cout << "Error: Index out of bounds\n";
			exit(1);
		}
	}
	end = clock();
	return 1000.0 * ((end - strt) / ((long double) numTrials * CLOCKS_PER_SEC));
}
