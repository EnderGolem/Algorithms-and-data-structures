#include<iostream>
#include<unordered_set>
#include"unordered_set.h"
using namespace std;

int main()
{
	bool* f;
	f = new bool[10];
	if (f[2])
		cout << '2' << '\n';
	if (!f[2])
		cout << '3' << '\n';
	my::unordered_set<int> st;
	st.insert(1);
	cout << st.get_size() << '\n';
	st.erase(1);
	cout << st.get_size() << '\n';
	st.insert(1);
	cout << st.get_size() << '\n';
	for (int i = 1; i <= 1000; i++)
	{
		st.insert(i);
	}
	cout << st.get_size() << '\n';
}