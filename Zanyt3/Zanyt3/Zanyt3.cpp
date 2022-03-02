﻿#include <iostream>
#include "BinaryTree.h"

using namespace  std;

int main()
{
	{
		BinaryTree<int> bt;
		bt.insert(5);
		bt.insert(4);
		bt.insert(20);
		bt.insert(10);
		bt.insert(7);
		bt.insert(8);
		bt.printLKP();
		cout << "Test contains\n";
		cout << bt.contains(4) << '\n';
		cout << bt.contains(20) << '\n';
		cout << bt.contains(2) << '\n';
		cout << "Test min max first time\n";
		cout << bt.minElement() << '\n';
		cout << bt.maxElement() << '\n';
		cout << "Test min max second time\n";
		bt.insert(30);
		bt.insert(1);
		cout << bt.minElement() << '\n';
		cout << bt.maxElement() << '\n';
	}
	{
		BinaryTree<int> bt;
		bt.insert(10);
		bt.insert(5);
		bt.insert(15);
		bt.insert(12);
		bt.insert(20);
		bt.insert(21);
		cout << "Test lower bound\n";
		cout << bt.lowerBound(15) << '\n';
		cout << bt.lowerBound(17) << '\n';
		
	}
	system("pause");
}