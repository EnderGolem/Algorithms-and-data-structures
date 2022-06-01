#include <iostream>
#include "AVL.h"

template<typename T> using Myal = std::allocator<T>;
template<typename T> using Mypred = std::less<T>;
using namespace  std;
template<typename T> using ContainerTemplate = AVL<T, Mypred<T>, Myal<T>>;
int main()
{
	ContainerTemplate<int> Tree = { 40,50,30 };
	ContainerTemplate<int> Tree2(Tree);
	ContainerTemplate<int> Tree3(Tree.begin(), Tree.end());
	cout << (Tree == Tree3) << '\n';

	Tree3.clear();



}