#include "Queue.h"

template<class T, class A>
void Queue<T, A>::push(T element) {
	list.push_back(element);
}

template<class T, class A>
T Queue<T, A>::pop() {
	return list.pop_front();
}

template<class T, class A>
T Queue<T, A>::peek() {
	return list.peek_front();
}

template<class T, class A>
std::size_t Queue<T, A>::size() {
	return list.size();
}

template<class T, class A>
bool Queue<T, A>::contains(T element) {
	return list.contains(element);
}

template<class T, class A>
bool Queue<T, A>::empty() {
	return list.empty();
}

template<class T, class A>
void Queue<T, A>::clear() {
	list.clear();
}