#include "pch.h"

#include <set>
#include "..\Project1/AVL.h"
#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace TestTree
{
	TEST_CLASS(TestTree)
	{
	public:
		template<typename T> using Myal = std::allocator<T>;
		template<typename T> using Mypred = std::less<T>;

		//  Для того, чтобы выполнить тестирование одного из указанных контейнеров (std::set или Binary_Tree_Search)
		//    должна быть раскомментирована одна из следующих строк:
		//template<typename T> using ContainerTemplate = std::set<T, Mypred<T>, Myal<T>>;
		template<typename T> using ContainerTemplate = AVL<T, Mypred<T>, Myal<T>>;

		TEST_METHOD(TreeSizeTest)
		{
			//  Тестирование размера дерева при разных сценариях использования
			ContainerTemplate<int> T1;
			Assert::AreEqual(T1.size(), ContainerTemplate<int>::size_type(0), L"Пустое дерево имеет ненулевой размер!");
			ContainerTemplate<int> Tree = { 40,50,30,35,10,75,23,87,68 };
			Assert::AreEqual(Tree.size(), ContainerTemplate<int>::size_type(9), L"Неверно указывается размер дерева!");
			ContainerTemplate<int> Tree2(Tree);
			Assert::AreEqual(Tree.size(), Tree2.size(), L"Неверно указывается размер после копирования!");
		}
		
		TEST_METHOD(TreesEqualityTest)
		{
			//  Тестирование оператора == для дерева
			ContainerTemplate<int> T1, T2;
			Assert::IsTrue(T1 == T2, L"Неверно выполняется сравнение пустых деревьев!");
			ContainerTemplate<int> Tree = { 40,50,30,35,10,75,23,87,68 };
			ContainerTemplate<int> Tree2(Tree);
			Assert::IsTrue(Tree == Tree2, L"Ошибка сравнения деревьев на равенство после копирования!");			
			//TODO ContainerTemplate<int> Tree3(Tree.rbegin(), Tree.rend());
			ContainerTemplate<int> Tree3(Tree.begin(), Tree.end());
			Assert::IsTrue(Tree2 == Tree3, L"Ошибка сравнения деревьев на равенство после копирования в обратном порядке!");

			Logger::WriteMessage("Ого, кажется всё хорошо!");
		}
		
	};
}
