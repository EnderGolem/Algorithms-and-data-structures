#pragma once
#include <iostream>
#include <stack> 
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
	BinaryTree() : m_root(nullptr)
	{
	}
	void insert(T data)
	{
		if (m_root == nullptr)
		{
			m_root = new Node{ data,nullptr,nullptr,nullptr };
			return;
		}
		auto current = m_root;
		while (current != nullptr)
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
	/// �������� �� ���������� � ������
	/// </summary>
	bool contains(T data)
	{
		return data == generalBound(data, [](T x, T y)->T {return  x == y; });
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
	/// ��� ��������� �� ������ ����������
	/// </summary>
	/// <param name="compare">������� ���������</param>
	T generalBound(T data, T(*compare)(T, T))
	{
		if (m_root == nullptr)
		{
			return  T();
		}
		auto current = m_root;
		while (current != nullptr)
		{
			if (compare(current->data, data))
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
	/// ����� ��� 
	/// </summary>
	void printLKP()
	{
		printLKPAuxiliary(m_root);
		std::cout << '\n';
	}
	/// <summary>
	/// ����� ���
	/// </summary>
	void printPKL()
	{
		if(m_root == nullptr)
		{
			std::cout << "null\n"; return;;
		}
		std::stack<Node*> stack;
		auto top = m_root;
		while (top != nullptr || !stack.empty())
		{
			if (!stack.empty())
			{
				top = stack.top();
				stack.pop();
				std::cout << top->data << " ";
				top = top->left;
			}
			while (top != nullptr)
			{
				stack.push(top);
				top = top->right;
			}
		}
		std::cout << '\n';
	}
	/// ������� ������� �� ��� ��������
	void erase(T data)
	{
		if (m_root == nullptr)
		{
			return;
		}
		auto current = m_root;
		while (current != nullptr)
		{
			if (current->data == data)
			{
				deleteNode(current);
				return;
			}
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

private:
	/// <summary>
	/// ����� ���  �������������� �������
	/// </summary>
	void printLKPAuxiliary(Node* current)
	{
		if (current == nullptr)
			return;
		printLKPAuxiliary(current->left);
		std::cout << current->data << ' ';
		printLKPAuxiliary(current->right);
	}


	void deleteNode(Node* current)
	{
		if (current == nullptr) return;
		if (current->left == nullptr && current->right == nullptr)
		{
			if (current->parent->right == current)
				current->parent->right = nullptr;
			if (current->parent->left == current)
				current->parent->left = nullptr;
			delete current;

		}
		else if (current->left == nullptr || current->right == nullptr)
		{
			deleteParentWithOneSon(current);
		}
		else
		{
			Node* extremeNode = current;
			extremeNode = extremeNode->left;
			while (extremeNode->right != nullptr)
				extremeNode = extremeNode->right;

			std::swap(extremeNode->left, current->left);
			std::swap(extremeNode->parent, current->parent);
			extremeNode->right = current->right;
			current->right = nullptr;

			if (extremeNode->parent->right == current) //�������� �� ����� ������� current  ���� ��������
				extremeNode->parent->right = extremeNode;
			if (extremeNode->parent->left == current)
				extremeNode->parent->left = extremeNode;

			if (current->parent->right == extremeNode) //�������� �� ����� ������� extremeNode  ���� ��������
				current->parent->right = current;
			if (current->parent->left == extremeNode)
				current->parent->left = current;
			deleteParentWithOneSon(current);
		}
	}


	/// �������������� ��� deleteNode, ������� ���� � ����� ��������	
	void deleteParentWithOneSon(Node*& current)
	{
		auto x = current;
		if (current->left != nullptr)          //��������, ���� ����� ���� �����
		{
			current->left->parent = current->parent;
			changedParentWhileDelete(current, current->left);
		}
		if (current->right != nullptr)  		//��������, ���� ������ ���� �����
		{
			current->right->parent = current->parent;
			changedParentWhileDelete(current, current->left);
		}
		delete x;
	}

	/// <summary>
	/// �������������� ��� deleteNode
	/// </summary>
	/// <param name="d_curentSon">����������, �������� ������� ����������</param>
	void changedParentWhileDelete(Node*& d_current, Node*& d_curentSon)
	{
		if (d_current->parent->left == d_current)	 //���� �������, ����� ���
			d_current->parent->left = d_curentSon;

		if (d_current->parent->right == d_current)	 //���� �������, ������ ���
			d_current->parent->right = d_curentSon;
	}
};
