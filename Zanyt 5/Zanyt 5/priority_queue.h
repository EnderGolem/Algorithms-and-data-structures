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
		void add(_Ty x)
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
		void merge(priority_queue cont2<value_type,container_type,value_compare>)
		{
			container_type<value_type> new_cont;
			int i = 0;
			int y = 0;
			size = 0;
			for (; i < sf.size() && y < cont2.size(); )
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
				if (new_cont[size - 1] > new_cont[parent(size - 1)])
				{
					std::swap(new_cont[size - 1], new_cont[parent(size - 1)]);
				}
			}


			cont = new_cont;
		}
		void heapify(int i)
		{
			assert(i >= 0 && i < size);
			while (true) {
				int largest = i;
				if (left(i) < size && cmp(cont[largest], cont[left(i)]))
					largest = left(i);
				if (right(i) < size && cmp(cont[largest], cont[right(i)]))
					largest = right(i);
				if (i == largest)
					break;
				std::swap(cont[i], cont[largest]);
				i = largest;
			}
		}
	private:
		_Container cont;
		int size = 0;

	
		void heap_insert(_Ty x)
		{
			cont.push_back(x);
			size++;
			int i = size - 1;
			while (i > 0 && cmp(cont[parent(i)], cont[i]))
			{
				std::swap(cont[i], cont[parent(i)]);
				i = parent(i);
			}
		}
		int parent(int i)
		{
			assert(i >= 0 && i < size);
			return (i - 1) / 2;
		}
		int left(int i)
		{
			assert(i >= 0 && i < size);
			return 2 * i + 1;
		}
		int right(int i)
		{
			assert(i >= 0 && i < size);
			return 2 * i + 2;
		}
	};

}