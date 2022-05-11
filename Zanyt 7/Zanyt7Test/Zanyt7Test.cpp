#include "pch.h"
#include "CppUnitTest.h"
#include "../Zanyt 7/unordered_set.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Zanyt7Test
{
	TEST_CLASS(Zanyt7Test)
	{
	public:
		
		TEST_METHOD(TestInsert)
		{
			my::unordered_set<int> st;
			st.insert(1);
			Assert::IsTrue(st.get_size() == 1);
			st.insert(2);
			Assert::IsTrue(st.get_size() == 2);
			st.insert(3);
			Assert::IsTrue(st.get_size() == 3);
			st.insert(5);
			Assert::IsTrue(st.get_size() == 4);
			st.insert(5);
			Assert::IsTrue(st.get_size() == 4);
		}
		TEST_METHOD(TestErase)
		{
			my::unordered_set<int> st;
			st.insert(1);
			Assert::IsTrue(st.get_size() == 1);
			st.erase(1);
			Assert::IsTrue(st.get_size() == 0);
			for (int i = 1; i <= 1000; i++)
			{
				st.insert(i);
			}
			Assert::IsTrue(st.get_size() == 1000);
			for (int i = 1; i <= 500; i++)
			{
				st.erase(i);
			}
			Assert::IsTrue(st.get_size() == 500);
			for (int i = 1; i <= 500; i++)
			{
				st.erase(i);
			}
			Assert::IsTrue(st.get_size() == 500);

			for (int i = 500; i <= 1000; i++)
			{
				st.erase(i);
			}
			Assert::IsTrue(st.get_size() == 0);

			for (int i = 1; i <= 2000; i++)
			{
				st.insert(i);
			}
			Assert::IsTrue(st.get_size() == 2000);
			for (int i = 1; i <= 2000; i++)
			{
				st.erase(i);
			}
			Assert::IsTrue(st.get_size() == 0);
		}
		TEST_METHOD(TestHas)
		{
			my::unordered_set<int> st;
			for (int i = 1; i <= 1000; i++)
			{
				st.insert(i);
			}
			for (int i = 1; i <= 1000; i++)
			{
				Assert::IsTrue(st.has(i));
			}
			for (int i = 1001; i < 2000; i++)
			{
				Assert::IsFalse(st.has(i));
			}
		}
		TEST_METHOD(TestFull)
		{
			my::unordered_set<int> st;
			for (int i = 1; i <= 2000; i++)
			{
				st.insert(i);
			}
			Assert::IsTrue(st.get_size() == 2000);
			for (int i = 1; i <= 2000; i++)
			{
				Assert::IsTrue(st.has(i));
			}

		}
	};
}
