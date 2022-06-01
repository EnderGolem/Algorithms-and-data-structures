#include <iostream>

#include "AVL.h"
template<typename T> using Myal = std::allocator<T>;
template<typename T> using Mypred = std::less<T>;
using namespace  std;
template<typename T> using ContainerTemplate = AVL<T, Mypred<T>, Myal<T>>;
int main()
{
	ContainerTemplate<int> T1, T2;
	T1.insert(1);
	T1.insert(2);
	T1.insert(3);
	T1.insert(4);
	T1.insert(5);
	T1.insert(6);
	cout << (T1 == T2) << '\n';
	ContainerTemplate<int> Tree = { 40,50,30,35,10,75,23,87,68 };
	ContainerTemplate<int> Tree2(Tree);
	cout << (Tree == Tree2) << '\n';
	ContainerTemplate<int> Tree3;
	for (auto fi = Tree2.begin(); fi != Tree2.end(); fi++)
	{
		Tree3.insert(*fi);
	}

	cout << (Tree == Tree3) << '\n';
	for (auto fi = Tree2.begin(); fi != Tree2.end(); fi++)
	{
		cout << *fi << '\n';
	}
	cout << '\n';
	auto a = Tree3.begin();
	cout << *a << '\n';
	for (int i = 0; i < 10; i++)
	{
		a++;
		cout << *a << '\n';
	}
}