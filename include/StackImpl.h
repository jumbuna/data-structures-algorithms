#include "Stack.h"

template<class T, class A>
void Stack<T, A>::push(T element) {
	list.push_front(element);
}

template<class T, class A>
T Stack<T, A>::pop() {
	return list.pop_front();
}

template<class T, class A>
T Stack<T, A>::peek() {
	return list.peek_front();
}

template<class T, class A>
std::size_t Stack<T, A>::size() {
	return list.size();
}

template<class T, class A>
bool Stack<T, A>::contains(T element) {
	return list.contains(element);
}

template<class T, class A>
bool Stack<T, A>::empty() {
	return list.empty();
}

template<class T, class A>
void Stack<T, A>::clear() {
	list.clear();
}