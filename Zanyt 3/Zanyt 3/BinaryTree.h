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
	Node* m_fictive;
	class iteratorBinaryTree
	{
	private:
		Node* m_node;
		Node* it_fictive;
	public:
		using difference_type = size_t;
		using value_type = T;
		using pointer = T*;
		using reference = T&;
		using iterator_category = std::bidirectional_iterator_tag;
		iteratorBinaryTree(Node* node, Node* fictive) : m_node(node), it_fictive(fictive) {}
		T& operator*() { return  m_node->data; }
		iteratorBinaryTree operator++()
		{
			if (m_node == it_fictive)
			{
				m_node = it_fictive->left;
				return *this;
			}
			if (m_node->right != nullptr)
			{
				m_node = m_node->right;
				if (m_node == it_fictive)
					return  *this;
				while (m_node->left != nullptr && m_node->left != it_fictive)
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
			++* this;
			return t;
		}
		iteratorBinaryTree operator--()
		{
			if (m_node == it_fictive)
			{
				m_node = it_fictive->right;
				return *this;
			}
			if (m_node->left != nullptr && m_node->left != it_fictive)
			{
				m_node = m_node->left;
				if (m_node == it_fictive)
					return  *this;
				while (m_node->right != nullptr && m_node->right != it_fictive)
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
			return v1.m_node == v2.m_node;
		}
		friend bool operator!=(iteratorBinaryTree v1, iteratorBinaryTree v2) {
			return !(v1 == v2);
		}
	};
public:
	iteratorBinaryTree begin()
	{
		auto r = m_root;
		while (r->left != nullptr && r->left != m_fictive)
			r = r->left;
		return iteratorBinaryTree(r, m_fictive);
	}
	iteratorBinaryTree end()
	{
		return iteratorBinaryTree(m_fictive, m_fictive);
	}
	iteratorBinaryTree first()
	{
		auto r = m_root;
		while (r->left != nullptr && r->left != m_fictive)
			r = r->left;
		return iteratorBinaryTree(r, m_fictive);
	}
	BinaryTree() : m_root(nullptr)
	{
		void* place = operator new(sizeof(Node)); // Выделяем память под фиктивную вершину без вызова конструктора
		m_fictive = static_cast<Node*>(place); // Получаем указатель на фиктивную вершину
		m_fictive->left = m_fictive;
		m_fictive->right = m_fictive;
	}
	BinaryTree(initializer_list<T> lst) : m_root(nullptr)
	{
		void* place = operator new(sizeof(Node)); // Выделяем память под фиктивную вершину без вызова конструктора
		m_fictive = static_cast<Node*>(place); // Получаем указатель на фиктивную вершину
		m_fictive->left = m_fictive;
		m_fictive->right = m_fictive;
		for (auto x : lst)
		{
			this->insert(x);
		}
	}
	void insert(T data)
	{
		if (m_root == nullptr)
		{
			m_root = new Node{ data,nullptr,m_fictive,m_fictive };
			m_fictive->left = m_root;
			m_fictive->right = m_root;

			return;
		}
		auto current = m_root;
		while (current != nullptr)
		{
			if (current->data > data) {
				if (current->left == m_fictive)
				{
					current->left = new Node{ data,current, m_fictive,nullptr };
					m_fictive->left = current->left;
					return;
				}
				if (current->left == nullptr) {
					current->left = new Node{ data,current,nullptr,nullptr };
					return;
				}
				current = current->left;
			}
			else
			{
				if (current->right == m_fictive)
				{
					current->right = new Node{ data,current,nullptr ,m_fictive };
					m_fictive->right = current->right;
					return;
				}
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
		while (current->right != nullptr && current->right != m_fictive)
			current = current->right;
		return  current->data;
	}
	T minElement()
	{
		auto current = m_root;
		while (current->left != nullptr && current->left != m_fictive)
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
		while (current != nullptr && current != m_fictive)
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
	void printLKP() const
	{
		printLKPAuxiliary(m_root);
		std::cout << " End" << '\n';
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
				if (top->left != nullptr && top->left != m_fictive)
					top = top->left;
				else
					top = nullptr;
			}
			while (top != nullptr && top != m_fictive)
			{
				stack.push(top);
				top = top->right;
			}
		}
		std::cout << " End\n";
	}

	/// Выводит дерево по слоям/уровням
	void printByLevels() const
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
			if (x.first->left != nullptr && x.first->left != m_fictive)
			{
				std::cout << (x.first->left == nullptr) << '\n';
				queue.push(std::make_pair(x.first->left, x.second + 1));
			}
			if (x.first->right != nullptr && x.first->right != m_fictive)
			{
				queue.push(std::make_pair(x.first->right, x.second + 1));
			}
		}
		std::cout << " End" << '\n';
	}
	/// Удаляет элемент по его значению
	void erase(T data)
	{
		if (m_root == nullptr)
		{
			return;
		}
		auto current = m_root;
		while (current != nullptr && current != m_fictive)
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
		return equalTo(this->m_root, bt.m_root, bt.m_fictive);
	}
private:

	/// Сравнение двух узлов
	bool equalTo(Node*& x, Node*& y, Node*& y_fictive)
	{
		if ((x == nullptr || x == m_fictive) && (y == nullptr || y == y_fictive))
			return  true;
		if (x == nullptr || y == nullptr || x == m_fictive || y == y_fictive)
			return  false;
		return  (x->data == y->data) && equalTo(x->left, y->left, y_fictive) && equalTo(x->right, y->right, y_fictive);
	}
	/// <summary>
	/// Вывод ЛКП  дополнительная функция
	/// </summary>
	void printLKPAuxiliary(Node* current) const
	{
		if (current == nullptr || current == m_fictive)
			return;
		printLKPAuxiliary(current->left);
		std::cout << current->data << ' ';
		printLKPAuxiliary(current->right);
	}


	void deleteNode(Node* current)
	{
		if (current == nullptr && current == m_fictive) return;

		//Delete if node is leaf
		if ((current->left == nullptr || current->left == m_fictive) && (current->right == nullptr || current->right == m_fictive))
		{
			deleteNodeWithoutSon(current);

		}
		else if (current->left == nullptr || current->right == nullptr || current->left == m_fictive || current->right == m_fictive)
		{
			deleteParentWithOneSon(current);
		}
		else
		{
			Node* extremeNode = current;
			extremeNode = extremeNode->left;
			while (extremeNode->right != nullptr /* || extremeNode->right != m_fictive*/) //Вторая проверка предположительно не нужна
				extremeNode = extremeNode->right;

			//Change son
			if (current->left == extremeNode) //if we swap the direct son and parent
			{
				auto x = extremeNode->left;
				extremeNode->left = current;
				current->left = x;

				extremeNode->parent = current->parent;
				current->parent = extremeNode;
				extremeNode->right = current->right;
				current->right = nullptr;

			}
			else {
				std::swap(extremeNode->left, current->left);

				if (current == m_root) {
					current->parent = extremeNode->parent;
					extremeNode->parent = nullptr;
				}
				else
					std::swap(extremeNode->parent, current->parent);
				extremeNode->right = current->right;
				current->right = nullptr;
			}


			//Change parent son
			if (extremeNode->parent != nullptr)
				if (extremeNode->parent->right == current) //Проверка по какой стороне current  была потомком
					extremeNode->parent->right = extremeNode;
				else
					extremeNode->parent->left = extremeNode;

			if (current->parent->right == extremeNode) //Проверка по какой стороне extremeNode  была потомком
				current->parent->right = current;
			if (current->parent->left == extremeNode)
				current->parent->left = current;

			if (current == m_root)
			{
				m_root = extremeNode;
			}
			if (extremeNode == m_fictive->left)
				m_fictive->left = current;
			//Delete if current is leaf or has one son.
			if ((current->left == nullptr || current->left == m_fictive) && (current->right == nullptr || current->right == m_fictive))
			{
				deleteNodeWithoutSon(current);
			}
			else if (current->left == nullptr || current->right == nullptr || current->left == m_fictive || current->right == m_fictive)
			{
				deleteParentWithOneSon(current);
			}
		}
	}

	/// Extract methods for deleteNode, delete node with zero childern
	void deleteNodeWithoutSon(Node* current)
	{
		if (current == m_root) {
			m_root = nullptr;
			m_fictive->left = m_fictive;
			m_fictive->right = m_fictive;
			return;
		}

		if (current->parent->right == current)
			current->parent->right = nullptr;
		else
			current->parent->left = nullptr;
		//Check if current end by m_fictive
		if (m_fictive->left == current) {
			m_fictive->left = current->parent;
			current->parent->left = m_fictive;
		}
		if (m_fictive->right == current) {
			m_fictive->right = current->parent;
			current->parent->right = m_fictive;
		}

		delete current;
		current = nullptr;
	}


	/// Вспомогательня для deleteNode, удаляет Ноду с одним потомком	
	void deleteParentWithOneSon(Node*& current)
	{
		if (current->left != nullptr && current->left != m_fictive)          //Удаление, если левый узел занят
		{
			if (current != m_root)
				current->left->parent = current->parent;
			changedParentWhileDelete(current, current->left);
			if (current == m_root)
				m_root = current->left;

		}
		if (current->right != nullptr && current->right != m_fictive)  		//Удаление, если правый узел занят
		{
			if (current != m_root)
				current->right->parent = current->parent;
			changedParentWhileDelete(current, current->right);
			if (current == m_root)
				m_root = current->right;

		}
		delete current;
		current = nullptr;
	}

	/// <summary>
	/// Вспомогательня для deleteNodе
	/// </summary>
	/// <param name="d_currentSon">Переменная, хранящая занятую переменную</param>
	void changedParentWhileDelete(Node*& d_current, Node*& d_currentSon)
	{
		//Change son
		if (d_current != m_root) {
			if (d_current->parent->left == d_current)	 //Если текущий, левый сын
				d_current->parent->left = d_currentSon;
			else										//Если текущий, правый сын
				d_current->parent->right = d_currentSon;
		}
		//Change m_fictive 
		if (m_fictive->left == d_current)
			m_fictive->left = d_current->parent;
		if (m_fictive->right == d_current)
			m_fictive->right = d_current->parent;
	}
};
