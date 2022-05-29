#include <iostream>
#include <set>
#include <vector>
#include <math.h>
#include <cmath>

using namespace  std;

const int INF = INT32_MAX;
const int INS = INT32_MIN;
double distance(double a, double b)
{
	return sqrt(a * a + b * b);
}
double distance(pair<int, int> a, pair<int, int> b)
{
	return distance(abs(a.first - b.first), abs(a.second - b.second));
}

vector<double> mars_colonization(int& n, const	vector < vector<double> >& g)
{
	vector<double> ans(n);
	vector<bool> used(n);
	vector<double> min_e(n, INF), sel_e(n, -1);
	min_e[0] = 0;
	for (int i = 0; i < n; ++i) {
		int v = -1;
		for (int j = 0; j < n; ++j)
			if (!used[j] && (v == -1 || min_e[j] < min_e[v]))
				v = j;
		if (min_e[v] == INF) {
			exit(0);
		}

		used[v] = true;
		if (sel_e[v] != -1) {
			ans[v] = g[v][sel_e[v]];
		}

		for (int to = 0; to < n; ++to)
			if (g[v][to] < min_e[to]) {
				min_e[to] = g[v][to];
				sel_e[to] = v;
			}
	}
	return ans;
}
/*
7 4
1 1
1 6
3 3
3 5
6 1
6 3
6 6

 */
 //https://www.codingame.com/ide/puzzle/mars-colonization
void mars_colonization_enter()
{
	int n;
	int m;
	cin >> m >> n;
	vector<pair<int, int>> sf(m);
	for (int i = 0; i < m; i++)	
		cin >> sf[i].first >> sf[i].second;
	
	vector<vector<double>> mat(m, vector<double>(m, INF));
	for (int i = 0; i < m; i++)
	{
		for (int y = i + 1; y < m; y++)
		{
			mat[i][y] = distance(sf[i], sf[y]);
			mat[y][i] = distance(sf[i], sf[y]);
		}
	}
	auto vec = mars_colonization(m, mat);
	for (int i = 0; i < n - 1; i++)
	{
		int z = 0;
		for (int y = 0; y < m; y++)		
			if (vec[z] < vec[y])
					z = y;
		vec[z] = 0;
	}
	int z = 0;
	for (int y = 0; y < m; y++)	
		if (vec[z] < vec[y])		
			z = y;
		
	cout << fixed;
	cout.precision(2);
	cout << vec[z] << '\n';
}


int main()
{
	mars_colonization_enter();
}