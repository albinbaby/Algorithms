/*
Developed by: Albin Baby (albinchiramel@gmail.com)
*/

#include <windows.h>
#include <iostream>
#include "BinaryTree.h"


template <class Type>
BinaryTree<Type>::BinaryTree(void)
{
	m_rootNode = 0;
}

template <class Type>
BinaryTree<Type>::BinaryTree(const Type& element)
{
	BinaryTree<Type>::BinaryTree();
	m_rootNode = new Node<Type>(element);
}

template <class Type>
BinaryTree<Type>::~BinaryTree(void)
{
	delete m_rootNode;
}

template <class Type>
void BinaryTree<Type>::Insert(const Type& element)
{
	Node<Type>** node = &m_rootNode;
	bool nodeExists = false;

	while(*node != NULL)
	{
		if((*node)->m_element == element)
		{
			// already exist in the tree
			nodeExists = true;
			break;
		}
		else if((*node)->m_element > element)
		{
			node = &(*node)->m_leftNode;
		}
		else
		{
			node = &(*node)->m_rightNode;
		}
	}

	if(false == nodeExists)
	{
		*node = new Node<Type>(element);
	}
}

template <class Type>
void BinaryTree<Type>::TraverseInOrder()
{
	InOrder(m_rootNode);
}

template <class Type>
void BinaryTree<Type>::TraversePreOrder()
{
	PreOrder(m_rootNode);
}

template <class Type>
void BinaryTree<Type>::TraversePostOrder()
{
	PostOrder(m_rootNode);
}

template <class Type>
void BinaryTree<Type>::InOrder(Node<Type>* node)
{
	if(NULL == node)
	{
		return;
	}

	InOrder(node->m_leftNode);
	std::cout << node->m_element << std::endl;
	InOrder(node->m_rightNode);
}

template <class Type>
void BinaryTree<Type>::PreOrder(Node<Type>* node)
{
	if(NULL == node)
	{
		return;
	}

	std::cout << node->m_element << std::endl;
	PreOrder(node->m_leftNode);
	PreOrder(node->m_rightNode);
}

template <class Type>
void BinaryTree<Type>::PostOrder(Node<Type>* node)
{
	if(NULL == node)
	{
		return;
	}

	PostOrder(node->m_leftNode);
	PostOrder(node->m_rightNode);
	std::cout << node->m_element << std::endl;
}

template <typename Type>
Type GetMin()
{
    return Type();
}

int GetMin()
{
    return INT_MIN;
}

template <typename Type>
Type GetMax()
{
    return Type();
}

int GetMax()
{
    return INT_MAX;
}

template <typename Type>
bool BinaryTree<Type>::IsValid()
{
    return IsBTree(m_rootNode, GetMin(), GetMax());
}

template <typename Type>
bool BinaryTree<Type>::IsBTree(Node<Type>* node, const Type& min, const Type& max)
{
    if (!node) return true;

    if (node->m_element > min && node->m_element < max) {
        return IsBTree(node->m_leftNode, min, node->m_element) && IsBTree(node->m_rightNode, node->m_element, max);
    }

    return false;
}

template <typename Type>
void BinaryTree<Type>::CreateBTree(const Type elements[], int size, TraverseOrder traverseOrder)
{
    int index = 0;
    switch (traverseOrder)
    {
    case PreOrderTraverse:
        m_rootNode = CreateBTreeFromPreOrder(GetMin(), GetMax(), index, elements, size);
    }
}

template <typename Type>
Node<Type>* BinaryTree<Type>::CreateBTreeFromPreOrder(const Type& min, const Type& max, int& index, const Type elements[], int size)
{
    if (index >= size || min > elements[index] || max < elements[index]) {
        return NULL;
    }

    Node<Type>* node = new Node<Type>(elements[index]);
    index++;
    node->m_leftNode = CreateBTreeFromPreOrder(min, node->m_element, index, elements, size);
    node->m_rightNode = CreateBTreeFromPreOrder(node->m_element, max, index, elements, size);
    return node;
}

template class BinaryTree<int>;
