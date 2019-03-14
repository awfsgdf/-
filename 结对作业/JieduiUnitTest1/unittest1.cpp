#include "stdafx.h"
#include "CppUnitTest.h"
#include "..\结对作业\interface.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace JieduiUnitTest1
{
	TEST_CLASS(UnitTest1)
	{
	public:

		TEST_METHOD(TestMethod1)
		{
			char* input[4] = { "END", "OF", "THE", "WORLD" };
			char* result[4] = { 0 };
			/* 调用Core中封装好的函数 */
			int len = gen_chain_word(input, 4, result, 0, 0, false);
			Assert::AreEqual(len, 2);
		}
		TEST_METHOD(TestMethod2)
		{
			char* input[11] = { "Algebra", "Apple", "Zoo", "Elephant", "Under", "Fox", "Dog", "Moon", "Leaf",
									"Trick", "Pseudopseudohypoparathyroidism" };
			char* result[11] = { 0 };
			/* 调用Core中封装好的函数 */
			int len = gen_chain_word(input, 11, result, 0, 0, false);
			Assert::AreEqual(len, 4);
		}
		TEST_METHOD(TestMethod3)
		{
			char* input[11] = { "Algebra", "Apple", "Zoo", "Elephant", "Under", "Fox", "Dog", "Moon", "Leaf",
									"Trick", "Pseudopseudohypoparathyroidism" };
			char* result[11] = { 0 };
			/* 调用Core中封装好的函数 */
			int len = gen_chain_char(input, 11, result, 0, 0, false);
			Assert::AreEqual(len, 2);
		}
		TEST_METHOD(TestMethod4)
		{
			char* input[5] = { "Element", "heaven", "Table", "Teach", "Talk" };
			char* result[5] = { 0 };
			/* 调用Core中封装好的函数 */
			int len = gen_chain_word(input, 5, result, 0, 0, true);
			Assert::AreEqual(len, 4);
		}
		TEST_METHOD(TestMethod5)
		{
			char* input[5] = { "Element", "heaven", "Table", "Teach", "Talk" };
			char* result[5] = { 0 };
			/* 调用Core中封装好的函数 */
			int len = gen_chain_char(input, 5, result, 0, 0, true);
			Assert::AreEqual(len, 4);
		}

		TEST_METHOD(TestMethod6)
		{
			char* input[11] = { "Algebra", "Apple", "Zoo", "Elephant", "Under", "Fox", "Dog", "Moon", "Leaf",
									"Trick", "Pseudopseudohypoparathyroidism" };
			char* result[11] = { 0 };
			/* 调用Core中封装好的函数 */
			int len = gen_chain_word(input, 11, result, 'a', 0, false);
			Assert::AreEqual(len, 4);
		}
		TEST_METHOD(TestMethod7)
		{
			char* input[11] = { "Algebra", "Apple", "Zoo", "Elephant", "Under", "Fox", "Dog", "Moon", "Leaf",
									"Trick", "Pseudopseudohypoparathyroidism" };
			char* result[11] = { 0 };
			/* 调用Core中封装好的函数 */
			int len = gen_chain_char(input, 11, result, 'a', 0, false);
			Assert::AreEqual(len, 4);
		}
		TEST_METHOD(TestMethod8)
		{
			char* input[11] = { "Algebra", "Apple", "Zoo", "Elephant", "Under", "Fox", "Dog", "Moon", "Leaf",
									"Trick", "Pseudopseudohypoparathyroidism" };
			char* result[11] = { 0 };
			/* 调用Core中封装好的函数 */
			int len = gen_chain_word(input, 11, result, 0, 'n', false);
			Assert::AreEqual(len, 2);
		}
		TEST_METHOD(TestMethod9)
		{
			char* input[11] = { "Algebra", "Apple", "Zoo", "Elephant", "Under", "Fox", "Dog", "Moon", "Leaf",
									"Trick", "Pseudopseudohypoparathyroidism" };
			char* result[11] = { 0 };
			/* 调用Core中封装好的函数 */
			int len = gen_chain_char(input, 11, result, 0, 'n', false);
			Assert::AreEqual(len, 2);
		}
		TEST_METHOD(TestMethod12)
		{
			char* input[5] = { "Element", "heaven", "Table", "Teach", "Talk" };
			char* result[5] = { 0 };
			/* 调用Core中封装好的函数 */
			int len = gen_chain_word(input, 5, result, 't', 0, true);
			Assert::AreEqual(len, 4);
		}
		TEST_METHOD(TestMethod13)
		{
			char* input[5] = { "Element", "heaven", "Table", "Teach", "Talk" };
			char* result[5] = { 0 };
			/* 调用Core中封装好的函数 */
			int len = gen_chain_char(input, 5, result, 't', 0, true);
			Assert::AreEqual(len, 4);
		}
		TEST_METHOD(TestMethod14)
		{
			char* input[5] = { "Element", "heaven", "Table", "Teach", "Talk" };
			char* result[5] = { 0 };
			/* 调用Core中封装好的函数 */
			int len = gen_chain_word(input, 5, result, 0, 'n', true);
			Assert::AreEqual(len, 4);
		}
		TEST_METHOD(TestMethod15)
		{
			char* input[5] = { "Element", "heaven", "Table", "Teach", "Talk" };
			char* result[5] = { 0 };
			/* 调用Core中封装好的函数 */
			int len = gen_chain_word(input, 5, result, 0, 'n', true);
			Assert::AreEqual(len, 4);
		}
	};
}