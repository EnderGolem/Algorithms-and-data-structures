#pragma once
#include <iostream>
#include <stack> 
#include <queue>
using namespace  std;
template<class  T>
class  BinaryTree
{
private:
	struct  Node
	{
		T data;
		Node* parent, * left, * right;
	};
	Node* m_root;
	class iteratorBinaryTree
	{
	private:
		Node* m_node;
	public:
		using difference_type = size_t;
		using value_type = T;
		using pointer = T*;
		using reference = T&;
		using iterator_category = std::bidirectional_iterator_tag;
		iteratorBinaryTree(Node* node) : m_node(node) {}
		T& operator*() { return  m_node->data; }
		iteratorBinaryTree operator++()
		{			
			if (m_node->right != nullptr)
			{
				m_node = m_node->right;
				while (m_node->left != nullptr)
				{
					m_node = m_node->left;
				}
				return *this;
			}

			while (m_node->parent->right == m_node)
			{
				m_node = m_node->parent;
			}

			if (m_node == m_node->parent->left)
			{
				m_node = m_node->parent;
				return *this;
			}
		}
		iteratorBinaryTree  operator++(int)
		{
			auto t = *this;
			++*this;
			return t;
		}
		iteratorBinaryTree operator--()
		{
			if (m_node->left != nullptr)
			{
				m_node = m_node->left;
				while (m_node->right != nullptr)
				{
					m_node = m_node->right;
				}
				return *this;
			}

			while (m_node->parent->left == m_node)
			{
				m_node = m_node->parent;
			}

			if (m_node == m_node->parent->right)
			{
				m_node = m_node->parent;
				return *this;
			}
		}
		iteratorBinaryTree  operator--(int)
		{
			auto t = *this;
			--* this;
			return t;
		}
		friend bool operator==(iteratorBinaryTree v1, iteratorBinaryTree v2) {
			return v1.m_node->data == v2.m_node->data;
		}
		friend bool operator!=(iteratorBinaryTree v1, iteratorBinaryTree v2) {
			return !(v1 == v2);
		}
	};
public:

	iteratorBinaryTree first()
	{
		auto r = m_root;
		while (r->left != nullptr)
			r = r->left;
		return iteratorBinaryTree(r);
	}
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
	/// Проверка на содержание в дереве
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
	/// Для сравнения по своему усмотрению
	/// </summary>
	/// <param name="compare">Функция сравнения</param>
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
	/// Вывод ЛКП 
	/// </summary>
	void printLKP()
	{
		printLKPAuxiliary(m_root);
		std::cout << '\n';
	}
	/// <summary>
	/// Вывод ПКЛ
	/// </summary>
	void printPKL()
	{
		if (m_root == nullptr)
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

	/// Выводит дерево по слоям/уровням
	void printByLevels()
	{
		if (m_root == nullptr)
		{
			std::cout << "null\n"; return;;
		}
		std::queue<std::pair<Node*, int>> queue;
		int level = 0;
		queue.push(std::make_pair(m_root, level));
		while (!queue.empty())
		{
			if (queue.front().second != level)
			{
				level++;
				std::cout << '\n';
			}
			auto x = queue.front();
			queue.pop();
			std::cout << x.first->data << ' ';
			if (x.first->left != nullptr)
			{
				queue.push(std::make_pair(x.first->left, x.second + 1));
			}
			if (x.first->right != nullptr)
			{
				queue.push(std::make_pair(x.first->right, x.second + 1));
			}
		}
		std::cout << '\n';
	}
	/// Удаляет элемент по его значению
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

	/// Сравнение с другим деревом
	bool equalTo(BinaryTree<T>& bt)
	{
		return equalTo(this->m_root, bt.m_root);
	}
private:

	/// Сравнение двух узлов
	bool equalTo(Node*& x, Node*& y)
	{
		if (x == nullptr && y == nullptr)
			return  true;
		if (x == nullptr || y == nullptr)
			return  false;
		return  (x->data == y->data) && equalTo(x->left, y->left) && equalTo(x->right, y->right);
	}
	/// <summary>
	/// Вывод ЛКП  дополнительная функция
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

			if (extremeNode->parent->right == current) //Проверка по какой стороне current  была потомком
				extremeNode->parent->right = extremeNode;
			if (extremeNode->parent->left == current)
				extremeNode->parent->left = extremeNode;

			if (current->parent->right == extremeNode) //Проверка по какой стороне extremeNode  была потомком
				current->parent->right = current;
			if (current->parent->left == extremeNode)
				current->parent->left = current;
			deleteParentWithOneSon(current);
		}
	}


	/// Вспомогательня для deleteNode, удаляет Ноду с одним потомком	
	void deleteParentWithOneSon(Node*& current)
	{
		auto x = current;
		if (current->left != nullptr)          //Удаление, если левый узел занят
		{
			current->left->parent = current->parent;
			changedParentWhileDelete(current, current->left);
		}
		if (current->right != nullptr)  		//Удаление, если правый узел занят
		{
			current->right->parent = current->parent;
			changedParentWhileDelete(current, current->left);
		}
		delete x;
	}

	/// <summary>
	/// Вспомогательня для deleteNode
	/// </summary>
	/// <param name="d_curentSon">Переменная, хранящая занятую переменную</param>
	void changedParentWhileDelete(Node*& d_current, Node*& d_curentSon)
	{
		if (d_current->parent->left == d_current)	 //Если текущий, левый сын
			d_current->parent->left = d_curentSon;

		if (d_current->parent->right == d_current)	 //Если текущий, правый сын
			d_current->parent->right = d_curentSon;
	}
};
