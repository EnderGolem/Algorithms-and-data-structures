#include <chrono>
#include <iostream>
#include <fstream>
#include <map>
#include <string>
#include <iomanip>
#include <unordered_map>
#include "tree_for_words.h"
using namespace std;

/// <summary>
/// Реализация через set
/// </summary>
void realize_set()
{
	map<string, int> mp;
	chrono::high_resolution_clock::time_point t1 = chrono::high_resolution_clock::now();
	std::ifstream in("War and Peace.txt");
	if (in.is_open())
	{

		string s;
		while (in >> s)
		{
			mp[s]++;
		}

		/*
		char c;
		while (in.peek() != EOF)
		{
			c = in.get();
			tree.plus_word(c);
		}
		*/
	}
	else
	{
		cout << "Couldn't open file\n";
	}
	in.close();
	chrono::high_resolution_clock::time_point t2 = chrono::high_resolution_clock::now();
	cout << std::chrono::duration_cast<chrono::milliseconds>(t2 - t1).count() << '\n';
}

void realize_tree_for_words_string()
{
	cout << int('\r') << int('\n') << '\n';
	tree_for_words tree{};
	chrono::high_resolution_clock::time_point t1 = chrono::high_resolution_clock::now();
	std::ifstream in("War and Peace.txt");
	if (in.is_open())
	{

		string s;
		while (in >> s)
		{
			tree.plus_word(s);
		}

		/*
		char c;
		while(in.peek()  != EOF)
		{
			c = in.get();
			tree.plus_word(c);
		}*/
	}
	else
	{
		cout << "Couldn't open file\n";
	}
	in.close();
	chrono::high_resolution_clock::time_point t2 = chrono::high_resolution_clock::now();
	cout << chrono::duration_cast<chrono::milliseconds>(t2 - t1).count() << '\n';
}

void realize_tree_for_words_char()
{
	tree_for_words tree{};
	chrono::high_resolution_clock::time_point t1 = chrono::high_resolution_clock::now();
	std::ifstream in("War and Peace.txt");
	if (in.is_open())
	{


		char c;
		while (in.peek() != EOF)
		{
			c = in.get();
			if ('A' <= c && c <= 'Z') // По приколу сравни потом без такого сравнения
				c += 32;
			tree.plus_word(c);
		}
	}
	else
	{
		cout << "Couldn't open file\n";
	}
	in.close();
	chrono::high_resolution_clock::time_point t2 = chrono::high_resolution_clock::now();
	cout << "Time " << chrono::duration_cast<chrono::milliseconds>(t2 - t1).count() << '\n';

	tree.find_max();

}

void realize_unordered_map_first()
{
	unordered_map<string, int> mp;
	chrono::high_resolution_clock::time_point t1 = chrono::high_resolution_clock::now();
	std::ifstream in("War and Peace.txt");
	if (in.is_open())
	{
		string s;
		while (in >> s)
		{
			if (s.back() < 'a' || s.back() > 'z')
			{
				s.pop_back();
				while (s.length() > 0 && (s.back() < 'a' || s.back() > 'z'))
				{
					s.pop_back();
				}

			}
			while (s.length() > 0 && !('A' <= s[0] && s[0] <= 'z'))
				s.erase(0);

			if (s.length() > 0 && 'A' <= s[0] && s[0] <= 'Z')
				s[0] += 32;

			if (!s.empty())
				mp[s]++;
		}

	}
	else
	{
		cout << "Couldn't open file\n";
	}
	in.close();
	chrono::high_resolution_clock::time_point t2 = chrono::high_resolution_clock::now();
	cout << mp.size() << '\n';
	cout << chrono::duration_cast<chrono::milliseconds>(t2 - t1).count() << '\n';
	vector<pair<string, int>> vec;
	for (auto& x : mp)
	{
		vec.emplace_back(x.first, x.second);
	}
	sort(vec.begin(), vec.end(), [](auto& x, auto& y) {return x.second > y.second; });
	for (int i = 0; i < 50; i++)
	{
		std::cout << vec[i].first << " - " << vec[i].second << "\n";
	}
}

