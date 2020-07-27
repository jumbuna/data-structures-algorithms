#include "HashMap.h"


template<class K, class V>
void Map<K, V>::doubleCapacity() {
	//double the capacity
	currentCapacity *= 2;
	//update threshold
	threshold = currentCapacity * loadFactor;
	//create a new pool
	Pool<Node> *newPool = new MemoryPool<Node>;
	//set new pool size to be twice that of the current pool
	newPool->numberOfChunks = currentCapacity;
	//allocate actual pool space
	newPool->allocate();
	//get the table address from the new pool
	Node *newPoolAddress = newPool->poolAddress;
	//set every node in new table to be free
	Node node; 
	for(std::size_t i = 0; i < currentCapacity; i++) {
		newPoolAddress[i] = node;
	}
	for(std::size_t i = 0; i < currentCapacity/2; i++) {
		node = memoryPool->poolAddress[i];
		//ignore free and tombstones from the current table
		if(!node.free && !node.tombstone) {
			std::size_t nodeKeyHash = hashFunction(node.key);
			for(std::size_t j = 1; !newPoolAddress[nodeKeyHash].free; j++) {
				nodeKeyHash = (nodeKeyHash + probeFunction(j)) % currentCapacity;
			}
			newPoolAddress[nodeKeyHash] = node;
		}
	}
	//release previous table memory to the system
	memoryPool->~Pool();
	//use new table
	memoryPool = newPool;
}

template<class K, class V>
std::size_t Map<K, V>::hashFunction(K &key) {
	//modulo of the hash current capacity so as to remain in the bounds of table size
	return hashingObject(key) % currentCapacity;
}

template<class K, class V>
std::size_t Map<K, V>::probeFunction(std::size_t step) {
	//linear probe
	//can also use quadratic probe : pow(step, 2) + step; provides table capacity is a factor of 2
	return step;
}

template<class K, class V>
std::size_t Map<K, V>::indexOf(K key) {
	//incase table is empty the just return -1
	if(nodeCount == 0) {
		return -1;
	}
	//calculate hash of given key
	std::size_t keyHash = hashFunction(key);
	for(std::size_t i = 0; ;i++) {
		//free block signifies that we've checked in all the possible locations of given key in the table
		if(memoryPool->poolAddress[keyHash].free) {
			break;
		}
		//tombstone nodes are ignored during search
		if(memoryPool->poolAddress[keyHash].key == key && !memoryPool->poolAddress[keyHash].tombstone) {
			return keyHash;
		}
		//go to next possible location of the key in the table
		keyHash = (keyHash + probeFunction(i)) % currentCapacity;
	}
	//key was not found in the table
	return -1;
}


template<class K, class V>
Map<K, V>::Map(bool allowDuplicates)
:nodeCount(0), currentCapacity(16), AllowDuplicates(allowDuplicates)
{
	//initial pool
	memoryPool = new MemoryPool<Node>;
	threshold = loadFactor * currentCapacity;
}

template<class K, class V>
Map<K, V>::Map(Map<K, V> &other) {
	memoryPool = new MemoryPool<Node>;
	currentCapacity = other.currentCapacity;
	nodeCount = other.nodeCount;
	threshold = other.threshold;
	AllowDuplicates = other.AllowDuplicates;
	memoryPool->numberOfChunks = currentCapacity;
	memoryPool->allocate();
	std::memcpy(memoryPool->poolAddress, other.memoryPool->poolAddress, currentCapacity * sizeof(Node));
}

template<class K, class V>
Map<K, V>::~Map() {
	//release memory bac to the system
	memoryPool->~Pool();
}

template<class K, class V>
void Map<K, V>::insert(K key, V value) {
	//allocate memory for table
	if(memoryPool->poolAddress == nullptr) {
		//specify the number of nodes the table will hold
		memoryPool->numberOfChunks = currentCapacity;
		//allocates the actual space for the table
		memoryPool->allocate();
		Node node{};
		//initialize all table slots to free
		for(int i = 0; i < currentCapacity; i++) {
			memoryPool->poolAddress[i] = node;
		}
	}
	//if key is already in table then just update the value
	//making it multimap by removing the if statement
	if(contains(key) && !AllowDuplicates) {
		operator[](key) = value;
	}else {
		//find where to place the given key and value in the table taking care of possible key collisions
		std::size_t keyHash = hashFunction(key);
		for(std::size_t i = 1; !memoryPool->poolAddress[keyHash].free; i++){
			keyHash = (keyHash + probeFunction(i)) % currentCapacity;
		}
		//mark the slot as occupied
		memoryPool->poolAddress[keyHash].free = false;
		memoryPool->poolAddress[keyHash].key = key;
		memoryPool->poolAddress[keyHash].value = value;
		//incase we used a slot that was initially  a tombstone then mark it as not a tombstone :)
		memoryPool->poolAddress[keyHash].tombstone = false;
		//increment the count of non-free/non-tombstone in the table
		++nodeCount;
		if(nodeCount >= threshold) {
			//alocate new table with a higher capacity
			//this is necessary to reduce collisions
			doubleCapacity();
		}
	}
}

template<class K, class V>
void Map<K, V>::insert(std::pair<K, V> kv) {
	//accessibility function
	insert(kv.first, kv.second);
}

template<class K, class V>
V& Map<K, V>::operator[](K key) {
	//only changes first occurence incase of multiple keys
	std::size_t index = indexOf(key);
	if(index != -1) {
		return memoryPool->poolAddress[index].value;
	}else {
		//if key is absent then insert it and call this function which will now resolve to the first case
		V value;
		insert(key, value);
		return operator[](key);
	}

}

template<class K, class V>
std::size_t Map<K, V>::size() {
	//get the current number of non-free/non-tombstone nodes
	return nodeCount;
}

template<class K, class V>
std::size_t Map<K, V>::capacity() {
	//get current capacity of the table
	return currentCapacity;
}

template<class K, class V>
bool Map<K, V>::contains(K key) {
	return indexOf(key) != -1;
}

template<class K, class V>
void Map<K, V>::remove(K key, bool all) {
	//no removal actually happens
	//the slot of the key is just omitted during search
	std::size_t index = indexOf(key);
	if(!all && index != -1) {
		memoryPool->poolAddress[index].tombstone = true;
		--nodeCount;
	} else {
		while(index != -1) {
			memoryPool->poolAddress[index].tombstone = true;
			--nodeCount;
			index = indexOf(key);
		}
	}
}

template<class K, class V>
void Map<K, V>::clear() {
	//just mark all slots in the table as free
	for(std::size_t i = 0; i < currentCapacity; i++) {
		memoryPool->poolAddress[i].free = true;
	}
	nodeCount = 0;
}

template<class K, class V>
Vector<K> Map<K, V>::keys() {
	Vector<K> vector {nodeCount};
	if(size() == 0) {
		return vector;
	}
	for(std::size_t i = 0; i < currentCapacity; i++) {
		if(!memoryPool->poolAddress[i].free && !memoryPool->poolAddress[i].tombstone) {
			vector.push_back(memoryPool->poolAddress[i].key);
		}
	}
	return vector;
}