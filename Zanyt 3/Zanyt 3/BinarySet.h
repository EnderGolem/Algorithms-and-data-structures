#pragma once
#include <iostream>
#include <initializer_list>
#include "BinaryTree.h"




template<class  T>
class  BinarySet
{

private:
	BinaryTree<T> m_binaryTree;
	
	class iteratorBinarySet
	{
	private:
		typename BinaryTree<T> ::iteratorBinaryTree m_iterator;
	public:
		//Можно так typename T::template BinaryTree<T> ::iteratorBinaryTree m_iterator
		//итак		typename BinaryTree<T> ::iteratorBinaryTree m_iterator
		iteratorBinarySet(typename BinaryTree<T> ::iteratorBinaryTree m_iterator) :m_iterator(m_iterator) {}
		T& operator*()
		{
			return  *m_iterator;
		}
		iteratorBinarySet operator++() { return ++m_iterator; }
		iteratorBinarySet operator++(int) { return  m_iterator++; }
		friend bool operator==(iteratorBinarySet v1, iteratorBinarySet v2) {
			return v1.m_iterator == v2.m_iterator;
		}
		friend bool operator!=(iteratorBinarySet v1, iteratorBinarySet v2) {
			return !(v1 == v2);
		}
		
	};
	
public:
	
	iteratorBinarySet begin()
	{
		return m_binaryTree.begin();
	}
	iteratorBinarySet end()
	{
		return m_binaryTree.end();
	}
	
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
