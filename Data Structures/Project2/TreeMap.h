#ifndef TREEMAP_H
#define TREEMAP_H
#include "Map.h"

/**
* A class that implements the Map.h interface.
* This implements the Map ADT using a binary
* search tree. T1 is the
* type of the key T2 is the type of the
* value in a (key, value) pair.
*/

template <typename T1, typename T2>
class TreeMap : public Map < T1, T2 >
{
public:
	//Default constructor
	TreeMap()
	{
		root = NULL;
		n = 0;
	}

	//Copy constructor
	TreeMap(const TreeMap& tm)
	{
		if (rhs.n == 0) {
			n = 0;
			root = NULL; 
		}
		else {
			this->preOrder(tm.root);
		}
	}

	//Virtual destructor
	virtual ~TreeMap()
	{
		Clear();
	}

	TreeMap& operator=(const TreeMap& rhs)
	{
		this->Clear();
		if (rhs.n == 0) {
			return *this;
		}
		this->preOrder(rhs.root);
		return *this;
	}

	void Clear() {
		int x = n;
		for (int i = 0; i < x-1; i++) {
			Erase(root->kv.key);
		}
		delete root;
		root = NULL; 
		n = 0; 
	}

	virtual void Erase(const T1& k)
	{
		KeyValue t(k);
		Remove(root, t);
		--n;
	}

	virtual T2& Find(const T1& k) const
	{
		if (n == 0) {
			throw ELE_DNE;
		}

		Node * ptr = root;
		KeyValue t(k);
		while (true) {
			if (ptr == NULL)
				throw ELE_DNE;
			if (t == ptr->kv){
				return ptr->kv.value;
			}
			else if (t < ptr->kv) {
				ptr = ptr->left;
			}
			else if (t > ptr->kv) {
				ptr = ptr->right;
			}
		} //end while

	}

	virtual void Put(const T1& k, const T2& v)
	{
		KeyValue t(k, v);
		if (n == 0) {
			root = new Node(t);
		}
		else {
			Insert(t);
		}
		n++;
	}

	virtual unsigned int Size() const
	{
		return n;
	}



private:
	//The root of the tree and the number of children (n)
	class KeyValue
	{
	public:
		T1 key;
		T2 value;
		KeyValue(){}
		KeyValue(T1 k) {
			key = k;
		}
		KeyValue(T1 k, T2 v) {
			key = k;
			value = v;
		}
		friend bool operator==(const KeyValue &lhs, const KeyValue & rhs) {
			return lhs.key == rhs.key;
		}
		friend bool operator<(const KeyValue & lhs, const KeyValue & rhs) {
			return lhs.key < rhs.key;
		}
		friend bool operator>(const KeyValue & lhs, const KeyValue & rhs) {
			return lhs.key > rhs.key;
		}
	};

	class Node
	{
	public:
		Node() { right = left = NULL; }
		Node(KeyValue val) {
			right = left = NULL;
			kv.key = val.key; kv.value = val.value;
		}
		Node(T1 x, T2 y) {
			right = left = NULL;
			kv.key = x; kv.value = y;
		}
		Node* right;
		Node* left;
		KeyValue kv;
	};

	//---------------------Used for iterations and returns Nodes and accepts keyvalue pairs-----------------------
	void preOrder(Node* n) {
		if (n) {
			Put(n->kv.key, n->kv.value);
			preOrder(n->left);
			preOrder(n->right);
		}
	}

	//Remove uses Find
	Node* const & Find(Node * const & ptr, const KeyValue& keyval) const {
		if (ptr == NULL || keyval == ptr->kv){
			return ptr;
		}
		else if (keyval < ptr->kv) {
			return Find(ptr->left, keyval);
		}
		else {
			return Find(ptr->right, keyval);
		}
	}

	void Insert(const KeyValue& keyval) const {
		Node * ptr = root;
		while (true) {
			if (keyval == ptr->kv){
				ptr->kv.key = keyval.key;
				break;
			}
			else if (keyval < ptr->kv) {
				if (ptr->left == NULL) {
					ptr->left = new Node(keyval);
					break;
				}
				else {
					ptr = ptr->left;
				}
			}
			else if (keyval > ptr->kv) {
				if (ptr->right == NULL) {
					ptr->right = new Node(keyval);
					break;
				}
				else {
					ptr = ptr->right;
				}
			}
		} //end while

	}

	void Remove(Node * &ptr, const KeyValue& keyval) {
		Node *& node = const_cast<Node *&>(Find(ptr, keyval));
		if (node == NULL) {
			throw ELE_DNE;
		}

		if (node->right != NULL && node->left != NULL) { //if two children
			Node* tmp = FindMinNode(node->right);
			node->kv = tmp->kv;
			Remove(node->right, node->kv);
		}
		else if (node->right != NULL) { //if one child
			Node * tmp = node;
			node = node->right;
			delete tmp;
		}
		else if (node->left != NULL) {
			Node * tmp = node;
			node = node->left;
			delete tmp;
		}
		else { //no children
			delete node;
			node = NULL;
		}

	}

	Node * FindMinNode(Node * p) {
		while (p->left != NULL) {
			p = p->left;
		}
		return p;
	}

	Node* root;
	unsigned int n;

};
#endif