#pragma once
#include <iostream>
#include <initializer_list>
#include "BinaryTree.h"

template<class  T>
class  BinarySet
{
private:
	BinaryTree<T> m_binaryTree;
public:
	BinarySet():m_binaryTree(){}
	BinarySet(std::initializer_list<T> lst) : m_binaryTree(lst) {}
	void add(T element)
	{
		m_binaryTree.insert(element);
	}
	void erase(T element)
	{
		m_binaryTree.erase(element);
	}
	bool contains(T element)
	{
		return  m_binaryTree.contains(element);		
	}
};