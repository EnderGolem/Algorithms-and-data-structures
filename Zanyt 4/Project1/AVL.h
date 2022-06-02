#pragma once
#include <algorithm>
#include <iostream>
#include <queue>


template<typename T, class Compare = std::less<T>, class Allocator = std::allocator<T>>
class AVL
{
private:
	struct  Node
	{
		T data;
		Node* parent, * left, * right;
		unsigned char height;
		Node(T data, Node* parent, Node* left, Node* right, unsigned char height) : data(data), parent(parent), left(left), right(right), height(height)
		{

		}
	};

public:
	using AllocType = typename std::allocator_traits<Allocator>::template rebind_alloc < Node >;
	AllocType Alc;
	using key_type = T;
	using key_compare = Compare;
	using value_compare = Compare;
	using value_type = T;
	using allocator_type = AllocType;
	using size_type = size_t;
	using difference_type = size_t;
	using pointer = T*;
	using const_pointer = const pointer;
	using reference = value_type&;
	using const_reference = const value_type&;
	//using iterator = typename _Mybase::iterator;   //  Не нужно! Явно определили iterator внутри данного класса
	class iterator;   //  Предварительное объявление класса iterator, т.к. он определён ниже
	using const_iterator = iterator;
	using reverse_iterator = std::reverse_iterator<iterator>;
	using const_reverse_iterator = std::reverse_iterator<const_iterator>;
	Compare cmp = Compare();


private:
	Node* make_fictive()
	{
		m_fictive = Alc.allocate(1);
		std::allocator_traits<AllocType>::construct(Alc, &(m_fictive->parent));
		m_fictive->parent = nullptr;
		std::allocator_traits<AllocType>::construct(Alc, &(m_fictive->left));
		m_fictive->left = m_fictive;
		std::allocator_traits<AllocType>::construct(Alc, &(m_fictive->right));
		m_fictive->right = m_fictive;
		m_fictive->height = 0;
		//  Возвращаем указатель на созданную вершину
		return m_fictive;
	}
	void delete_fictive(Node* node) {
		if (node != m_fictive)
			std::allocator_traits<AllocType>::destroy(Alc, &(node->parent));
		std::allocator_traits<AllocType>::destroy(Alc, &(node->left));
		std::allocator_traits<AllocType>::destroy(Alc, &(node->right));
		std::allocator_traits<AllocType>::deallocate(Alc, node, 1);
	}
	Node* m_fictive;
	size_t m_size;
	int m_count_rotate;
public:
	//static int iteratorBinaryTree; возможно можно удалить...
	class iterator
	{
		friend  class AVL;
	protected:
		Node* m_node;
		//TODO It would be possible to get rid of it somehow, but I do not know
		Node* it_fictive;

		Node*& _data()
		{
			return m_node;
		}

