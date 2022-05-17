#include <chrono>
#include<iostream>
#include <set>
#include<unordered_set>
#include"unordered_set.h"
using namespace std;
using namespace chrono;



void testMyUnorderedSet()
{
	int count = 1000000;
	high_resolution_clock::time_point t1 = high_resolution_clock::now();
	time_t start = clock();
	my::unordered_set<int> st;
	int mas[100];
	for (int i = 0; i < 100; i++)
	{
		mas[i] = rand() % 100;
	}
	for (int i = 0; i < 1000; i++)
	{
		st.insert(mas[i % 100]);
	}
	for (int z = 0; z < count; z++)
	{
		for (int i = 0; i < 100; i++)
		{
			st.insert(mas[i]);
		}
		for (int i = 0; i < 50; i++)
		{
			st.has(mas[rand() % 100]);
		}
		for (int i = 0; i < 100; i++)
		{
			st.erase(mas[i]);
		}
	}
	high_resolution_clock::time_point t2 = high_resolution_clock::now();
	long double duration = duration_cast<milliseconds>(t2 - t1).count();
	cout <<"my::unordered_set<int>  " << duration / count << '\n';
}

void testUnorderedSet()
{
	int count = 1000000;
	high_resolution_clock::time_point t1 = high_resolution_clock::now();
	time_t start = clock();
	unordered_set<int> st;
	int mas[100];
	for (int i = 0; i < 100; i++)
	{
		mas[i] = rand() % 100;
	}
	for (int i = 0; i < 1000; i++)
	{
		st.insert(mas[i % 100]);
	}
	for (int z = 0; z < count; z++)
	{
		for (int i = 0; i < 100; i++)
		{
			st.insert(mas[i]);
		}
		for (int i = 0; i < 50; i++)
		{
			st.contains(mas[rand() % 100]);
		}
		for (int i = 0; i < 100; i++)
		{
			st.erase(mas[i]);
		}
	}
	high_resolution_clock::time_point t2 = high_resolution_clock::now();
	long double duration = duration_cast<milliseconds>(t2 - t1).count();
	cout << "unordered_set<int>  " << duration / count << '\n';
}
void testSet()
{
	int count = 1000000;
	high_resolution_clock::time_point t1 = high_resolution_clock::now();
	time_t start = clock();
	set<int> st;
	int mas[100];
	for (int i = 0; i < 100; i++)
	{
		mas[i] = rand() % 100;
	}
	for (int i = 0; i < 1000; i++)
	{
		st.insert(mas[i % 100]);
	}
	for (int z = 0; z < count; z++)
	{
		for (int i = 0; i < 100; i++)
		{
			st.insert(mas[i]);
		}
		for (int i = 0; i < 50; i++)
		{
			st.contains(mas[rand() % 100]);
		}
		for (int i = 0; i < 100; i++)
		{
			st.erase(mas[i]);
		}
	}
	high_resolution_clock::time_point t2 = high_resolution_clock::now();
	long double duration = duration_cast<milliseconds>(t2 - t1).count();
	cout << "set<int>  " << duration / count << '\n';
}
/*
old
my::unordered_set<int>  0.003483
unordered_set<int>  0.007834
set<int>  0.009365
 */
int main()
{
	my::unordered_set<int> st;
/*	st.insert(1);
	st.insert(702);
	st.insert(2);
	st.insert(3);
	st.erase(2);
	cout << st.get_size() << '\n';
	st.insert(3);
	cout << st.get_size() << '\n';
	st.print();
	*/

	st.insert(1);
	st.erase(1);
	cout << st.has(1) << '\n';
	/*
	testMyUnorderedSet();
	testUnorderedSet();
	testSet();
	*/
}