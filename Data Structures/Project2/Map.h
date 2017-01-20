#ifndef MAP_H
#define MAP_H
/**
 * A abstract class defining the interface
 * for the Map class. Two template parameters
 * are used. T1 is the type of the key
 * T2 is the type of the value in a 
 * (key, value) pair.
 * Note: Map contains pure virtual functions
 * and therefore is abstract and cannot be
 * instantiated. Use the subclass ListMap
 * HashMap, TreeMap, or SearchTable instead.
 */
template <typename T1, typename T2>
class Map
{
public:
	//Defines an error code used for throwing
	//integer exceptions
	const static int ELE_DNE = -2468;

	/**
	* Attempts to erase the (key, value) pair
	* with key  = k. The int ELE_DNE is thrown
	* if the key is not in the map
	* @param k Is the key of the pair to erase
	*/
	virtual void Erase(const T1& k) = 0;
	 
	/**
	* Attempts to find the corresponding value
	* for a given key. The int ELE_DNE is thrown
	* if the key is not in the map
	* @param k Is the key to search for
	* @return The value corresponding to k
	*/
	virtual T2& Find(const T1& k) const = 0;
	
	/**
	* Returns the number of elements in the Map
	* @return: Number of elements in map object
	*/
	virtual unsigned int Size() const = 0;
	
	/**
	* Adds a (key, value) pair to the map
	* @param k Is the key
	* @param v Is the value
	*/
	virtual void Put(const T1& k, const T2& v) = 0;
	
};
#endif