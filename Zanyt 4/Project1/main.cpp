#include <iostream>
#include "AVL.h"

using namespace  std;
template<typename T> using Myal = std::allocator<T>;
template<typename T> using Mypred = std::less<T>;

//  Для того, чтобы выполнить тестирование одного из указанных контейнеров (std::set или Binary_Tree_Search)
//    должна быть раскомментирована одна из следующих строк:
//template<typename T> using ContainerTemplate = std::set<T, Mypred<T>, Myal<T>>;
template<typename T> using ContainerTemplate = AVL<T, Mypred<T>, Myal<T>>;

using Mycont = ContainerTemplate<char>;
int main()
{
	char carr[] = "abc", carr2[] = "def";
	Mycont v0;
	Myal<char> al = v0.get_allocator();
	Mypred<char> pred;
	Mycont v0a(pred);

	Mycont v1(carr, carr + 3);
	v1.printWithHeights();

}