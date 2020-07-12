#include "PoolAllocator.h"

//constructor -> links a chunk to the next forming the freelist
template<class T, std::size_t growthsize>
MemoryPool<T, growthsize>::chunk::chunk(chunk *next)
:nextchunk(next)
{}

template<class T, std::size_t growthsize>
MemoryPool<T, growthsize>::buffer::buffer(buffer *next, std::size_t noc)
:nextbuffer(next), numberOfChunks(noc)
{
	//request a block from the system
	block = reinterpret_cast<uint8_t*> (std::malloc(numberOfChunks * chunksize));
}

template<class T, std::size_t growthsize>
T* MemoryPool<T, growthsize>::buffer::getchunk(std::size_t index) {
	//return pointer to the begining of a chunk
	return reinterpret_cast<T*> (&block[chunksize*index]);
}

template<class T, std::size_t growthsize>
MemoryPool<T, growthsize>::MemoryPool()
:allocatingbuffer(nullptr), freelist(nullptr), usedblocks(growthsize)
{
	//set numberOfChunks to the given growth size passed as template argument 
	Pool<T>::numberOfChunks = growthsize;
}

template<class T, std::size_t growthsize>
MemoryPool<T, growthsize>::~MemoryPool() {
	//free all buffer which were allocated using new
	while(allocatingbuffer) {
		buffer *temp = allocatingbuffer;
		allocatingbuffer = allocatingbuffer->nextbuffer;
		delete temp;
	}
}

template<class T, std::size_t growthsize>
T* MemoryPool<T, growthsize>::allocate() {
	//return a chunk from the freelist if it's not empty
	if(freelist) {
		chunk *freechunk = freelist;
		freelist = freelist->nextchunk;
		return reinterpret_cast<T*> (freechunk);
	}
	
	//if the number of usedchunks then generate a new buffer and use that for allocation
	if(usedblocks >= Pool<T>::numberOfChunks) {
		
		allocatingbuffer = new buffer(allocatingbuffer, Pool<T>::numberOfChunks);
		usedblocks = 0;
		//set the base pool address to the block in the buffer
		//done only once
		//this is a tweak to allow for a vector to use pool address as an array name
		if(!Pool<T>::poolAddress) {
			Pool<T>::poolAddress = (T*) allocatingbuffer->block;
		}
	}
	//return a chunk from the buffer block
	return allocatingbuffer->getchunk(usedblocks++);
}

template<class T, std::size_t growthsize>
void MemoryPool<T, growthsize>::deallocate(T *recycle) {
	//destruct object currently held in the chunk
	recycle->~T();
	//add chunk to the begining of the free list for later usage
	chunk *temp = reinterpret_cast<chunk*> (recycle);
	temp->nextchunk = freelist;
	freelist = temp;
}

template<class T, std::size_t growthsize>
void MemoryPool<T, growthsize>::reset() {
	//clear all buffers except for the initial one
	while (allocatingbuffer->nextbuffer) {
		buffer *temp = allocatingbuffer;
		allocatingbuffer = allocatingbuffer->nextbuffer;
		delete temp;
	}
	//clear the free list
	freelist = nullptr;
	usedblocks = 0;	
}

template<class T, std::size_t growthsize>
template<typename ...Args>
T* Allocator<T, growthsize>::create(Args&& ...args) {
	//object construction
	return new (MemoryPool<T, growthsize>::allocate()) T(std::forward<Args>(args)...);
}

template<class T, std::size_t growthsize>
void Allocator<T, growthsize>::destroy(T *recycle) {
	MemoryPool<T, growthsize>::deallocate(recycle);
}

template<class T, std::size_t growthsize>
void Allocator<T, growthsize>::reset() {
	MemoryPool<T, growthsize>::reset();
}