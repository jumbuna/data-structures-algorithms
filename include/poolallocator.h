/*
	base class monotonic allocator
*/

#pragma once

#include <cstdlib>
#include <utility>

template<class T, std::size_t growthsize = 1024>
class memorypool {
	//form a linked list of freed memory
	struct chunk {
		chunk(chunk *);
		chunk *nextchunk;
	};
	//memory pool that get expanded on demand
	class buffer {
		static const std::size_t chunksize = sizeof(chunk) > sizeof(T) ? sizeof(chunk) : sizeof(T);
		uint8_t block[chunksize * growthsize];
	public:
		buffer *nextbuffer;
		buffer(buffer *);
		T* getchunk(std::size_t);
	};
	
	buffer *allocatingbuffer;
	chunk *freelist;
	std::size_t usedblocks;
public:
	memorypool();
	~memorypool();
	memorypool(const memorypool&) = delete;
	memorypool(const memorypool&&) = delete;
	memorypool operator=(const memorypool&) = delete;
	memorypool operator=(const memorypool&&) = delete;
	T* allocate();
	void deallocate(T *);
	void reset();
};

template<class T, std::size_t growthsize = 1024>
class Allocator: private memorypool<T, growthsize> {
public:
	template<typename ...Args>
	T *create(Args ...args);
	void destroy(T *);
	void reset();
};

#include "poolallocatorImpl.h"




























//#include <iostream>
//#include <cstdlib>
//
//template<class t>
//struct pool {
//	struct node {
//			node *next;
//	};
//	
//	struct buffer {
//			buffer *next;
//			static const std::size_t grow = 1024;
//			static const std::size_t blocksize = sizeof(node) > sizeof(t) ? sizeof(node) : sizeof(t);;
//			buffer(buffer *next)
//			:next(next)
//			{
//					
//			}
//			uint8_t array[grow*blocksize];
//			t *getblock(std::size_t index) {
//					return reinterpret_cast<t*>(&array[index*blocksize]);
//			}
//	};
//	
//	buffer *currentbuffer = nullptr;
//	node *freelist = nullptr;
//	std::size_t usedblocks = 1024;
//	
//	t* allocate() {
//			if(freelist) {
//					node *freeblock = freelist;
//					freelist = freelist->next;
//					return reinterpret_cast<t*>(freeblock);
//			}
//			
//			if(usedblocks >= 1024) {
//					currentbuffer = new buffer(currentbuffer);
//					usedblocks = 0;
//			}
//			return currentbuffer->getblock(usedblocks++);
//	}
//	
//	void deallocate(t *reusable) {
//			reusable->~t();
//			node *reuse = reinterpret_cast<node*>(reusable);
//			reuse->next = freelist;
//			freelist = reuse;
//	}
//	
//	~pool() {
//			while(currentbuffer) {
//					buffer *temp = currentbuffer;
//					currentbuffer = currentbuffer->next;
//					delete temp;
//			}
//	}
//};
//
//template<class t>
//struct allocator : private pool<t> {
//		template<typename ...Arg>
//		t* create(Arg ...args) {
//				return new(pool<t>::allocate()) t(std::forward<t>(args...));
//		}
//		
//		void destroy(t* pointer) {
//				pool<t>::deallocate(pointer);
//		}
//};
