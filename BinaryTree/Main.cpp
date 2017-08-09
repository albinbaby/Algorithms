// BinaryTree.cpp : Defines the entry point for the console application.
//

#include <windows.h>
#include <tchar.h>
#include "BinaryTree.h"

int _tmain(int argc, _TCHAR* argv[])
{
	BinaryTree<int> myBTree;
	myBTree.Insert(10);
	myBTree.Insert(5);
	myBTree.Insert(4);
	myBTree.Insert(10);
	myBTree.Insert(15);
	myBTree.Insert(6);

	myBTree.TraverseInOrder();
	myBTree.TraversePreOrder();
	myBTree.TraversePostOrder();
	return 0;
}

