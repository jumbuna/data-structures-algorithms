#include "poolallocator.h"

template<class T, std::size_t growthsize>
memorypool<T, growthsize>::chunk::chunk(chunk *next)
:nextchunk(next)
{}

template<class T, std::size_t growthsize>
memorypool<T, growthsize>::buffer::buffer(buffer *next)
:nextbuffer(next)
{}

template<class T, std::size_t growthsize>
T* memorypool<T, growthsize>::buffer::getchunk(std::size_t index) {
	return reinterpret_cast<T*> (&block[chunksize*index]);
}

template<class T, std::size_t growthsize>
memorypool<T, growthsize>::memorypool()
:allocatingbuffer(nullptr), freelist(nullptr), usedblocks(growthsize)
{}

template<class T, std::size_t growthsize>
memorypool<T, growthsize>::~memorypool() {
	while(allocatingbuffer) {
		buffer *temp = allocatingbuffer;
		allocatingbuffer = allocatingbuffer->nextbuffer;
		delete allocatingbuffer;
	}
}

template<class T, std::size_t growthsize>
T* memorypool<T, growthsize>::allocate() {
	if(freelist) {
		chunk *freechunk = freelist;
		freelist = freelist->nextchunk;
		return reinterpret_cast<T*> (freechunk);
	}
	
	if(usedblocks >= growthsize) {
		allocatingbuffer = new buffer(allocatingbuffer);
		usedblocks = 0;
	}
	return allocatingbuffer->getchunk(usedblocks++);
}

template<class T, std::size_t growthsize>
void memorypool<T, growthsize>::deallocate(T *recycle) {
	recycle->~T();
	chunk *temp = reinterpret_cast<chunk*> (recycle);
	temp->nextchunk = freelist;
	freelist = temp;
}

template<class T, std::size_t growthsize>
void memorypool<T, growthsize>::reset() {
	while (allocatingbuffer) {
		buffer *temp = allocatingbuffer;
		allocatingbuffer = allocatingbuffer->nextbuffer;
		delete temp;
	}
	freelist = nullptr;
	usedblocks = growthsize;	
}

template<class T, std::size_t growthsize>
template<typename ...Args>
T* Allocator<T, growthsize>::create(Args ...args) {
	return new (memorypool<T, growthsize>::allocate()) T(std::forward<T>(args...));
}

template<class T, std::size_t growthsize>
void Allocator<T, growthsize>::destroy(T *recycle) {
	memorypool<T, growthsize>::deallocate(recycle);
}

template<class T, std::size_t growthsize>
void Allocator<T, growthsize>::reset() {
	memorypool<T, growthsize>::reset();
}