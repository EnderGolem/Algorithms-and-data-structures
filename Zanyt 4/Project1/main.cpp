#include <iostream>

#include "AVL.h"
template<typename T> using Myal = std::allocator<T>;
template<typename T> using Mypred = std::less<T>;
using namespace  std;
template<typename T> using ContainerTemplate = AVL<T, Mypred<T>, Myal<T>>;
int main()
{
	ContainerTemplate<int> T1;
	cout << T1.size() << '\n';
	ContainerTemplate<int> Tree = { 40,50,30,35,10,75,23,87,68 };
	cout << Tree.size() << '\n';
	ContainerTemplate<int> Tree2(Tree);
	cout << Tree2.size() << '\n';
	auto a = Tree.begin();
	for(int i = 0;i<12;i++)
	{
		a++;
		cout << *a << '\n';
	}
	
}