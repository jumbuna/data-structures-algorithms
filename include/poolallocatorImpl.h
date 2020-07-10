#include "PoolAllocator.h"

template<class T, std::size_t growthsize>
MemoryPool<T, growthsize>::chunk::chunk(chunk *next)
:nextchunk(next)
{}

template<class T, std::size_t growthsize>
MemoryPool<T, growthsize>::buffer::buffer(buffer *next, std::size_t noc)
:nextbuffer(next), numberOfChunks(noc)
{
	block = reinterpret_cast<uint8_t*> (std::malloc(numberOfChunks * chunksize));
}

template<class T, std::size_t growthsize>
T* MemoryPool<T, growthsize>::buffer::getchunk(std::size_t index) {
	return reinterpret_cast<T*> (&block[chunksize*index]);
}

template<class T, std::size_t growthsize>
MemoryPool<T, growthsize>::MemoryPool()
:allocatingbuffer(nullptr), freelist(nullptr), usedblocks(growthsize)
{
	Pool<T>::numberOfChunks = growthsize;
}

template<class T, std::size_t growthsize>
MemoryPool<T, growthsize>::~MemoryPool() {
	while(allocatingbuffer) {
		buffer *temp = allocatingbuffer;
		allocatingbuffer = allocatingbuffer->nextbuffer;
		delete temp;
	}
}

template<class T, std::size_t growthsize>
T* MemoryPool<T, growthsize>::allocate() {
	if(freelist) {
		chunk *freechunk = freelist;
		freelist = freelist->nextchunk;
		return reinterpret_cast<T*> (freechunk);
	}
	
	if(usedblocks >= Pool<T>::numberOfChunks) {
		allocatingbuffer = new buffer(allocatingbuffer, Pool<T>::numberOfChunks);
		usedblocks = 0;
		Pool<T>::poolAddress = (T*) allocatingbuffer->block;
	}
	return allocatingbuffer->getchunk(usedblocks++);
}

template<class T, std::size_t growthsize>
void MemoryPool<T, growthsize>::deallocate(T *recycle) {
	recycle->~T();
	chunk *temp = reinterpret_cast<chunk*> (recycle);
	temp->nextchunk = freelist;
	freelist = temp;
}

template<class T, std::size_t growthsize>
void MemoryPool<T, growthsize>::reset() {
	while (allocatingbuffer->nextbuffer) {
		buffer *temp = allocatingbuffer;
		allocatingbuffer = allocatingbuffer->nextbuffer;
		delete temp;
	}
	freelist = nullptr;
	usedblocks = 0;	
}

template<class T, std::size_t growthsize>
template<typename ...Args>
T* Allocator<T, growthsize>::create(Args ...args) {
	return new (MemoryPool<T, growthsize>::allocate()) T(std::forward<T>(args...));
}

template<class T, std::size_t growthsize>
void Allocator<T, growthsize>::destroy(T *recycle) {
	MemoryPool<T, growthsize>::deallocate(recycle);
}

template<class T, std::size_t growthsize>
void Allocator<T, growthsize>::reset() {
	MemoryPool<T, growthsize>::reset();
}