#include <iostream>
#include <queue>
#include <vector>


using namespace  std;

int n, m;
int* dist;
bool* used;
int* trace;
int** mas;

void Dejkstra(const int& s = 0)
{
	
	priority_queue<int> q;
	dist[s] = 0;
	q.push(s);
	while (!q.empty()) {
		{
			int current = q.top();
			q.pop();
			//что-то
			used[current] = true;

			for (int y = 0; y < m; y++)
			{
				if (mas[current][y] >= 0)
					if (dist[current] + mas[current][y] < dist[y])
					{
						dist[y] = dist[current] + mas[current][y];
						trace[y] = current;
						q.push(y);
					}
			}
		}
	}
}

void print_test()
{
	if (trace[n - 1] == -1)
	{
		cout << -1 << '\n';
		return;
	}
	vector<int> vec;
	vec.push_back(n - 1);
	while (vec.back() != -1)
	{
		vec.push_back(trace[vec.back()]);
	}
	vec.pop_back();
	reverse(vec.begin(), vec.end());

	for (auto value : vec)
	{
		cout << value + 1 << ' ';
	}
}

int main()
{
	cin >> n >> m;
	dist = new int[n];
	used = new bool[n];
	trace = new int[n];
	for (int i = 0; i < n; i++) 
	{
		dist[i] = INT32_MAX;
		used[i] = false;
		trace[i] = -1;
	}
	mas = new int* [n];
	for (int i = 0; i < n; i++)
	{
		mas[i] = new int[n];
		for (int j = 0; j < n; j++)
		{
			mas[i][j] = -1;
		}
	}


	for(int i = 0;i<m;i++)
	{
		int a, b,cost;
		cin >> a >> b>>cost;
		a--; b--;
		mas[a][b] = cost;
		mas[b][a] = cost;		
	}
	Dejkstra(0);

	print_test();
}
