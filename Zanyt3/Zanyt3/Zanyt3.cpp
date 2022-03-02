#include <iostream>
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
		cout << bt.contains(100) << '\n';
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
		cout << "Test upper bound\n";
		cout << bt.upperBound(15) << '\n';
		cout << bt.upperBound(17) << '\n';

	}
	{

		cout << "erase\n";
		BinaryTree<int> bt;
		bt.insert(5);
		bt.insert(4);
		bt.insert(10);
		bt.insert(12);
		bt.insert(7);
		bt.insert(9);
		bt.insert(8);
		bt.printLKP();
		bt.erase(10);
		bt.printLKP();

	}
	{
		cout << "printPKL\n";
		BinaryTree<int> bt;
		bt.insert(5);
		bt.insert(4);
		bt.insert(10);
		bt.insert(12);
		bt.insert(7);
		bt.insert(9);
		bt.insert(8);
		bt.printLKP();
		bt.printPKL();

	}
	{
		cout << "printByLevels\n";
		BinaryTree<int> bt;
		bt.insert(5);
		bt.insert(4);
		bt.insert(10);
		bt.insert(12);
		bt.insert(7);
		bt.insert(9);
		bt.insert(8);
		bt.printByLevels();
	}
	{
		cout << "equalTo\n";
		BinaryTree<int> bt1;
		bt1.insert(5);
		bt1.insert(4);
		bt1.insert(10);
		bt1.insert(12);
		bt1.insert(7);
		bt1.insert(9);
		bt1.insert(8);
		BinaryTree<int> bt2;
		bt2.insert(5);
		bt2.insert(4);
		bt2.insert(10);
		bt2.insert(12);
		bt2.insert(7);
		bt2.insert(9);
		bt2.insert(8);
		cout<<bt1.equalTo(bt2)<<'\n';
		bt2.insert(8);
		cout<<bt1.equalTo(bt2)<<'\n';
		BinaryTree<int> bt3;
		bt3.insert(3);
		cout << bt1.equalTo(bt3) << '\n';
		BinaryTree<int> bt4;
		cout << bt1.equalTo(bt4) << '\n';
	}
	system("pause");
}