#pragma once
#include <iostream>
template<class  T>
class  BinaryTree
{
private:
	struct  Node
	{
		T data;
		Node* parent, * left, * right;
	};
public:
	Node* m_root;
	BinaryTree(): m_root(nullptr)
	{
	}
	void insert(T data)
	{
		if(m_root == nullptr)
		{
			m_root = new Node{ data,nullptr,nullptr,nullptr };
			return;
		}
		auto current = m_root;
		while(current != nullptr)
		{
			if (current->data > data) {
				if (current->left == nullptr) {
					current->left = new Node{ data,current,nullptr,nullptr };
					return;
				}
				current = current->left;
			}			
			else
			{
				if (current->right == nullptr) {
					current->right = new Node{ data,current,nullptr,nullptr };
					return;
				}
				current = current->right;
			}
		}
	}
	/// <summary>
	/// Проверка на содержание в дереве
	/// </summary>
	bool contains(T data)
	{
	return data == 	generalBound(data, [](T x, T y)->T {return  x == y; });
	}
	T maxElement()
	{
		auto current = m_root;
		while (current->right != nullptr)
			current = current->right;
		return  current->data;
	}
	T minElement()
	{
		auto current = m_root;
		while (current->left != nullptr)
			current = current->left;
		return  current->data;
	}
	T lowerBound(T data)
	{
		return 	generalBound(data, [](T x, T y)->T {return x >= y; });	
	}
	T upperBound(T data)
	{
		return 	generalBound(data, [](T x, T y)->T {return x > y; });	
	}
	/// <summary>
	/// Для сравнения по своему усмотрению
	/// </summary>
	/// <param name="compare">Функция сравнения</param>
	T generalBound(T data, T (*compare)(T, T))
	{
		if (m_root == nullptr)
		{
			return  T();
		}
		auto current = m_root;
		while (current != nullptr)
		{
			if ( compare(current->data,data))
				return current->data;
			if (current->data > data)
			{
				current = current->left;
			}
			else
			{
				current = current->right;
			}
		}
	}
	/// <summary>
	/// Вывод ЛКП 
	/// </summary>
	void printLKP()
	{
		printLKPAuxiliary(m_root);
		std::cout << '\n';
	}


private:
	/// <summary>
	/// Вывод ЛКП  дополнительная функция
	/// </summary>
	void printLKPAuxiliary(Node* current)
	{
		if(current == nullptr)
			return;
		printLKPAuxiliary(current->left);
		std::cout << current->data << ' ';
		printLKPAuxiliary(current->right);
	}
};
