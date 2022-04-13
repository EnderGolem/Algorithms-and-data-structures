#include <algorithm>
#include <iostream>
#include <map>
#include <stack>
#include <unordered_map>








using namespace  std;


void correct_budget(int& n, int& cost, int*& budgets, int*& ans, int& sum_b, int i)
{
	int b = budgets[i];
	int extra = (sum_b - cost) / (n - i);
	int reminder = (sum_b - cost) - extra * (n - i);
	for (int y = i; y < i + reminder; y++)
	{
		ans[y] = budgets[i] - extra - 1;
	}
	for (int y = i + reminder; y < n; y++)
	{
		ans[y] = budgets[i] - extra;
	}
}

//https://www.codingame.com/training/medium/the-gift
void the_gift()
{
	int n;
	cin >> n; cin.ignore();
	int cost;
	cin >> cost; cin.ignore();
	int* budgets = new int[n];
	int* ans = new int[n];
	int sum_b = 0;

	for (int i = 0; i < n; i++) {
		cin >> budgets[i];
		sum_b += budgets[i];
	}
	if (sum_b < cost)
	{
		cout << "IMPOSSIBLE\n";
		return;
	}

	sort(budgets, budgets + n);

	sum_b = budgets[0] * n;
	ans[0] = budgets[0];
	if (sum_b >= cost) {
		correct_budget(n, cost, budgets, ans, sum_b, 0);
	}
	else
		for (int i = 1; i < n; i++)
		{
			sum_b = sum_b + (budgets[i] - budgets[i - 1]) * (n - i);
			ans[i] = budgets[i];
			if (sum_b >= cost)
			{
				correct_budget(n, cost, budgets, ans, sum_b, i);
				break;
			}
		}
	for (int i = 0; i < n; i++)
	{
		cout << ans[i] << '\n';
	}
	cout << '\n';
	delete[] ans;
	delete[] budgets;


}

//https://www.codingame.com/training/medium/magic-stones
void magic_stones_ver1()
{
	int n;
	cin >> n; cin.ignore();
	map<int, int> levels;
	for (int i = 0; i < n; i++) {
		int level;
		cin >> level; cin.ignore();
		levels[level] ++;
	}
	int ans = 0;
	for (auto lv : levels)
	{
		if (lv.second / 2 != 0)
			levels[lv.first + 1] += lv.second / 2;    //Presumably, here O(logn)   , but we go for map for O(n * logn) => here O(n * logn * logn)
		levels[lv.first] = lv.second % 2;
		if (lv.second % 2 != 0)
			ans++;
	}
	cout << levels.size() << '\n';
	cout << ans << '\n';
}
//I think it is faster than ver1.
void magic_stones_ver2()
{
	int n;
	cin >> n; cin.ignore();
	map<int, int> levels;
	for (int i = 0; i < n; i++) {
		int level;
		cin >> level; cin.ignore();
		levels[level] ++;
	}
	stack<pair<int, int>> st;
	st.push({ 0,0 });
	for (auto it = levels.rbegin(); it != levels.rend(); ++it)
	{
		st.push({ it->first,it->second });
	}


	int ans = 0;
	while (st.top().first != 0)
	{
		ans += st.top().second % 2;
		auto t = st.top();
		st.pop();
		if (t.second > 0 && st.top().first != t.first + 1)
		{
			st.push({ t.first + 1,t.second / 2 });
		}
		else
		{
			st.top().second += (t.second / 2);
		}
	}
	cout << ans << '\n';
}
short min(short a, short b)
{
	if (a < b)
		return  a;
	return  b;
}
short rectangle[151][151];
int recur(short h, short w)
{
	
	if (h == 1) return rectangle[h][w] = w;
	if (w == h) return rectangle[h][w] = 1;
	int ans = INT16_MAX;
	
	for (short c = 1; c <= w / 2; c++) {
		if (rectangle[h][c] == 0)
			recur(h, c);
		if (rectangle[h][w - c] == 0)
			recur(h, w - c);
		ans = min(ans, rectangle[h][c] + rectangle[h][w - c]);
	}
	
	for (short c = 1; c <= h / 2; c++) {
		if (rectangle[c][w] == 0)
			recur(c, w);
		if (rectangle[h - c][w] == 0)
			recur(h - c, w);
		ans = min(ans, rectangle[c][w] + rectangle[h - c][w]);
	}


	return  rectangle[h][w] = ans;
}
//https://www.codingame.com/training/medium/goro-want-chocolate
void goro_want_chocolate()
{
	short h;
	short w;
	cin >> h >> w; cin.ignore();
	cout << recur(h, w) << '\n';
}
int main()
{
	goro_want_chocolate();
}