#include <chrono>
#include <iostream>
#include <fstream>
#include <map>
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
		while(in>>s)
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
	if(in.is_open())
	{
		
		string s;
		while(in>>s)
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
	if(in.is_open())
	{
		
		
		char c;
		while(in.peek()  != EOF)
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
	cout <<"Time " << chrono::duration_cast<chrono::milliseconds>(t2 - t1).count() << '\n';

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
		while (in>>s)
		{
			if (s.back() < 'a' || s.back() > 'z')
			{
				s.pop_back();
				while (s.length() > 0 && (s.back() < 'a' || s.back() > 'z'))
				{
					s.pop_back();
				}

			}
			while(s.length() > 0 && !( 'A' <= s[0] && s[0] <= 'z') )
				s.erase(0);
			
			if(s.length() > 0  && 'A' <= s[0] && s[0] <= 'Z')			
				s[0] += 32;
			
			if(!s.empty())
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
			while (s.length() > 0 && !('A' <= s[0] && s[0] <= 'z') )			
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


int main()
{
	realize_unordered_map_third();
}
