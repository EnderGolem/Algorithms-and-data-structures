#pragma once
#include <iostream>






template<typename T, class Compare = std::less<T>, class Allocator = std::allocator<T>>
class AVL
{
	struct  Node
	{
		T data;
		Node* parent, * left, * right;
		unsigned char height;
	};
	Node* m_fictive;
	//  Стандартные контейнеры позволяют указать пользовательский аллокатор, который используется для
//  выделения и освобождения памяти под узлы (реализует замену операций new/delete). К сожалению, есть 
//  типичная проблема – при создании дерева с ключами типа T параметром шаблона традиционно указывается
//  std::allocator<T>, который умеет выделять память под T, а нам нужен аллокатор для выделения/освобождения
//  памяти под Node, т.е. std::allocator<Node>. Поэтому параметр шаблона аллокатора нужно изменить
//  с T на Node, что и делается ниже. А вообще это одна из самых малополезных возможностей - обычно мы
//  пользовательские аллокаторы не пишем, это редкость.

	//  Определяем тип аллокатора для Node (Allocator для T нам не подходит)
	using AllocType = typename std::allocator_traits<Allocator>::template rebind_alloc < Node >;

public:
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


public:
	//static int iteratorBinaryTree; хз можно ли удалить...
	class iteratorAVL
	{
		
	};

	AVL()
	{
		void* place = operator new(sizeof(Node)); 
		m_fictive = static_cast<Node*>(place); 
		m_fictive->left = m_fictive;
		m_fictive->right = m_fictive;
		m_fictive->parent = nullptr;		
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
		fixheight(p);
		fixheight(q);
		return q;
	}
	Node* rotateleft(Node* q) // левый поворот вокруг q
	{
		Node* p = q->right;
		q->right = p->left;
		p->left = q;
		fixheight(q);
		fixheight(p);
		return p;
	}
	Node* balance(Node* p) // балансировка узла p
	{
		fixheight(p);
		if (bfactor(p) == 2)
		{
			if (bfactor(p->right) < 0)
				p->right = rotateright(p->right);
			return rotateleft(p);
		}
		if (bfactor(p) == -2)
		{
			if (bfactor(p->left) > 0)
				p->left = rotateleft(p->left);
			return rotateright(p);
		}
		return p; // балансировка не нужна
	}
	Node* insert(Node* p, int k) // вставка ключа k в дерево с корнем p
	{
		if (!p) return new Node(k);
		if (k < p->key)
			p->left = insert(p->left, k);
		else
			p->right = insert(p->right, k);
		return balance(p);
	}
};