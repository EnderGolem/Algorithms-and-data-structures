#include<iostream>
#include<queue>
#include<vector>
#include<list>
#include "priority_queue.h"

using namespace std;

int main()
{
	my::priority_queue<int > sf;
	int a[7] = { 3,8,2,8,1,4,9};

	sf.build_heap(a, 7);
	sf.print();
	
	int b[5] = {4,5,0,2,5};
	my::priority_queue<int > fs;
	fs.build_heap(b, 5);
	fs.print();
	sf.merge(fs);
	sf.print();
	
}