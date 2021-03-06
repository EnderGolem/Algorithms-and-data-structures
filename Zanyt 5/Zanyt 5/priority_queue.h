#pragma once
#include<iostream>
#include<vector>
#include<cassert>
#include<algorithm>

namespace my
{
	template <class _Ty, class _Container = std::vector<_Ty>, class _Pr = std::less<typename _Container::value_type>>
	class priority_queue
	{

	public:
		using value_type = typename _Container::value_type;
		using reference = typename _Container::reference;
		using const_reference = typename _Container::const_reference;
		using size_type = typename _Container::size_type;
		using container_type = _Container;
		using value_compare = _Pr;
		_Pr cmp = _Pr();
		priority_queue() = default;
		priority_queue(value_type mas[], int size)
		{
			build_heap(mas, size);
		}
		void push(_Ty x)
		{
			heap_insert(x);
		}
		void print()
		{
			std::cout << "Size: " << size << '\n';
			std::for_each(cont.begin(), cont.end(), [](auto x) {std::cout << x << ' '; });
			std::cout << '\n';
		}

		void build_heap(value_type mas[], int size)
		{
			cont.clear();
			this->size = size;
			for (int i = 0; i < size; i++)
				cont.push_back(mas[i]);
			for (int i = size/ 2 - 1; i >= 0; i--)
			{
				heapify(i);
			}
		}
		void merge(priority_queue<value_type, container_type, value_compare> pri_queue)
		{
			auto cont2 = pri_queue.cont;
			container_type new_cont;
			int i = 0;
			int y = 0;
			size = 0;
			for (; i < cont.size() && y < cont2.size(); )
			{
				if (cont[i] < cont2[y])
				{
					new_cont.push_back(cont2[y]);
					y++;
				}
				else
				{
					new_cont.push_back(cont[i]);
					i++;
				}
				if (new_cont[new_cont.size - 1] > new_cont[parent(new_cont.size - 1)])
				{
					std::swap(new_cont[new_cont.size - 1], new_cont[parent(new_cont.size - 1)]);
				}
			}
			while (i < cont.size())
			{
				new_cont.push_back(cont[i]);
				i++;
				size++;
				if (new_cont[new_cont.size - 1] > new_cont[parent(new_cont.size - 1)])
				{
					std::swap(new_cont[new_cont.size - 1], new_cont[parent(new_cont.size - 1)]);
				}
			}
			while (y < cont2.size())
			{
				new_cont.push_back(cont2[y]);
				y++;
				if (new_cont[new_cont.size - 1] > new_cont[parent(new_cont.size - 1)])
				{
					std::swap(new_cont[new_cont.size - 1], new_cont[parent(new_cont.size - 1)]);
				}
			}
			cont = new_cont;
		}
		void heapify(int i)
		{
			assert(i >= 0 && i < cont.size());
			while (true) {
				int largest = i;
				if (left(i) < cont.size() && cmp(cont[largest], cont[left(i)]))
					largest = left(i);
				if (right(i) < cont.size() && cmp(cont[largest], cont[right(i)]))
					largest = right(i);
				if (i == largest)
					break;
				std::swap(cont[i], cont[largest]);
				i = largest;
			}
		}
		value_type top()
		{
			return cont.front();
		}
		void pop()
		{
			cont[0]= cont.back();
			cont.pop_back();
			heapify(0);

		}
		friend std::ostream& operator<<(std::ostream& os, const priority_queue& queue)
		{
			for (const auto& x : queue.cont)
			{
				os << x << "; ";
			}
			return os;
		}
		size_t size()
		{
			return cont.size();
		}
	private:
		container_type cont;
	
		void heap_insert(_Ty x)
		{
			cont.push_back(x);
			int i = cont.size() - 1;
			while (i > 0 && cmp(cont[parent(i)], cont[i]))
			{
				std::swap(cont[i], cont[parent(i)]);
				i = parent(i);
			}
		}
		int parent(int i)
		{
			assert(i >= 0 && i < cont.size());
			return (i - 1) / 2;
		}
		int left(int i)
		{
			assert(i >= 0 && i < cont.size());
			return 2 * i + 1;
		}
		int right(int i)
		{
			assert(i >= 0 && i < cont.size());
			return 2 * i + 2;
		}
	};

}