// BinaryTree.cpp : Defines the entry point for the console application.
//

#include <windows.h>
#include <tchar.h>
#include <iostream>
#include "BinaryTree.h"

int _tmain(int argc, _TCHAR* argv[])
{
	BinaryTree<int> myBTree;
	myBTree.Insert(10);
	myBTree.Insert(5);
	myBTree.Insert(4);
	myBTree.Insert(11);
	myBTree.Insert(15);
	myBTree.Insert(6);

    std::cout << "TraverseInOrder\n";
	myBTree.TraverseInOrder();
    std::cout << "TraversePreOrder\n";
	myBTree.TraversePreOrder();
    std::cout << "TraversePostOrder\n";
	myBTree.TraversePostOrder();

    if (myBTree.IsValid()) {
        std::cout << "BTree is valid\n";
    } else {
        std::cout << "BTree is invalid\n";
    }

    int arr[] = { 10, 5, 3, 1, 4, 7, 20, 30 };
    BinaryTree<int> fromArr;
    fromArr.CreateBTree(arr, sizeof(arr)/sizeof(int), BinaryTree<int>::TraverseOrder::PreOrderTraverse);
    std::cout << "From Array TraversePreOrder\n";
    fromArr.TraversePreOrder();

    if (fromArr.IsValid()) {
        std::cout << "fromArr BTree is valid\n";
    } else {
        std::cout << "fromArr BTree is invalid\n";
    }
	return 0;
}

