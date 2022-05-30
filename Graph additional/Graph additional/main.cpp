#include <algorithm>
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







//https://www.codingame.com/ide/puzzle/electrical-grid
vector<pair<pair<int, int>, int>> electical_grid(int n, vector < vector < pair<int, int> > > g)
{

	vector<int> min_e(n, INF), sel_e(n, -1);
	vector<bool> used(n);
	min_e[0] = 0;
	
	set < pair<int, int> > q;
	vector<pair<pair<int, int>, int>> ans;
	q.insert(make_pair(0, 0));
	while(!q.empty()){

		int v = q.begin()->second;
		int cost_f = q.begin()->first;
		q.erase(q.begin());

		if (sel_e[v] != -1 && !used[v]) {
			ans.push_back({ { min(v,sel_e[v]),max(sel_e[v],v)}, cost_f });
			used[v] = true;
		}

		for (size_t j = 0; j < g[v].size(); ++j) {
			int to = g[v][j].first,
				cost = g[v][j].second;
			if (cost < min_e[to]) {
				q.erase(make_pair(min_e[to], to));
				min_e[to] = cost;
				sel_e[to] = v;
				q.insert(make_pair(min_e[to], to));
			}
		}
	}
	return ans;
}

void electical_grid_enter()
{
	int n;
	int m;
	cin >> n >> m;
	vector < vector < pair<int, int> > > sf(n);
	for (int i = 0; i < m; i++) {
		int house_1;
		int house_2;
		int cost;
		cin >> house_1 >> house_2 >> cost; cin.ignore();
		house_1--; house_2--;
		sf[house_1].push_back({ house_2,cost });
		sf[house_2].push_back({ house_1,cost });
	}
	//cout << '\n';
	auto r = electical_grid(n, sf);
	sort(r.begin(), r.end());
	//cout << '\n';
	int sum = 0;
	for (int i = 0; i < r.size(); i++)
		sum += r[i].second;
	cout << r.size() << " " << sum << '\n';

	for (int i = 0; i < r.size(); i++)
	{
		cout << r[i].first.first + 1 << " " << r[i].first.second + 1 << " " << r[i].second << '\n';
	}
}

int main()
{
	electical_grid_enter();
}