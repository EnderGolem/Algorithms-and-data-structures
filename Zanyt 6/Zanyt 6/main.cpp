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
	//VASHNO препод, сказал, что можно использовать кучу, для того, чтобы сократить время, не создавая вектор
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
//VASHNO неправильно релизованно
void realize_unordered_map_third()
{

	unordered_map<string, vector<string>> mp;
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
				s[0] += 32;  //VASHNO такое не желательно это быстрее, но если будет другой алфавит, то все сломается, плюс например ё находится вообще хрен знает где
			string s_not_sort = s;
			sort(s.begin(), s.end());
			if (!s.empty())
				mp[s].push_back(s_not_sort);
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
	vector<pair<string, vector<string>>> vec;
	for (auto& x : mp)
	{
		vec.emplace_back(x.first, x.second);
	}
	sort(vec.begin(), vec.end(), [](auto& x, auto& y) {return x.second.size() > y.second.size(); });
	cout << vec[0].first << '\n';
	for (auto x : vec[0].second)
	{
		cout << x << '\n';
	}
}





//4 - 6

void print(string*& const arr, int n = 16)
{
	for (int i = 0; i < n; i++)
	{
		cout << arr[i] << '|';
	}
	cout << '\n';
}
void split(string s, string*& arr)
{
	int n = 1;
	auto g = s.begin();
	while (true)
	{

		g = (find(g, s.end(), ','));
		if (g == s.end())
			break;
		++g;
		n++;
	}
	arr = new string[16];
	auto first = s.begin();
	g = s.begin();
	string fir = "";
	string sec = "";
	string thi = "";
	while (true)
	{

		fir += sec;
		sec = thi;
		g = (find(g, s.end(), ','));
		thi = s.substr(first - s.begin(), g - first);
		++g;
		first = g;
		if (thi == "N/A" || thi.length() == 4 && isdigit(thi[0]) && isdigit(thi[1]) && isdigit(thi[2]) && isdigit(thi[3]))
			break;


	}

	arr[0] = fir;
	arr[1] = sec;
	arr[2] = thi;
	for (int i = 3; i < 14; i++)
	{
		g = (find(g, s.end(), ','));
		arr[i] = s.substr(first - s.begin(), g - first);
		++g;
		first = g;
	}

	auto r = s.find_last_of(',');
	arr[14] = s.substr(first - s.begin(), r - (first - s.begin()));
	arr[15] = s.substr(r + 1);
}
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

		delete[] arr;
	}
	for (auto x : mp)
	{
		double sum = 0;
		cout << "Publisher: " << x.first << '\n';
		for (auto y : x.second)
		{
			sum += y.second;
		}
		cout << "     " << "Sum: " << sum << '\n';
	}
	ifs.close();

}

//Задача 5. Вычислить наиболее доходный жанр игровой индустрии по каждому году. 
void fifth()
{
	ifstream ifs("Video_Games.csv");
	string s;
	unordered_map<string, map<string, double>> mp;
	getline(ifs, s);
	while (getline(ifs, s))
	{
		string* arr;
		split(s, arr);
		mp[arr[2]][arr[3]] += atof(arr[9].c_str());
		delete[] arr;
	}
	for (auto x : mp)
	{
		string ans = "S";
		cout << "Year: " << x.first << '\n';
		for (auto y : x.second)
		{
			if (y.second > mp[x.first][ans])
			{
				ans = y.first;
			}
		}
		cout << "     " << "Max income: " << ans << '\n';
	}
	ifs.close();

}


//Name, Platform, Year_of_Release, Genre, Publisher, NA_Sales, EU_Sales, JP_Sales, Other_Sales,
//Global_Sales, Critic_Score, Critic_Count, User_Score, User_Count, Developer, Rating

//Задача 6. Для каждого издателя выдать список из 5 наиболее доходных разработчиков (за всё время).
void six()
{
	ifstream ifs("Video_Games.csv");
	string s;
	unordered_map<string, map<string, double>> mp;
	getline(ifs, s);
	while (getline(ifs, s))
	{
		string* arr;
		split(s, arr);
		mp[arr[4]][arr[14]] += atof(arr[9].c_str());
		delete[] arr;
	}
	for (auto x : mp)
	{
		cout << "Publisher: " << x.first << '\n';
		vector < pair < string, double >> vec;
		for (auto y : x.second)
		{
			vec.push_back({ y.first,y.second });
		}
		sort(vec.begin(), vec.end(), [](auto& x, auto& y) {return x.second > y.second; });
		for (int i = 0; i < min(5, static_cast<int>(vec.size())); i++)
		{
			cout << "      " << vec[i].first << " " << vec[i].second << '\n';
		}
	}
	ifs.close();

}


void print_mine(string s)
{
	string* arr;
	split(s, arr);
	print(arr, 16);
}

int main()
{
	//realize_unordered_map_first();
	//realize_unordered_map_second();
	//realize_unordered_map_third();

	//print_mine("Game Pons,WiiU,2012,Action,Warnerment,0.09,0.03,0,0.01,0.13,24,8,3.5,21,\"Phosphor Games Studio, LLC\",E");
	//fourth();
	//fifth();
	//six();
}

//Madden NFL 2004,PS2,N/A,Sports,Electronic Arts,4.26,0.26,0.01,0.71,5.23,94,29,8.5,140,EA Tiburon,E
//Men of War : Assault Squad, PC, 2011, Strategy, 1C Company, 0.01, 0.03, 0, 0.01, 0.05, 77, 21, 8.2, 93, "THQ, 1C, 1C Company", T
//Game Party: Champions,WiiU,2012,Action,Warner Bros. Interactive Entertainment,0.09,0.03,0,0.01,0.13,24,8,3.5,21,"Phosphor Games Studio, LLC",E