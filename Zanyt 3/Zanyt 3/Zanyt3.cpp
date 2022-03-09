#include <iostream>
#include <assert.h>
#include <chrono>
#include <fstream>
#include <set>

#include "BinaryTree.h"
#include "BinarySet.h"

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
	assert(*g == 1);
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

void TestContainsMinMax()
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
	assert(bt.contains(4));
	assert(bt.contains(20));
	assert(!bt.contains(2));
	assert(!bt.contains(100));
	cout << "Test min max first time\n";
	assert(bt.minElement() == 4);
	assert(bt.maxElement() == 20);
	cout << "Test min max second time\n";
	bt.insert(30);
	bt.insert(1);
	assert(bt.minElement() == 1);
	assert(bt.maxElement() == 30);
}

void testLowerUpper()
{
	BinaryTree<int> bt;
	bt.insert(10);
	bt.insert(5);
	bt.insert(15);
	bt.insert(12);
	bt.insert(20);
	bt.insert(21);
	bt.printLKP();
	cout << "Test lower bound\n";
	cout << bt.lowerBound(15) << '\n';
	cout << bt.lowerBound(17) << '\n';
	cout << "Test upper bound\n";
	cout << bt.upperBound(15) << '\n';
	cout << bt.upperBound(17) << '\n';
}

void testErase()
{
	cout << "erase\n";
	{
		BinaryTree<int> bt({ 5,4,10,12,7,9,8 });
		bt.printLKP();
		bt.erase(10);
		bt.printLKP();
	}
	{
		BinaryTree<int> bt({ 10,5,4,6 });
		bt.printByLevels();
		bt.printLKP();
		bt.erase(5);
		bt.printByLevels();
		bt.printLKP();
	}
}

void testPrintPKL()
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

void testEqualTo()
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
	assert(bt1.equalTo(bt2));
	bt2.insert(8);
	assert(!bt1.equalTo(bt2));
	BinaryTree<int> bt3;
	bt3.insert(3);
	assert(!bt1.equalTo(bt3));
	BinaryTree<int> bt4;
	assert(!bt1.equalTo(bt4));
}

void testPrintByLevels()
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
void testFor()
{
	BinaryTree<int> bt;
	bt.insert(5);
	bt.insert(1);
	bt.insert(6);
	for (auto x : bt)
	{
		cout << x << ' ';
	}
}
int* massive;
void eratosphenMassive(int n)
{
	
	for (int i = 2; i <= n; i++)
	{
		if (massive[i] == 1)
			for (int y = i + i; y <= n; y += i)
			{
				massive[y] = 0;
			}
	}

}

BinarySet<int> binaries;
void eratosphenBinarySetRegular(int n)
{
	
	for (int i = 2; i <= n; i++)
	{
		for (int y = i + i; y <= n; y += i)
		{
			binaries.erase(y);
		}
	}
	
}

set<int> usualSet;
void eratosphenBinarySetStandart(int n)
{
	for (int i = 2; i <= n; i++)
	{
		for (int y = i + i; y <= n; y += i)
		{
			usualSet.erase(y);
		}
	}
	
}
long double  test(void (*F)(int), int n)
{
	int	count = 10;
	chrono::high_resolution_clock::time_point t1 = chrono::high_resolution_clock::now();
	for(int i = 0;i < count;i++)
	{
		F(n);
	}
	chrono::high_resolution_clock::time_point t2 = chrono::high_resolution_clock::now();
	long double duration = std::chrono::duration_cast<chrono::milliseconds>(t2 - t1).count();
	cout << duration / count << '\n';
	return (duration) / count;
}

void createTable()
{
	ofstream out("results.csv");
	out << "Massive;BinarySet;Set;\n";
	for (int i = 100; i < 1e8; i*=10) {
		out << i << ";";
		cout << i << '\n';
		massive = new int[i + 1];
		for (int element = 1; element <= i; element++)
		{
			massive[element] = 1;
		}
		binaries = BinarySet<int>();
		for (int element = 1; element <= i; element++)
		{
			binaries.add(element);
		}

		for (int element = 1; element <= i; element++)
		{
			usualSet.insert(element);
		}
		auto f = test(eratosphenMassive, i); out << f << ";";
		f = test(eratosphenBinarySetRegular, i); out << f << ";";
		f = test(eratosphenBinarySetStandart, i); out << f << "; \n";
		


	}


	out.close();
	system("results.csv");
	system("pause");
}
int main()
{


	/*
	TestContainsMinMax();
	testLowerUpper();
	testErase();
	testPrintPKL();
	testPrintByLevels();
	testEqualTo();
	testIterator();
	testFor();*/
	createTable();
	system("pause");
}
