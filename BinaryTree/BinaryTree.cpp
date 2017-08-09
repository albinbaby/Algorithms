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

template class BinaryTree<int>;
