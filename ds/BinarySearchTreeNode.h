#pragma once

//base class for all nodes of a binary tree

namespace jumbuna {
template<class T>
struct BstNode {
	BstNode();
	BstNode(T, BstNode<T> *, BstNode<T> * = nullptr);
	T element;
	BstNode *leftChild;
	BstNode *rightChild;
	BstNode *parent;
};
}

using namespace jumbuna;

template<class T>
BstNode<T>::BstNode()
{
	parent = rightChild = leftChild = nullptr;
}

template<class T>
BstNode<T>::BstNode(T element, BstNode<T> *parent, BstNode<T> *leafSentinel)
:element(element), parent(parent), rightChild(leafSentinel), leftChild(leafSentinel)
{}
