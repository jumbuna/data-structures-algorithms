#pragma once

#include "PoolAllocator.h"
#include "Vector.h"
#include <utility>

template<class K, class V>
struct MapNode {
	//tombstone means node can be used during insertion and is also ignored during rehashing
	//free means node can be used during insertion
	bool tombstone, free;
	K key;
	V value;
	MapNode()
	:tombstone(false), free(true)
	{}
};

template<class K, class V>
class Map {
	using Node = MapNode<K, V>;
	//allow duplicateKeys?
	bool AllowDuplicates;
	//pool to allocate the table space
	Pool<Node> *memoryPool;
	std::size_t nodeCount, currentCapacity, threshold;
	const double loadFactor = 0.67;
	//expand table space
	void doubleCapacity();
	//find the index of a given key int the table
	std::size_t indexOf(K);
	//calculate the hashfunction of a given key
	//assumption key has a way of being hashed
	std::size_t hashFunction(K&);
	//find the next slot incase of key collision
	std::size_t probeFunction(std::size_t);
	//the object used to hash the key
	std::hash<K> hashingObject;
public:
	//constructor
	Map(bool = false);
	//copy constructor
	Map(Map<K, V>&);
	//destructor
	~Map();
	//insert values to the table
	void insert(K, V);
	void insert(std::pair<K, V>);
	//accessing values int the table
	V& operator[](K);
	//get current table size
	std::size_t size();
	//get current table capacity
	std::size_t capacity();
	//check for a given key in the table
	bool contains(K);
	//remove access to given key in the table
	void remove(K, bool=false);
	//return table to initial state
	void clear();
	//return vector containing all the keys
	Vector<K> keys();
	
	//TODO implement iterators
};

#include "HashMapImpl.h"