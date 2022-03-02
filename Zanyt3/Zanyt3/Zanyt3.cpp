#include <iostream>
#include "BinaryTree.h"

using namespace  std;

int main()
{
	BinaryTree<int> bt;
	bt.insert(5);
	bt.insert(4);
	bt.insert(100);
	bt.insert(50);
	bt.insert(7);
	bt.insert(8);
	bt.printLKP();
	cout << bt.contains(4)<<'\n';
	cout << bt.contains(50)<<'\n';
	cout << bt.contains(2)<<'\n';
}