void realize_unordered_map_second()
{
	unordered_map<string, int> mp;
	chrono::high_resolution_clock::time_point t1 = chrono::high_resolution_clock::now();
	std::ifstream in("War and Peace.txt");
	if (in.is_open())
	{
		string s;
		while (in >> s)
		{
			if (s.back() < 'a' || s.back() > 'z')
			{
				s.pop_back();
				while (s.length() > 0 && (s.back() < 'a' || s.back() > 'z'))
				{
					s.pop_back();
				}

			}
			while (s.length() > 0 && !('A' <= s[0] && s[0] <= 'z'))
				s.erase(0);

			if (!s.empty() && 'A' <= s[0] && s[0] <= 'Z')
				mp[s]++;
		}

	}
	else
	{
		cout << "Couldn't open file\n";
	}
	in.close();
	chrono::high_resolution_clock::time_point t2 = chrono::high_resolution_clock::now();
	cout << mp.size() << '\n';
	cout << chrono::duration_cast<chrono::milliseconds>(t2 - t1).count() << '\n';
	vector<pair<string, int>> vec;
	for (auto& x : mp)
	{
		vec.emplace_back(x.first, x.second);
	}
	sort(vec.begin(), vec.end(), [](auto& x, auto& y) {return x.second > y.second; });
	for (int i = 0; i < 50; i++)
	{
		std::cout << vec[i].first << " - " << vec[i].second << "\n";
	}
}

void realize_unordered_map_third()
{

	unordered_map<string, int> mp;
	chrono::high_resolution_clock::time_point t1 = chrono::high_resolution_clock::now();
	std::ifstream in("War and Peace.txt");
	if (in.is_open())
	{
		string s;
		while (in >> s)
		{
			if (s.back() < 'a' || s.back() > 'z')
			{
				s.pop_back();
				while (s.length() > 0 && (s.back() < 'a' || s.back() > 'z'))
				{
					s.pop_back();
				}

			}
			while (s.length() > 0 && !('A' <= s[0] && s[0] <= 'z'))
				s.erase(0);

			if (s.length() > 0 && 'A' <= s[0] && s[0] <= 'Z')
				s[0] += 32;
			sort(s.begin(), s.end());
			if (!s.empty())
				mp[s]++;
		}

	}
	else
	{
		cout << "Couldn't open file\n";
	}
	in.close();
	chrono::high_resolution_clock::time_point t2 = chrono::high_resolution_clock::now();
	cout << mp.size() << '\n';
	cout << chrono::duration_cast<chrono::milliseconds>(t2 - t1).count() << '\n';
	vector<pair<string, int>> vec;
	for (auto& x : mp)
	{
		vec.emplace_back(x.first, x.second);
	}
	sort(vec.begin(), vec.end(), [](auto& x, auto& y) {return x.second > y.second; });
	for (int i = 0; i < 50; i++)
	{
		std::cout << vec[i].first << " - " << vec[i].second << "\n";
	}
}





//4 - 6

void print( string*& const arr, int n = 16)
{
	for (int i = 0; i < n; i++)
	{
		cout << arr[i] << ' ';
	}
	cout << '\n';
}

void split(string s, string* &arr)
{
	int n = 16;
	arr = new string[n];
	auto first = s.begin();
	auto g = s.begin();
	for (int i = 0; i < n; i++)
	{
		g = (find(g, s.end(), ','));
		arr[i] = s.substr(first - s.begin(), g - first);
		++g;
		first = g;
	}
}

//Name Platform Year_of_Release Genre Publisher NA_Sales EU_Sales JP_Sales
//Other_Sales Global_Sales Critic_Score Critic_Count User_Score
//User_Count Developer Rating;
//Задача 4. На основе приведённой базы компьютерных игр для каждого издателя указать суммарный доход по различным жанрам игр.
void fourth()
{
	ifstream ifs("Video_Games.csv");
	string s;
	unordered_map<string, map<string, double>> mp;
	getline(ifs, s);
	while (getline(ifs, s))
	{
		string* arr;
		split(s, arr);
		mp[arr[4]][arr[3]] += atof(arr[9].c_str());
	//	cout<<arr[0]<<" " << arr[9] << '\n';

		delete[] arr;
	}
	for (auto x : mp)
	{
		double sum = 0;
		cout << "Publisher: " << x.first << '\n';
		for(auto y : x.second)
		{
			//cout<<"     " << y.first << " " << y.second << '\n';
			sum += y.second;
		}
		cout<<"     "  << "Sum: " << sum << '\n';
	}
	ifs.close();
	
}
//Wii Sports,Wii,2006,Sports,Nintendo
//41.36 28.96 3.77 8.45 82.53,76,51,8,322,Nintendo,E
int main()
{
	fourth();
}
