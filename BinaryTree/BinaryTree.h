/*
Developed by: Albin Baby (albinchiramel@gmail.com)
*/

#pragma once

template<class Type>
class Node
{
public:
	Node(Type element)
	{
		m_element = element;
		m_leftNode = NULL;
		m_rightNode = NULL;
	}
	~Node()
	{
	}
	Type m_element;
	Node* m_leftNode;
	Node* m_rightNode;
};


template<class Type>
class BinaryTree
{
public:
	BinaryTree(void);
	BinaryTree(const Type& element);
	virtual ~BinaryTree(void);

	void Insert(const Type& node);
	void TraverseInOrder();
	void TraversePreOrder();
	void TraversePostOrder();

private:
	Node<Type>* m_rootNode;

	void InOrder(Node<Type>* node);
	void PreOrder(Node<Type>* node);
	void PostOrder(Node<Type>* node);
};