	public:
		//  Определяем стандартные типы в соответствии с требованиями стандарта к двунаправленным итераторам
		using iterator_category = std::bidirectional_iterator_tag;
		using value_type = AVL::value_type;
		using difference_type = AVL::difference_type;
		using pointer = AVL::pointer;
		using reference = AVL::reference;
		iterator(Node* _node, Node* _fictive) : m_node(_node), it_fictive(_fictive)
		{
		}
		const T& operator*() const
		{
			return m_node->data;
		}
		iterator operator++()
		{
			if (m_node == it_fictive)
			{
				m_node = it_fictive->left;
				return *this;
			}
			if (m_node == it_fictive->right)
			{
				m_node = it_fictive;
				return *this;
			}
			if (m_node->right != it_fictive)
			{
				m_node = m_node->right;
				//if (m_node == it_fictive)
				// return  *this;
				while (m_node->left != it_fictive)
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
		iterator operator++(int)
		{
			auto t = *this;
			++* this;
			return t;
		}

		iterator operator--()
		{
			if (m_node == it_fictive)
			{
				m_node = it_fictive->right;
				return *this;
			}
			if (m_node == it_fictive->left)
			{
				m_node = it_fictive;
				return *this;
			}
			if (m_node->left != it_fictive)
			{
				m_node = m_node->left;
				//if (m_node == it_fictive)
				// return  *this;
				while (m_node->right != it_fictive)
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
		iterator operator--(int)
		{
			auto t = *this;
			--* this;
			return t;
		}
		friend bool operator== (const iterator& it_1, const iterator& it_2)
		{
			return it_1.m_node == it_2.m_node;
		}

		friend bool operator!= (const iterator& it_1, const iterator& it_2)
		{
			return !(it_1 == it_2);
		}

		//  Эти операции не допускаются между прямыми и обратными итераторами
		const iterator& operator=(const reverse_iterator& it) = delete;
		bool operator==(const reverse_iterator& it) = delete;
		bool operator!=(const reverse_iterator& it) = delete;
		iterator(const reverse_iterator& it) = delete;
	};
	iterator begin() const noexcept { return iterator(m_fictive->left, m_fictive); }
	iterator end() const noexcept { return iterator(m_fictive, m_fictive); }
	reverse_iterator rbegin() const noexcept { return reverse_iterator(iterator(m_fictive->right, m_fictive)); }
	reverse_iterator rend() const noexcept { return reverse_iterator(iterator(m_fictive, m_fictive)); }
	AVL() : m_size(0)
	{
		make_fictive();
	}
	AVL(std::initializer_list<T> lst) : m_size(0)
	{
		make_fictive();
		for (auto x : lst)
		{
			this->insert(x);
		}
	}
	AVL(const AVL<T>& avl)
	{
		make_fictive();
		for (auto it = avl.begin(); it != avl.end(); ++it)
			insert(*it);
	}
	AVL(AVL<T>&& avl) : m_size(avl.m_size)
	{
		m_fictive = avl.m_fictive;
		avl.m_fictive = nullptr;
	}
	AVL(const key_compare& key) : m_size(0)
	{
		cmp = key;
		make_fictive();
	}
	AVL(const key_compare& key, const allocator_type all) : m_size(0)
	{
		cmp = key;
		Alc = all;
		make_fictive();
	}
private:
	template <class RandomIterator>
	void ordered_insert(RandomIterator first, RandomIterator last, iterator position) {
		if (first >= last) return;
		RandomIterator center = first + (last - first) / 2;
		iterator new_pos = insert(position, *center);  //  итератор на вставленный элемент
		ordered_insert(first, center, position);
		ordered_insert(center + 1, last, ++position);
	}
public:
	template <class InputIterator>
	AVL(InputIterator first, InputIterator last, Compare comparator = Compare(), AllocType alloc = AllocType()) : m_fictive(make_fictive()), m_size(0), cmp(comparator), Alc(alloc)
	{
		cmp = comparator;
		Alc = alloc;
		for (auto fi = first; fi != last; ++fi)
		{
			insert(*fi);
		}
	}
	std::pair<iterator, bool>  insert(T k)
	{
		if (m_fictive->parent == nullptr)
		{
			m_size++;
			m_fictive->parent = new Node{ k ,nullptr,m_fictive,m_fictive, 0 };
			m_fictive->left = m_fictive->parent;
			m_fictive->right = m_fictive->parent;
			return { iterator(m_fictive->parent,m_fictive), true };
		}
		else {
			auto r = insert(m_fictive->parent, k);
			if (r.second) {
				m_size++;
				return { ++r.first,r.second };
			}
			return  { r.first,r.second };
		}
	}
	template <class InputIterator>
	void insert(InputIterator first, InputIterator last)
	{
		for (auto fi = first; fi != last; ++fi)
		{
			insert(*fi);
		}
	}
	iterator  insert(iterator hint, T k)
	{
		if (m_fictive->parent == nullptr)
		{
			m_size++;
			m_fictive->parent = new Node{ k ,nullptr,m_fictive,m_fictive, 0 };
			m_fictive->left = m_fictive->parent;
			m_fictive->right = m_fictive->parent;
			return  iterator(m_fictive->parent, m_fictive);
		}
		else {
			auto r = insert(m_fictive->parent, k);
			if (r.second)
				m_size++;
			return ++r.first;
		}
	}

	int erase(T data)
	{
		if (m_fictive->parent == nullptr)
		{
			return 0;
		}
		auto next = iterator(m_fictive->parent, m_fictive);
		auto current = m_fictive->parent;
		std::deque< Node*  > qu;
		while (current != m_fictive)
		{
			qu.push_back(current);
			if (current->data == data)
			{
				next = erase_node(current);
				break;
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

		while (qu.empty())
		{
			balance(qu.back());
			qu.pop_back();
		}
		if (next == begin())
			return  0;
		m_size--;
		return  1;
	}

	template <class InputIterator>
	iterator erase(InputIterator itr)
	{
		m_size--;
		auto d = erase_node(itr.m_node);
		auto g = d.m_node;
		while (g->parent != nullptr)
		{
			balance(g);
			g = g->parent;
		}
		return  d;
	}
	template <class InputIterator>
	iterator erase(InputIterator first, InputIterator last)
	{
		auto next = last;
		for (auto it = first; it != last; )
		{
			auto dop = it;
			++it;
			erase(dop);
		}
		return  next;
	}
	void print() const
	{
		for (auto it = begin(); it != end(); ++it)
		{
			std::cout << *it << ' ';
		}
		std::cout << " End \n";
	}

	void printWithHeights() const
	{
		for (auto it = begin(); it != end(); ++it)
		{
			std::cout << "[" << *it << " " << int(it.m_node->height) << "]" << ' ';
		}
		std::cout << " End \n";
	}
	void printByLevels() const
	{
		if (m_fictive->parent == nullptr)
		{
			std::cout << "null\n"; return;;
		}
		std::queue<std::pair<Node*, int>> queue;
		int level = 0;
		queue.push(std::make_pair(m_fictive->parent, level));
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
			if (x.first->left != m_fictive)
			{
				queue.push(std::make_pair(x.first->left, x.second + 1));
			}
			if (x.first->right != m_fictive)
			{
				queue.push(std::make_pair(x.first->right, x.second + 1));
			}
		}
		std::cout << " End" << '\n';
	}

	bool contains(T data) const
	{
		return end() != generalBound(data, [](T x, T y)->bool {return  x == y; });
	}
	iterator find(T data) const
	{
		return generalBound(data, [](T x, T y)->bool {return  x == y; });
	}
	int count(T data) const
	{
		if (contains(data))
			return 1;
		return 0;
	}
	iterator lowerBound(T data) const
	{

		for (auto it = begin(); it != end(); ++it)
		{
			if (!cmp(*it, data))
			{
				return it;
			}
		}
		return end();
	}
	iterator upperBound(T data) const
	{
		auto it = lowerBound(data);
		if (it != end() && *it == data)
			++it;
		return  it;
	}
	std::pair<const_iterator, const_iterator> equal_range(T data) const
	{
		return { lowerBound(data), upperBound(data) };
	}
	void swap(AVL& avl)
	{
		std::swap(avl, *this);
	}
	size_t size()
	{
		return  m_size;
	}
	bool empty()
	{
		return  m_size == 0;
	}
	std::allocator<T> get_allocator()
	{
		return Alc;
	}
	Compare key_comp()
	{
		return cmp;
	}
	Compare value_comp()
	{
		return cmp;
	}
	int get_count_rotate()
	{
		return m_count_rotate;
	}
	void clear_rotate()
	{
		m_count_rotate = 0;
	}
	void clear() {
		m_size = 0;
		m_count_rotate = 0;
		if (m_fictive == nullptr)
			return;
		Free_nodes(m_fictive->parent);
		m_fictive->parent = m_fictive->left = m_fictive->right = m_fictive;
		m_fictive->parent = nullptr;
	}

	friend bool operator== (const AVL<T>& tree_1, const AVL<T>& tree_2)
	{
		auto i = tree_1.begin(), ii = tree_2.begin();
		for (; (i != tree_1.end()) && (ii != tree_2.end()); ++i, ++ii)
		{
			if (*i != *ii)
				return false;
		}
		return i == tree_1.end() && ii == tree_2.end();
	}
private:
	unsigned char height(Node* p)
	{
		return p ? p->height : 0;
	}
	int bfactor(Node* p)
	{
		return height(p->right) - height(p->left);
	}
	void fixheight(Node* p)
	{
		unsigned char hl = height(p->left);
		unsigned char hr = height(p->right);
		p->height = (hl > hr ? hl : hr) + 1;
	}
	void fixroot()
	{
		while (m_fictive->parent->parent != nullptr)
		{
			m_fictive->parent = m_fictive->parent->parent;
		}
	}
	iterator rotateright(Node* p)
	{
		m_count_rotate++;
		Node* q = p->left;
		p->left = q->right;
		//Change parent
		q->right->parent = p;
		q->right = p;
		//Change parent
		q->parent = p->parent;
		p->parent = q;

		fixheight(p);
		fixheight(q);
		fixroot();
		return iterator(q, m_fictive);
	}
	iterator rotateleft(Node* q)
	{
		m_count_rotate++;
		Node* p = q->right;
		q->right = p->left;

		p->left->parent = q;
		p->left = q;

		p->parent = q->parent;
		q->parent = p;

		fixheight(q);
		fixheight(p);
		fixroot();
		return iterator(p, m_fictive);
	}
	iterator balance(Node* p)
	{
		fixheight(p);
		int h = bfactor(p);
		if (h == 2)
		{
			if (bfactor(p->right) < 0)
				p->right = rotateright(p->right).m_node;
			return rotateleft(p);
		}
		if (h == -2)
		{
			if (bfactor(p->left) > 0)
				p->left = rotateleft(p->left).m_node;
			return rotateright(p);
		}
		return iterator(p, m_fictive);
	}

	std::pair<iterator, bool> insert(Node* p, T k)
	{
		std::pair<iterator, bool> dop = { begin(), true };
		if (cmp(k, p->data))
			if (p == m_fictive->left) {
				p->left = new Node(k, p, m_fictive, m_fictive, 1);
				m_fictive->left = p->left;
			}
			else
				if (p->left == m_fictive)
					p->left = new Node(k, p, m_fictive, m_fictive, 1);
				else {
					dop = insert(p->left, k);
					p->left = dop.first.m_node;
				}
		else if (!cmp(k, p->data) && p->data != k) //VASHO
			if (p == m_fictive->right) {
				p->right = new Node(k, p, m_fictive, m_fictive, 1);
				m_fictive->right = p->right;
			}
			else
				if (p->right == m_fictive)
					p->right = new Node(k, p, m_fictive, m_fictive, 1);
				else {
					dop = insert(p->right, k);
					p->right = dop.first.m_node;
				}
		else if (k == p->data)
		{
			return { balance(p),false };
		}
		return { balance(p), dop.second };
	}
	iterator deleteNodeWithoutSon(Node* current)
	{
		if (current == m_fictive->parent) {
			m_fictive->parent = nullptr;
			m_fictive->left = m_fictive;
			m_fictive->right = m_fictive;
			return begin();
		}
		auto next = iterator(current, m_fictive);
		++next;
		if (current->parent->right == current)
			current->parent->right = m_fictive;
		else
			current->parent->left = m_fictive;
		//Check if current end by m_fictive
		if (m_fictive->left == current) {
			m_fictive->left = current->parent;
			current->parent->left = m_fictive;
		}
		if (m_fictive->right == current) {
			m_fictive->right = current->parent;
			current->parent->right = m_fictive;
		}
		delete_node(current);
		current = nullptr;
		return next;
	}
	void changedParentWhileDelete(Node*& d_current, Node*& d_currentSon)
	{
		//Change son
		if (d_current != m_fictive->parent) {
			if (d_current->parent->left == d_current)
				d_current->parent->left = d_currentSon;
			else
				d_current->parent->right = d_currentSon;
		}
		//Change m_fictive TODO
		if (m_fictive->left == d_current)
			m_fictive->left = d_current->parent;
		if (m_fictive->right == d_current)
			m_fictive->right = d_current->parent;
	}
	iterator deleteParentWithOneSon(Node*& current)
	{
		Node* root = m_fictive->parent;
		auto next = iterator(current, m_fictive);
		++next;
		if (current->left != m_fictive)
		{
			if (current != root)
				current->left->parent = current->parent;
			changedParentWhileDelete(current, current->left);
			if (current == root)
				root = current->left;

		}
		if (current->right != m_fictive)
		{
			if (current != root)
				current->right->parent = current->parent;
			changedParentWhileDelete(current, current->right);
			if (current == root)
				root = current->right;
		}
		delete_node(current);
		current = nullptr;
		return  next;
	}

	iterator erase_node(Node* current)
	{
		if (current == m_fictive) return begin();
		if (current->left == m_fictive && current->right == m_fictive)
		{
			return  deleteNodeWithoutSon(current);
		}
		else if (current->left == m_fictive || current->right == m_fictive)
		{
			return  deleteParentWithOneSon(current);
		}
		else
		{
			Node* root = m_fictive->parent;
			Node* extremeNode = current;
			extremeNode = extremeNode->left;
			while (extremeNode->right != m_fictive)
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
				current->right = m_fictive;

			}
			else {
				std::swap(extremeNode->left, current->left);

				if (current == root) {
					current->parent = extremeNode->parent;
					extremeNode->parent = nullptr;
				}
				else
					std::swap(extremeNode->parent, current->parent);
				extremeNode->right = current->right;
				current->right = m_fictive;
			}


			//Change parent son
			if (extremeNode->parent != nullptr)
				if (extremeNode->parent->right == current)
					extremeNode->parent->right = extremeNode;
				else
					extremeNode->parent->left = extremeNode;

			if (current->parent->right == extremeNode)
				current->parent->right = current;
			if (current->parent->left == extremeNode)
				current->parent->left = current;

			if (current == root)
			{
				root = extremeNode;
			}
			if (extremeNode == m_fictive->left)
				m_fictive->left = current;
			//Delete if current is leaf or has one son.
			if (current->left == m_fictive && current->right == m_fictive)
			{
				deleteNodeWithoutSon(current);
			}
			else if (current->left == m_fictive || current->right == m_fictive)
			{
				deleteParentWithOneSon(current);
			}
			return  iterator(extremeNode, m_fictive);
		}
	}
	iterator generalBound(T data, bool(*compare)(T, T)) const
	{
		if (m_fictive->parent == nullptr)
		{
			return  end();
		}
		auto current = m_fictive->parent;
		while (current != m_fictive)
		{
			if (compare(current->data, data))
				return iterator(current, m_fictive);
			if (current->data > data)
			{
				current = current->left;
			}
			else
			{
				current = current->right;
			}
		}
		return  end();
	}


	void delete_node(Node* node) {

		std::allocator_traits<AllocType>::destroy(Alc, &(node->data));
		delete_fictive(node);
	}
	void Free_nodes(Node* node)
	{
		if (node != nullptr && node != m_fictive)
		{
			Free_nodes(node->left);
			Free_nodes(node->right);
			delete_node(node);
		}
	}
public:
	AVL<T>& operator=(const AVL<T>& avl)
	{
		clear();
		m_fictive->parent = nullptr;
		for (auto it = avl.begin(); it != avl.end(); ++it)
			insert(*it);
		return *this;
	}
	AVL<T>& operator=(AVL<T>&& avl)
	{
		clear();
		m_size = avl.m_size;
		m_fictive = avl.m_fictive;
		avl.m_fictive = nullptr;
		return *this;
	}

	~AVL()
	{
		if (m_fictive != nullptr)
			clear();
		delete_fictive(m_fictive);
	}
};


template <class Key, class Compare, class Allocator>
bool operator==(const AVL<Key, Compare, Allocator>& x, const AVL<Key, Compare, Allocator>& y) {
	typename AVL<Key, Compare, Allocator>::const_iterator it1{ x.begin() }, it2{ y.begin() };
	while (it1 != x.end() && it2 != y.end() && *it1 == *it2) {
		++it1; ++it2;
	}

	return it1 == x.end() && it2 == y.end();
}

template <class Key, class Compare, class Allocator>
bool operator<(const AVL<Key, Compare, Allocator>& x, const AVL<Key, Compare, Allocator>& y) {

	typename AVL<Key, Compare, Allocator>::const_iterator it1{ x.begin() }, it2{ y.begin() };
	while (it1 != x.end() && it2 != y.end() && *it1 == *it2) {
		++it1; ++it2;
	}

	if (it1 == x.end())
		return it2 != y.end();

	return it2 != y.end() && *it1 < *it2;
}

template <class Key, class Compare, class Allocator>
bool operator!=(const AVL<Key, Compare, Allocator>& x, const AVL<Key, Compare, Allocator>& y) {
	return !(x == y);
}

template <class Key, class Compare, class Allocator>
bool operator>(const AVL<Key, Compare, Allocator>& x, const AVL<Key, Compare, Allocator>& y) {
	return y < x;
}

template <class Key, class Compare, class Allocator>
bool operator>=(const AVL<Key, Compare, Allocator>& x, const AVL<Key, Compare, Allocator>& y) {
	return !(x < y);
}

template <class Key, class Compare, class Allocator>
bool operator<=(const AVL<Key, Compare, Allocator>& x, const AVL<Key, Compare, Allocator>& y) {
	return   !(y < x);
}