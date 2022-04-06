#include <chrono>
#include <iostream>
#include <fstream>
#include <map>
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
	cout << int('\r') << int('\n') << '\n';
	tree_for_words tree{};
	chrono::high_resolution_clock::time_point t1 = chrono::high_resolution_clock::now();
	std::ifstream in("War and Peace.txt");
	if(in.is_open())
	{
		
		
		char c;
		while(in.peek()  != EOF)
		{
			c = in.get();
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
}

int main()
{
	realize_set();
	//realize_tree_for_words_string();
}
