// Zanyt2.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <algorithm>
#include <list>
#include "MyList.h"

using namespace std;

int main()
{
	{
		MyList<int> lst{ 1,6,2,-3,4,-5,-4 , 6 };
		cout << "Count_ positive: ";
		cout << count_positive(lst) << '\n';
		//int count,mx;
		auto [mx, count] = count_maxim(lst);
		cout << "Maxim and count: ";
		cout << mx << ' ' << count << '\n';
		MyList<int> n{};
		MyList<int> p{};
		split_the_list_into_two(lst, p);
		lst.print_from_head();
		p.print_from_head();

	}
	{
		MyList<int> lst{ 1,2,3,4,5 };
		reverse(lst);
		lst.print_from_head();
	}
	{
		MyList<int> list1, list2;
		list1.push_back(10);
		cout << (++--list1.end() == list1.end()) << endl;
		cout << (list2.end() != list1.end()) << endl;
		cout << (list1.end() == list1.end()) << endl;
		cout << *(--list1.end()) << endl;
	}

}