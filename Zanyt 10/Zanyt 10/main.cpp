#include <iostream>
#include <vector>


using namespace  std;

int n, m;
int* dist;
bool* used;
int** a;

void Dejkstra(const int &s = 0)
{
	dist[s] = 0;
	for (int i = 0; i < n; i++)
	{
		int current = 0;
		for (int j = 0; j < n; j++)
		{
			if (!used[j] && dist[current] > dist[j])
				j = current;
		}
		if(dist[current] == INT32_MAX)
			break;
		used[current] = true;
		
		for (int y = 0; y < m; y++)
		{
			if(a[current][y] >= 0)
				dist[y] = min(dist[y], dist[current] + a[current][y]);
		}
	}
}

int main()
{
	dist = new int[n];
	used = new bool[n];
	for (int i = 0; i < n; i++) {
		dist[i] = INT32_MAX;
		used[i] = false;
	}
	a = new int* [m];
	for (int i = 0; i < m; i++)
	{
		a[i] = new int[m];
		for (int j = 0; j < m; j++)
		{
			a[i][j] = -1;
		}
	}
	

}