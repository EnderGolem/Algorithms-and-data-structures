#pragma once
#include <iostream>
#include <iterator>
#include <tuple>
#include <initializer_list>

using namespace  std;

template<class T>
class MyList
{
private:
	class ListNode
	{
	public:
		T data;
		ListNode* next, * prev;
	};

	ListNode* head;
	ListNode* tail;
	/// <summary>
	/// Узел для итератора
	/// </summary>
	ListNode* tail_end;
	int sze;
public:
	class my_list_itetator
	{
		ListNode* node;
	public:
		using difference_type = size_t;
		using value_type = T;
		using pointer = T*;
		using reference = T&;
		using iterator_category = bidirectional_iterator_tag;

		my_list_itetator(ListNode* node) : node(node) {}
		T& operator*() { return node->data; }
		my_list_itetator& operator++() {
			node = node->next;
			return *this;
		}
		my_list_itetator operator++(int) {
			auto t = *this;
			++node;
			return t;
		}
		my_list_itetator operator--() {
			node = node->prev;
			return *this;
		}
		friend bool operator==(my_list_itetator v1, my_list_itetator v2) {
			return v1.node == v2.node;
		}
		friend bool operator!=(my_list_itetator v1, my_list_itetator v2) {
			return !(v1 == v2);
		}
	};

	my_list_itetator begin() const {
		return my_list_itetator(head);
	}
	my_list_itetator end() const {
		return my_list_itetator(tail_end);
	}
	MyList() : head(nullptr), tail(nullptr)
	{
		tail_end = new ListNode{ 1 };
		check_end();
	}
	MyList(initializer_list<T> lst) : head(nullptr), tail(nullptr)
	{
		tail_end = new ListNode{ 1 };
		check_end();
		for (auto x : lst)
		{
			this->push_back(x);
		}
		tail_end = new ListNode{ 1,nullptr,nullptr };
		check_end();
	}
	MyList(ListNode* node) : head(node)
	{
		tail_end = new ListNode{ 1 };
		check_end();

		if (head)
		{
			tail = nullptr;
			return;
		}
		while (node->next != nullptr)
			node = node->next;
		tail = node;

	}
	MyList(const MyList& lst) : head(nullptr), tail(nullptr)
	{
		tail_end = new ListNode{ 1 };
		check_end();
		for (auto x : lst)
			this->push_back(x);

	}
	MyList(my_list_itetator begin, my_list_itetator end) : head(nullptr), tail(nullptr)
	{
		while (begin != end)
		{
			++begin;
		}
		tail_end = new ListNode{ 1 };
		check_end();
	}
	void push_back(T x)
	{
		if (head != nullptr)
		{
			auto node = new ListNode{ x,nullptr,tail };
			tail->next = node;
			tail = node;
			
			sze++;
		}
		else
		{
			auto node = new ListNode{ x, nullptr, nullptr };
			head = node;
			tail = node;

			sze++;
		}
		check_end();
	}
	void push_back(ListNode* node)
	{

		if (head != nullptr)
		{
			tail->next = node;
			node->prev = tail;
			tail = node;
			sze++;
		}
		else
		{
			node->next = nullptr;
			node->prev = nullptr;
			head = node;
			tail = node;
			sze++;
		}
		check_end();
	}
	void pop_back()
	{
		if (head == nullptr)
			return;
		if (head != tail)
		{
			tail = tail->prev;
			delete tail->next;
			sze--;
		}
		else
		{
			delete tail;
			tail = nullptr;
			head = nullptr;
			sze--;
		}

		check_end();
	}
	T front() const
	{
		return head->data;
	}
	T back() const
	{
		return tail->data;
	}
	size_t size() const
	{
		return  sze;
	}
	~MyList()
	{
		if (head == nullptr)
			return;

		while (head != tail)
		{
			auto p = head;
			head = head->next;
			delete p;
		}

		delete head;
		head = nullptr; tail = nullptr;

		delete tail_end;
	}

	/// <summary>
	/// Выводит лист начиная с головы
	/// </summary>
	void print_from_head() const
	{
		auto node = head;
		while (node != tail_end)
		{
			cout << node->data << ' '; node = node->next;
		}
		cout << '\n';
	}
	/// <summary>
	/// Выводит лист начиная с хвоста
	/// </summary>
	void print_from_tail() const
	{
		auto node = tail;
		while (node != tail_end)
		{
			cout << node->data << ' '; node = node->prev;
		}
		cout << '\n';

	}
	/// <summary>
	/// Возвращает кортеж двух листов, в первом отрицательные элементы, во втором положительные
	/// </summary>
	friend void split_the_list_into_two(MyList<int>& negative_lst, MyList<int>& positive_lst)
	{
		auto node = negative_lst.head;
		while (node != negative_lst.tail_end)
		{
			auto f = node->next;
			if (node->data > 0)
			{
				negative_lst.remove_without_memory(node);
				positive_lst.push_back(node);
			}
			node = f;

		}
		negative_lst.check_end();
		positive_lst.check_end();
	}
	/// <summary>
	/// Реверсирует список
	/// </summary>
	friend void reverse(MyList<int>& lst)
	{
		swap(lst.head, lst.tail);
		auto node = lst.head;
		while (node != nullptr)
		{			
			swap(node->prev, node->next);
			node = node->next;
		}
		lst.check_end();
	}
private:
	/// <summary>
	/// удаляет вершину без удаления памяти
	/// </summary>
	void remove_without_memory(ListNode*& node)
	{
		if (node == head)
		{
			head = head->next;
		}
		if (node == tail)
		{
			tail = tail->prev;
		}

		if (node == nullptr)
			return;
		if (node->prev != nullptr)
			node->prev->next = node->next;
		if (node->next != tail_end)
			node->next->prev = node->prev;
		check_end();
	}
	/// <summary>
	/// Следит за тем, чтобы дополнительный элемент не пропал
	/// </summary>
	void check_end()
	{
		if(tail == nullptr)
		{
			tail_end->prev = nullptr;
			return;
		}
		tail->next = tail_end;
		tail_end->prev = tail;

	}
};

int count_positive(const MyList<int>  lst)
{
	int pos = 0;
	for (auto x : lst)
	{
		if (x > 0)
			pos++;
	}
	return  pos;
}
tuple<int, int> count_maxim(const MyList<int>& lst)
{
	int mx = INT32_MIN;
	for (auto x : lst)
	{
		if (mx < x)
			mx = x;
	}
	int count = 0;
	for (auto x : lst)
	{
		if (mx == x)
			count++;
	}
	return  make_tuple(mx, count);
}