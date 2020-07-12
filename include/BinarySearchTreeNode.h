#pragma once

template<class T>
struct BstNode {
	BstNode(T, BstNode<T> *);
	T element;
	BstNode *leftChild;
	BstNode *rightChild;
	BstNode *parent;
};

template<class T>
BstNode<T>::BstNode(T element, BstNode<T> *parent)
:element(element), parent(parent), rightChild(nullptr), leftChild(nullptr)
{}
