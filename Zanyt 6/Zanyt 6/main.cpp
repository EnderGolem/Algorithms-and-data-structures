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
	cout << chrono::duration_cast<chrono::milliseconds>(t2 - t1).count() << '\n';

	tree.find_max();
	chrono::high_resolution_clock::time_point t3 = chrono::high_resolution_clock::now();
	cout << chrono::duration_cast<chrono::milliseconds>(t3 - t2).count() <<" "<< chrono::duration_cast<chrono::milliseconds>(t3 - t1).count() << '\n';
}

void realize_unordered_map()
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
			if(s.length() > 0 && 'A' <= s[0] && s[0] <= 'Z')
			{
				s[0] += 32;
			}
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
	cout << chrono::duration_cast<chrono::milliseconds>(t2 - t1).count() << '\n';
}

void find_replace(string &str, const string & substr)
{
	size_t f;
	while((f = str.find(substr)) != string::npos)
	{
		str.replace(f, substr.length(), "");
	}
}

void remove_delimers(string s)
{
	find_replace(s, ",");
	find_replace(s, ".");
	find_replace(s, "!");
	find_replace(s, "?");
	find_replace(s, " ");
}
void to_lower(std::string& str)
{
	transform(str.begin(), str.end(),str.begin() ,std::tolower);
}
void realize_unordered_map_not()
{
	unordered_map<string, int> mp;
	chrono::high_resolution_clock::time_point t1 = chrono::high_resolution_clock::now();
	std::ifstream in("War and Peace.txt");
	string s;
	for(in>>s;!in.eof();in>>s)
	{
		to_lower(s);
		remove_delimers(s);
		++mp[s];
	}
	in.close();
	chrono::high_resolution_clock::time_point t2 = chrono::high_resolution_clock::now();
	cout << chrono::duration_cast<chrono::milliseconds>(t2 - t1).count() << '\n';
}

int main()
{
	realize_unordered_map_not();
}
