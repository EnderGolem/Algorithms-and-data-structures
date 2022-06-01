#pragma once
#include <algorithm>
#include <iostream>






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
		// Выделяем память по размеру узла без конструирования
		m_fictive = Alc.allocate(1);
		//  Все поля, являющиеся указателями на узлы (left, right, parent) инициализируем и обнуляем
		std::allocator_traits<AllocType>::construct(Alc, &(m_fictive->parent));
		m_fictive->parent = nullptr;
		std::allocator_traits<AllocType>::construct(Alc, &(m_fictive->left));
		m_fictive->left = m_fictive;
		std::allocator_traits<AllocType>::construct(Alc, &(m_fictive->right));
		m_fictive->right = m_fictive;
		//  Возвращаем указатель на созданную вершину
		return m_fictive;
	}
	Node* m_fictive;
	size_t m_size;
public:
	//static int iteratorBinaryTree; хз можно ли удалить...
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
		//TODO сделай чтобы возвращался итератор
		iterator Parent() const noexcept
		{
			return  m_node->parent;
		}
		iterator Left() const noexcept
		{
			return  m_node->left;
		}
		iterator Right() const noexcept
		{
			return  m_node->right;
		}
		bool IsLeft(Node* left) const noexcept
		{
			return  left == m_node->left;
		}
		//  Является ли узел дерева правым у своего родителя
		bool IsRight(Node* right) const noexcept
		{
			return  right == m_node->right;
		}
		//  Поиск «самого левого» элемента
		iterator GetMin() {
			Node* fake = m_node;
			//TODO возможно ошибка из-за вершины
			while (fake != m_fictive)
			{
				fake = fake->left;
			}
			return  fake;
		}

		iterator GetMax() {
			Node* fake = m_node;
			//TODO возможно ошибка из-за вершины
			while (fake != m_fictive)
			{
				fake = fake->right;
			}
			return  fake;
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
				//	return  *this;
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
				//	return  *this;
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
	reverse_iterator rbegin() const	noexcept { return reverse_iterator(iterator(m_fictive->right, m_fictive)); }
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
	AVL(InputIterator first, InputIterator last, Compare comparator = Compare(), AllocType alloc = AllocType()) : m_fictive(make_fictive()), cmp(comparator), Alc(alloc)
	{
		//	TODO возможно надо исправить
		//  Проверка - какой вид итераторов нам подали на вход
		/*if (std::is_same<typename std::iterator_traits<InputIterator>::iterator_category, typename std::random_access_iterator_tag>::value) {
			//  Если итератор произвольного доступа, то есть надежда, что диапазон отсортирован
			//    а даже если и нет - не важно, всё равно попробуем метод деления пополам для вставки
			ordered_insert(first, last, end());
		}
		else*/
		for (auto fi = first; fi != last; fi++)
		{
			insert(*fi);
		}
	}
	void insert(T k)
	{
		m_size++;
		if (m_fictive->parent == nullptr)
		{
			m_fictive->parent = new Node{ k ,nullptr,m_fictive,m_fictive, 1 };
			m_fictive->left = m_fictive->parent;
			m_fictive->right = m_fictive->parent;
		}
		else
			insert(m_fictive->parent, k);
	}

	//	TODO VASHO: rework
	//  Рекурсивное клонирование дерева (не включая фиктивную вершину)
	//  Идея так себе - вроде пользуемся стандартной вставкой, хотя явное клонирование вершин было бы лучше
	void clone(Node* from, Node* other_dummy)
	{
		if (from == other_dummy)
			return;
		//	клонирование через insert? оно же будет переразвешиваться
		// Это ещё и рекурсивный проход в ширину, выраждает дево в список
		insert(from->data);
		clone(from->right, other_dummy);
		clone(from->left, other_dummy);
	}
	size_t size()
	{
		return  m_size;
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
	Node* rotateright(Node* p)
	{
		Node* q = p->left;
		p->left = q->right;
		q->right = p;

		q->parent = p->parent;
		p->parent = q;

		q->right->parent = p;

		fixheight(p);
		fixheight(q);
		return q;
	}
	Node* rotateleft(Node* q) // левый поворот вокруг q
	{
		Node* p = q->right;
		q->right = p->left;
		p->left = q;

		p->parent = q->parent;
		q->parent = p;

		q->left->parent = p;

		fixheight(q);
		fixheight(p);
		return p;
	}
	Node* balance(Node* p) // балансировка узла p
	{
		fixheight(p);
		int h = bfactor(p);
		if (h == 2)
		{
			if (bfactor(p->right) < 0)
				p->right = rotateright(p->right);
			return rotateleft(p);
		}
		if (h == -2)
		{
			if (bfactor(p->left) > 0)
				p->left = rotateleft(p->left);
			return rotateright(p);
		}
		return p; // балансировка не нужна
	}
	Node* insert(Node* p, T k) // вставка ключа k в дерево с корнем p
	{

		if (k < p->data)
			if (p == m_fictive->left) {
				p->left = new Node(k, p, m_fictive, m_fictive, 0);
				m_fictive->left = p->left;
			}
			else
				if (p->left == m_fictive)
					p->left = new Node(k, p, m_fictive, m_fictive, 0);
				else
					p->left = insert(p->left, k);
		else
			if (p == m_fictive->right) {
				p->right = new Node(k, p, m_fictive, m_fictive, 0);
				m_fictive->right = p->right;
			}
			else
				if (p->right == m_fictive)
					p->right = new Node(k, p, m_fictive, m_fictive, 0);
				else
					p->right = insert(p->right, k);
		return balance(p);
	}
};