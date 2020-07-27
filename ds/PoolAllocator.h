/*
	base class monotonic allocator
*/

#pragma once

#include <cstdlib>
#include <utility>

template<class T>
class Pool {
public:
	//the requested number of chunks the block is to be split in
	std::size_t numberOfChunks = 1024;
	//address of the block
	T *poolAddress = nullptr;
	//return a chunk from the block
	virtual T* allocate() = 0;
	//takes a given chunk and adds it to the fre list for later usage
	virtual void deallocate(T *) = 0;
	//reset the pool to its initial state by clearing the free list and setting address to beginning of block
	virtual void reset() = 0;
	//freees th block of memory back to the system
	virtual ~Pool() = default;
};

template<class T, std::size_t growthsize = 1024>
class MemoryPool: public Pool<T> {
	//form a linked list of freed memory
	struct chunk {
		chunk(chunk *);
		chunk *nextchunk;
	};
	//memory pool that get expanded on demand
	class buffer {
		std::size_t numberOfChunks;
		//iuf chank is maller than pointer size the use pointer size as size of a chunk
		static const std::size_t chunksize = sizeof(chunk) > sizeof(T) ? sizeof(chunk) : sizeof(T);
	public:
		//pointer to the requested block 
		uint8_t *block;
		//pointer to next buffer incase this buffer is fully utilized
		buffer *nextbuffer;
		//constructor
		buffer(buffer *, std::size_t);
		//get a chunk from th block
		T* getchunk(std::size_t);
		~buffer() {
			//destructor to return the block memory back to the system
			std::free(reinterpret_cast<void*> (block));
		}
	};
	//pointer to the buffer being used to allocate chunks
	buffer *allocatingbuffer;
	//list of chunk addresses that have been release back to  the allocator by the user
	chunk *freelist;
	//the number of chuks that have already been occupied
	//TODO rename to usedChunks
	std::size_t usedblocks;
public:
	MemoryPool();
	~MemoryPool();
	//prevent auto-genenration of copy and move constructors
	MemoryPool(const MemoryPool&) = delete;
	MemoryPool(const MemoryPool&&) = delete;
	MemoryPool operator=(const MemoryPool&) = delete;
	MemoryPool operator=(const MemoryPool&&) = delete;
	//override methods of base class Pool
	virtual T* allocate() override;
	virtual void deallocate(T *) override;
	virtual void reset() override;
};

//growthsize == numberOfchunks
template<class T, std::size_t growthsize = 1024>
class Allocator: public MemoryPool<T, growthsize> {
public:
	//construct the object in a chunk and return the address
	template<typename ...Args>
	T *create(Args&& ...args);
	//add given address to the pools free list
	void destroy(T *);
	//reset the pool
	void reset();
};

#include "PoolAllocatorImpl.h"