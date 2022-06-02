#include <chrono>
#include <iostream>
#include <set>

#include "AVL.h"

using namespace  std;
template<typename T> using Myal = std::allocator<T>;
template<typename T> using Mypred = std::less<T>;


//template<typename T> using ContainerTemplate = std::set<T, Mypred<T>, Myal<T>>;
template<typename T> using ContainerTemplate = AVL<T, Mypred<T>, Myal<T>>;

using Mycont = ContainerTemplate<char>;

void testSet(int n = 1e5)
{
	set<int> st;
	chrono::high_resolution_clock::time_point t1 = chrono::high_resolution_clock::now();
	for (int i = 0; i < n / 2; i++)
	{
		st.insert(i);
	}
	for (int y = 0; y <= n; y++) {
		for (int i = 0; i < 100; i++)
		{
			st.erase(i);
		}
		for (int i = 0; i < 100; i++)
		{
			st.insert(i);
		}
	}
	chrono::high_resolution_clock::time_point t2 = chrono::high_resolution_clock::now();
	long double duration = std::chrono::duration_cast<chrono::milliseconds>(t2 - t1).count();
	cout << duration << '\n';

}
void testAVL(int n = 1e5)
{
	AVL<int> st;
	chrono::high_resolution_clock::time_point t1 = chrono::high_resolution_clock::now();
	for (int i = 0; i < n / 2; i++)
	{
		st.insert(i);
	}
	for (int y = 0; y <= n; y++) {
		for (int i = 0; i < 100; i++)
		{
			st.erase(i);
		}
		for (int i = 0; i < 100; i++)
		{
			st.insert(i);
		}
	}
	chrono::high_resolution_clock::time_point t2 = chrono::high_resolution_clock::now();
	long double duration = std::chrono::duration_cast<chrono::milliseconds>(t2 - t1).count();
	cout << duration << '\n';

}


int main()
{
	testSet(10000);
	testAVL(10000);
}