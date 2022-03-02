#pragma once
#include <time.h>
#include <vector>
#include <algorithm>
#include <chrono>
#include <iostream>
#include <random>
using namespace  std;

using ll = long long;
class elem {
	int data;
public:
	static size_t assigns, compares;
	elem() {
		data = rand() % 100;
	};
	
	elem(const int& data):data(data)
	{
		++assigns;
	}
	elem(const elem& other) : data(other.data) {
		++assigns;
	};
	static void reset() {
		assigns = 0;
		compares = 0;
	}
	bool operator<(const elem& other) const {
		++compares;
		return data < other.data;
	}
	const elem& operator=(const elem& other) {
		++assigns;
		data = other.data;
		return *this;
	}
	friend  ostream& operator<<(std::ostream& out, const elem& item) {
		return out << item.data;
	}
};
void bubblesort(std::vector<elem>& vect) {
	for (size_t i = vect.size() - 1; i > 0; --i)
		for (size_t j = 0; j < i; ++j)
			if (vect[j + 1] < vect[j])
				std::swap(vect[j + 1], vect[j]);
}
void quicksort(std::vector<elem>& vect) {
	sort(vect.begin(), vect.end());
}
void stablesort(std::vector<elem>& vect) {
	stable_sort(vect.begin(), vect.end());
}

void insertionSort(vector<elem>& vect)
{
	elem t;
	int	last; 
	for (int i = 1; i < vect.size(); i++)
	{
		t = vect[i];
		last = i - 1;
		while (last >= 0 &&  t < vect[last]) 
		{
			vect[last + 1] = vect[last]; 
			vect[last] = t;			
			last--;
		}
	}
}
bool is_prime(ll n)
{
	if (n == 0 || n == 1) { return  false; }

	 for (ll i = 2; i < sqrt(n); i++)
	 { if (n % i == 0) {return false; } }
	 return  true;


}
/// <summary>
/// Все ли делители числа меньше 7
/// </summary>
bool is_mild(ll n)
{
	if(n == 0 || n == 1)	
		return  false;

	while (n % 2 == 0)	n /= 2;
	while (n % 3 == 0) n /= 3;
	while (n % 5 == 0) n /= 5;
	while (n % 7 == 0) n /= 7;

	return n == 1;

	
}
void create_random_vector(vector<ll>& v,int sz)
{
	random_device rd;
	mt19937 engine(rd());
	uniform_int_distribution<ll> dist(pow(10,sz-1), pow(10,sz));
	for (int i = 0; i < v.size(); i++)
		v[i] = dist(engine);
}
void create_simple_vector(vector<long long>& v,int sz)
{
	ll y = pow(10, sz - 1);
	for (int i = 0; i < v.size(); i++)
		while(y < pow(10,sz))
		{
			y++;
			y %= (int)pow(10, sz);
			if(is_prime(y))
			{
				v[i] = y;
				break;
			}
		}
}

void create_mild_vector(vector<long long>& v, int sz)
{

	ll y = pow(10, sz - 1);
	for (int i = 0; i < v.size(); i++)
	{
		while (y < pow(10, sz))
		{
			y++;
			y %= (int)pow(10, sz);
			if (is_mild(y))
			{
				v[i] = y;
				break;
			}
		}
	}
}

template<typename T>
void print(vector<T> v)
{
	for (auto e : v)
		cout << e << ' ';
	cout << '\n';
}

