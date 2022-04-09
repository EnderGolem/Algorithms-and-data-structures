#include <algorithm>
#include <iostream>


using namespace  std;



void correct_budget(int &n, int &cost, int* &budgets, int* &ans, int &sum_b, int i)
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


}


int main()
{
	the_gift();
}