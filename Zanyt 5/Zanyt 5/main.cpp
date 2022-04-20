#include<iostream>
#include<queue>
#include<vector>
#include<list>
#include <chrono>
#include <fstream>
#include <sstream>
#include "priority_queue.h"

using namespace std;
using namespace  chrono;
using ll = long long;


class strlength
{
public:
	bool operator() (const string& str1, const string& str2) const
	{
		return str1.length() > str2.length();
	}
};

void check_time() {
	ifstream ifs;
	ifs.open("Tolkien.txt");
	vector<string> vc;
	cout << "Start reading\n";

	string s;
	while (ifs >> s)
	{
		vc.push_back(s);
	}
	cout << "Stop reading \n";
	priority_queue < string, deque<string>, strlength>  sf;
	high_resolution_clock::time_point t1 = high_resolution_clock::now();
	time_t start = clock();
	for (auto x : vc)
	{
		sf.push(x);
		if (sf.size() > 20)
			sf.pop();
	}
	high_resolution_clock::time_point t2 = high_resolution_clock::now();
	long double duration1 = duration_cast<milliseconds>(t2 - t1).count();
	cout << "Normal PQ: \n";
	/*
	while (sf.size() > 0)
	{
		cout << sf.top() << "; ";
		sf.pop();
	}
	*/
	cout << '\n';
	cout << "Time: " << duration1 << '\n';


	my::priority_queue < string, deque<string>, strlength>  fs;
	high_resolution_clock::time_point t3 = high_resolution_clock::now();
	for (auto x : vc)
	{
		fs.push(x);
		if (fs.size() > 20)
			fs.pop();
	}
	high_resolution_clock::time_point t4 = high_resolution_clock::now();
	long double duration2 = duration_cast<milliseconds>(t4 - t3).count();
	cout << "My PQ: \n";
	//cout << fs;
	cout << '\n';
	cout << "Time: " << duration2 << '\n';
}
int main()
{
	check_time();

}

/*
vector:

Start reading
Stop reading
Normal PQ:

Time: 37
My PQ:

Time: 88

list:

Start reading
Stop reading
Normal PQ:

Time: 61
My PQ:

Time: 122

*/