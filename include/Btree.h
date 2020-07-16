#pragma once

#include "PoolAllocator.h"
#include "Vector.h"
#include "BinarySearchTree.h"
#include "BinarySearchTreeUtilities.h"

template<class T>
struct BtreeNode {
	BinarySearchTree<T> &elements;
	BinarySearchTree<BtreeNode*> &children;
};

template<class T>
class Btree {
	
};