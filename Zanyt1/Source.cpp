
#include "elem.h"
#include <time.h>
#include <vector>
#include <algorithm>
#include <iostream>
#include <assert.h>
#include <chrono>
#include <numeric>
#include <ctime>
#include <fstream>
#include <map>

typedef  long long ll;
using ll = long long;
using namespace  std;
using namespace  chrono;

size_t elem::assigns = 0;
size_t elem::compares = 0;


/// <summary>
/// Подсчет операций для задачи 1
/// </summary>
void test1(size_t n, long long& ins, long long& srt, int times = 5)
{
	ins = 0;
	srt = 0;
	for (int i = 0; i < times; i++) {
		vector<elem> v1(n), v2(v1);


		elem::reset();
		insertionSort(v1);
		ins += elem::compares + elem::assigns;
		elem::reset();
		quicksort(v2);
		srt += elem::compares + elem::assigns;
	}
	srt /= times;
	ins /= times;

}
/// <summary>
/// 2 задача через динамику
/// </summary>
int solution_task_2(int n)
{
	vector<pair<int, int>> sf(n + 2);
	sf[0].first = 1;
	sf[0].second = 1;
	sf[1].first = 1;
	sf[1].second = 1;
	for (int i = 2; i < n; i++)
	{
		sf[i].first = sf[i - 1].first + sf[i - 1].second;
		sf[i].second = sf[i - 1].first;
	}
	return sf[n - 1].second;
}
/// <summary>
/// 3 задача
/// </summary>
map<long long, int> solution_task_3(long long n)
{
	map<long long, int> ans;
	for (long long i = 2; i < sqrt(n); i++)
	{
		if (n % i == 0)
		{
			ans[i] = 1;
			n /= i;
		}
		while (n % i == 0) { n /= i; ans[i]++; }
	}
	return ans;
}
/// <summary>
/// 4 задача через динамику
/// </summary>
int solution_task_4(int n)
{
	vector<pair<int, pair<int, int>>> sf(11);

	sf[0].first = 5;
	sf[0].second.first = 4;
	sf[0].second.second = 0;
	for (int i = 1; i < n; i++)
	{
		sf[i].first = sf[i - 1].first * 6 + sf[i - 1].second.first * 6 - 1;
		sf[i].second.first = sf[i - 1].first * 5;
		if (i >= 2)
			sf[i].second.second = sf[i - 2].first * 5 + sf[i - 2].second.first * 4;
		cout << i << ' ' << sf[i].first << " " << sf[i].second.first << " " << sf[i].second.second << '\n';

	}
	return sf[n - 1].second.second;

}
/// <summary>
/// 4 задача через подобие фибоначи
/// </summary>
ll solution_task_4_ver_fib(int n)
{
	ll a = 9, b = 5;
	ll c = 0;
	ll d = 0;
	for (int i = 2; i < n; i++)
	{
		c = 6 * a + b * 4;
		d = 6 * a;
		a = c;
		b = d;
	}
	return  b + 4 * a;

}
/*
1 0 0
10 94 95
100 7450 2533
1000 742035 26798
10000 74492022 208736
100000 3126153266 2115218
 Встроенный алгоритм сортировки быстрее чем самописный метод сортировки вставками
 т.к. в среднем сортировка вставками O(n^2) а у sort (O(n*log(n))
 */


/// <summary>
/// Сравнение двух разных сортировок
/// </summary>
void test_the_number_of_actions_of_the_first()
{
	srand(static_cast<unsigned int>(time(NULL)));
	for (int i = 1; i < 1000000; i *= 10)
	{
		long long ins, srt;
		test1(i, ins, srt);
		cout << i << ' ' << ins << ' ' << srt << '\n';
	}
}

long double test3(vector<ll> inputArr) {
	size_t count = inputArr.size();
	high_resolution_clock::time_point t1 = high_resolution_clock::now();
	time_t start = clock();
	for (int i = 0; i < inputArr.size(); ++i)
		solution_task_3(inputArr[i]);
	high_resolution_clock::time_point t2 = high_resolution_clock::now();
	long double duration = duration_cast<milliseconds>(t2 - t1).count();
	cout << duration / count << '\n';
	return (duration ) / count;
}
/// <summary>
/// Вывод в таблицу для задачи 3
/// </summary>
void test_third()
{
	ofstream out("results.csv");
	out << "Size;Random;Simple;Mild;\n";
	for (int i = 1; i < 18; i++) {
		out << i << ";";
		cout << "Size " << i << '\n';
		vector<ll> sf(100);
		create_random_vector(sf, i); //print(sf);

		auto f = test3(sf); out << f << ";";

		create_simple_vector(sf, i); //print(sf);
		f = test3(sf);  out << f << ";";

		create_mild_vector(sf, i);// print(sf);
		f = test3(sf);  out << f << "; \n";
		cout << '\n';


	}


	out.close();
	system("results.csv");
	system("pause");
}
int main(int argc, char* argv[])
{
	test_third();
	return 0;
}




/*
long long solution_task_4_ver(int n)
{
	vector<vector<long long>> sf(14, vector<long long>(10, 0));
	for (int i = 1; i < 10; i++)
	{
		sf[0][i] = 1;
	}
	for (int i = 1; i < n; i++)
	{
		long long sum = 0;
		for (int y = 0; y < 10; y++)
		{
			sum += sf[i - 1][y];
		}
		sf[i][0] = sum;
		sf[i][1] = sum;
		sf[i][4] = sum;
		sf[i][6] = sum;
		sf[i][8] = sum;
		sf[i][9] = sum;
		sum = sf[i - 1][0] + sf[i - 1][1] + sf[i - 1][4] +
			sf[i - 1][6] + sf[i - 1][8] + sf[i - 1][9];
		sf[i][2] = sum;	sf[i][3] = sum;	sf[i][5] = sum;	sf[i][7] = sum;
	}
	long long ans = 0;
	for (int i = 0; i < 10; i += 2)
	{
		ans += sf[n - 1][i];
	}
	return  ans;
}*/