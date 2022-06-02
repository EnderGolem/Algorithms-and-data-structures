#include <iostream>
#include "AVL.h"

using namespace  std;
template<typename T> using Myal = std::allocator<T>;
template<typename T> using Mypred = std::less<T>;


//template<typename T> using ContainerTemplate = std::set<T, Mypred<T>, Myal<T>>;
template<typename T> using ContainerTemplate = AVL<T, Mypred<T>, Myal<T>>;

using Mycont = ContainerTemplate<char>;
int main()
{
	ContainerTemplate<int> a({1,2,3,4,5,6,7});
	cout<<a.contains(1)<<'\n';
	cout<<a.contains(3)<<'\n';
	cout<<a.contains(8)<<'\n';

}