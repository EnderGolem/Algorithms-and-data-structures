#include<iostream>
#include<unordered_set>
#include"unordered_set.h"
using namespace std;

int main()
{
	my::unordered_set<int> st;
	st.insert(6);
	cout << "-------------\n";
	st.insert(7);
	cout << "-------------\n";
	st.insert(7);
	st.print();
	cout << NULL << '\n';
}