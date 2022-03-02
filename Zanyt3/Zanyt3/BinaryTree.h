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
	bool contains(T data)
	{
		if (m_root == nullptr)
		{
			m_root = new Node{ data,nullptr,nullptr,nullptr };
			return  false;
		}
		auto current = m_root;
		while (current != nullptr)
		{
			if (current->data == data)
				return true;
			if (current->data > data) 
			{			
				current = current->left;
			}
			else
			{
				current = current->right;
			}
		}
		return false;
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
