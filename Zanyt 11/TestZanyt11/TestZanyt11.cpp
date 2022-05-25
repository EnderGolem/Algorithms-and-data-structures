#include "pch.h"
#include "CppUnitTest.h"
#include "..\Zanyt 11/function.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace std;

namespace TestZanyt11
{
	TEST_CLASS(TestZanyt11)
	{
	public:
		TEST_METHOD(TestPrefixFunction1)
		{
			std::vector<int> sf;
			sf = prefix_function("ab", "abcabc");
			Assert::IsTrue(sf == vector<int>({ 1, 2, 0, 1, 2, 0 }));
			sf = prefix_function("abc", "abcabc");
			Assert::IsTrue(sf == vector<int>({ 1, 2, 3, 1, 2, 3 }));
			sf = prefix_function("abcdddd", "abcabc");
			Assert::IsTrue(sf == vector<int>({ 1, 2, 3, 1, 2, 3 }));

			sf = prefix_function("ab", "%%cabc");
			Assert::IsTrue(sf == vector<int>({ 0, 0, 0, 1, 2, 0 }));
			sf = prefix_function("abc", "&&cabc");
			Assert::IsTrue(sf == vector<int>({ 0, 0, 0, 1, 2, 3 }));
			sf = prefix_function("abcdddd", "&&cabc");
			Assert::IsTrue(sf == vector<int>({ 0, 0, 0, 1, 2, 3 }));
		}

		TEST_METHOD(TestPrefixFunction2)
		{
			std::vector<int> sf;
			sf = prefix_function("a", "aaaa");
			Assert::IsTrue(sf == vector<int>({ 1, 1, 1, 1 }));
			sf = prefix_function("ab", "aaaa");
			Assert::IsTrue(sf == vector<int>({ 1, 1, 1, 1 }));
			sf = prefix_function("abc", "aaaa");
			Assert::IsTrue(sf == vector<int>({ 1, 1, 1, 1 }));
			sf = prefix_function("aaaa", "aaaa");
			Assert::IsTrue(sf == vector<int>({ 1, 2, 3, 4 }));
			sf = prefix_function("abaaa", "aaaa");
			Assert::IsTrue(sf == vector<int>({ 1, 1, 1, 1 }));
			sf = prefix_function("abcaaaa", "aaaa");
			Assert::IsTrue(sf == vector<int>({ 1, 1, 1, 1 }));

			sf = prefix_function("a", "%aaaa");
			Assert::IsTrue(sf == vector<int>({ 0, 1, 1, 1, 1 }));
			sf = prefix_function("ab", "%aaaa");
			Assert::IsTrue(sf == vector<int>({ 0, 1, 1, 1, 1 }));
			sf = prefix_function("abc", "%aaaa");
			Assert::IsTrue(sf == vector<int>({ 0, 1, 1, 1, 1 }));
			sf = prefix_function("aaaa", "%aaaa");
			Assert::IsTrue(sf == vector<int>({ 0, 1, 2, 3, 4 }));
			sf = prefix_function("abaaa", "%aaaa");
			Assert::IsTrue(sf == vector<int>({ 0, 1, 1, 1, 1 }));
			sf = prefix_function("abcaaa", "%aaaa");
			Assert::IsTrue(sf == vector<int>({ 0, 1, 1, 1, 1 }));
		}


		TEST_METHOD(TestFind_Subs1)
		{
			std::vector<int> sf;
			sf = find_subs("ab", "abcabc");
			Assert::IsTrue(sf == vector<int>({ 0, 3 }));
			sf = find_subs("abc", "abcabc");
			Assert::IsTrue(sf == vector<int>({ 0, 3 }));
			sf = find_subs("abcdddd", "abcabc");
			Assert::IsTrue(sf == vector<int>({}));

			sf = find_subs("ab", "%%cabc");
			Assert::IsTrue(sf == vector<int>({ 3 }));
			sf = find_subs("abc", "&&cabc");
			Assert::IsTrue(sf == vector<int>({ 3 }));
			sf = find_subs("abcdddd", "&&cabc");
			Assert::IsTrue(sf == vector<int>({}));
		}

		TEST_METHOD(TestFind_Subs2)
		{
			std::vector<int> sf;
			sf = find_subs("a", "aaaa");
			Assert::IsTrue(sf == vector<int>({ 0, 1, 2, 3 }));
			sf = find_subs("ab", "aaaa");
			Assert::IsTrue(sf == vector<int>({}));
			sf = find_subs("abc", "aaaa");
			Assert::IsTrue(sf == vector<int>({}));
			sf = find_subs("aaaa", "aaaa");
			Assert::IsTrue(sf == vector<int>({ 0 }));
			sf = find_subs("abaaa", "aaaa");
			Assert::IsTrue(sf == vector<int>({}));
			sf = find_subs("abcaaaa", "aaaa");
			Assert::IsTrue(sf == vector<int>({}));

			sf = find_subs("a", "%aaaa");
			Assert::IsTrue(sf == vector<int>({ 1,2,3,4 }));
			sf = find_subs("ab", "%aaaa");
			Assert::IsTrue(sf == vector<int>({}));
			sf = find_subs("abc", "%aaaa");
			Assert::IsTrue(sf == vector<int>({ }));
			sf = find_subs("aaaa", "%aaaa");
			Assert::IsTrue(sf == vector<int>({ 1 }));
			sf = find_subs("abaaa", "%aaaa");
			Assert::IsTrue(sf == vector<int>({}));
			sf = find_subs("abcaaa", "%aaaa");
			Assert::IsTrue(sf == vector<int>({}));
		}
	};
}
