#include <iostream>
#include <assert.h>
#include "BinaryTree.h"

using namespace  std;

void testIterator()
{
	cout << "Test iterator\n";
	BinaryTree<int> bt;
	bt.insert(10);
	bt.insert(5);
	bt.insert(15);
	bt.insert(2);
	bt.insert(7);
	bt.insert(1);
	bt.insert(3);
	bt.insert(4);


	bt.insert(12);
	bt.insert(18);
	bt.insert(11);
	bt.insert(13);
	bt.insert(16);
	bt.insert(19);


	bt.printByLevels();
	bt.printLKP();
	auto g = bt.first();
	; assert(*g == 1);
	++g;
	assert(*g == 2);
	++g;
	assert(*g == 3);
	++g;
	assert(*g == 4);
	++g;
	assert(*g == 5);
	++g;
	assert(*g == 7);
	++g;
	assert(*g == 10);
	++g;
	assert(*g == 11);
	++g;
	assert(*g == 12);
	++g;
	assert(*g == 13);
	g++;
	assert(*g == 15);
	g++;
	assert(*g == 16);
	++g;
	assert(*g == 18);
	++g;
	assert(*g == 19);
	bt.printPKL();
	assert(*g == 19);
	--g;
	assert(*g == 18);
	--g;
	assert(*g == 16);
	--g;
	assert(*g == 15);
	--g;
	assert(*g == 13);
	--g;
	assert(*g == 12);
	--g;
	assert(*g == 11);
	--g;
	assert(*g == 10);
	--g;
	assert(*g == 7);
	--g;
	assert(*g == 5);
	--g;
	assert(*g == 4);
	--g;
	assert(*g == 3);
	--g;
	assert(*g == 2);
	--g;
	assert(*g == 1);
}

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
		cout << bt1.equalTo(bt2) << '\n';
		bt2.insert(8);
		cout << bt1.equalTo(bt2) << '\n';
		BinaryTree<int> bt3;
		bt3.insert(3);
		cout << bt1.equalTo(bt3) << '\n';
		BinaryTree<int> bt4;
		cout << bt1.equalTo(bt4) << '\n';
	}

	{
		testIterator();
	}
	system("pause");
}
