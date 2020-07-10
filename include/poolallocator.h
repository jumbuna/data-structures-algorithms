/*
	base class monotonic allocator
*/

#pragma once

#include <cstdlib>
#include <utility>

template<class T>
class Pool {
public:
	std::size_t numberOfChunks = 1024;
	T *poolAddress = nullptr;
	virtual T* allocate() = 0;
	virtual void deallocate(T *) = 0;
	virtual void reset() = 0;
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
		static const std::size_t chunksize = sizeof(chunk) > sizeof(T) ? sizeof(chunk) : sizeof(T);
	public:
		uint8_t *block;
		buffer *nextbuffer;
		buffer(buffer *, std::size_t);
		T* getchunk(std::size_t);
		~buffer() {
			std::free(reinterpret_cast<void*> (block));
		}
	};
	
	buffer *allocatingbuffer;
	chunk *freelist;
	std::size_t usedblocks;
public:
	MemoryPool();
	~MemoryPool();
	MemoryPool(const MemoryPool&) = delete;
	MemoryPool(const MemoryPool&&) = delete;
	MemoryPool operator=(const MemoryPool&) = delete;
	MemoryPool operator=(const MemoryPool&&) = delete;
	virtual T* allocate() override;
	virtual void deallocate(T *) override;
	virtual void reset() override;
};

template<class T, std::size_t growthsize = 1024>
class Allocator: private MemoryPool<T, growthsize> {
public:
	template<typename ...Args>
	T *create(Args ...args);
	void destroy(T *);
	void reset();
};

#include "PoolAllocatorImpl.h"