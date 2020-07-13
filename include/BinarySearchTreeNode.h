#pragma once

template<class T>
struct BstNode {
	BstNode();
	BstNode(T, BstNode<T> *, BstNode<T> * = nullptr);
	T element;
	BstNode *leftChild;
	BstNode *rightChild;
	BstNode *parent;
};

template<class T>
BstNode<T>::BstNode()
{
	parent = rightChild = leftChild = nullptr;
}

template<class T>
BstNode<T>::BstNode(T element, BstNode<T> *parent, BstNode<T> *leafSentinel)
:element(element), parent(parent), rightChild(leafSentinel), leftChild(leafSentinel)
{}
