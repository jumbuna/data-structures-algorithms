#include <iostream>
#include <cstdlib>

template<class t>
struct pool {
	struct node {
			node *next;
	};
	
	struct buffer {
			buffer *next;
			static const std::size_t grow = 1024;
			static const std::size_t blocksize = sizeof(node) > sizeof(t) ? sizeof(node) : sizeof(t);;
			buffer(buffer *next)
			:next(next)
			{
					
			}
			uint8_t array[grow*blocksize];
			t *getblock(std::size_t index) {
					return reinterpret_cast<t*>(&array[index*blocksize]);
			}
	};
	
	buffer *currentbuffer = nullptr;
	node *freelist = nullptr;
	std::size_t usedblocks = 1024;
	
	t* allocate() {
			if(freelist) {
					node *freeblock = freelist;
					freelist = freelist->next;
					return reinterpret_cast<t*>(freeblock);
			}
			
			if(usedblocks >= 1024) {
					currentbuffer = new buffer(currentbuffer);
					usedblocks = 0;
			}
			return currentbuffer->getblock(usedblocks++);
	}
	
	void deallocate(t *reusable) {
			node *reuse = reinterpret_cast<node*>(reusable);
			reuse->next = freelist;
			freelist = reuse;
	}
	
	~pool() {
			while(currentbuffer) {
					buffer *temp = currentbuffer;
					currentbuffer = currentbuffer->next;
					delete temp;
			}
	}
};

template<class t>
struct allocator : private pool<t> {
		template<typename ...Arg>
		t* create(Arg ...args) {
				return new(pool<t>::allocate()) t(std::forward<t>(args...));
		}
		
		void destroy(t* pointer) {
				pool<t>::deallocate(pointer);
		}
};
