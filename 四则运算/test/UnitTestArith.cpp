#include "pch.h"
#include "CppUnitTest.h"

#define private public
#include "../arithmetic/arith.h"
#include"../arithmetic/main.cpp"
#include"../arithmetic/arith.cpp"
# undef private

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace ArithClassTest
{
	TEST_CLASS(FractionTests)
	{
	public:

		TEST_METHOD(TestMethod_get_str_fra)
		{
			Fraction f(25, 4);
			Assert::AreEqual(std::string("6'1/4"), f.get_str_fra());
		}
		TEST_METHOD(Test_get_frac)
		{
			int num = 6;
			int den = 5;
			Fraction f(num, den);
			float res = (float)num / (float)den;
			Assert::AreEqual(res, f.get_frac());
		}

	};
	TEST_CLASS(QuestionTests)
	{
	public:
		TEST_METHOD(TestMethod_ConstructorQuestion1)
		{
			Question q(10, 3);
			Assert::AreEqual(q.range, 10);
			Assert::AreEqual(q.num, 3);
			Assert::AreEqual((int)q.data.size(), 3);

		}
		TEST_METHOD(TestMethod_ADD)
		{
			std::string s("1. 1/2 + 2/3 =");
			std::istringstream iss(s);
			std::vector<std::string> words;
			std::string word;
			while (iss >> word)
			{
				words.push_back(word);
			}
			Question q(words);
			std::string res("1'1/6");
			Fraction f(7, 6);
			Assert::IsTrue(res == q.res);
			Assert::IsTrue(f == q.result);
		}
		TEST_METHOD(TestMethod_SUB)
		{
			std::string s("1. 2/3 - 1/2 =");
			std::istringstream iss(s);
			std::vector<std::string> words;
			std::string word;
			while (iss >> word)
			{
				words.push_back(word);
			}
			Question q(words);
			std::string res("1/6");
			Fraction f(1, 6);
			Assert::IsTrue(res == q.res);
			Assert::IsTrue(f == q.result);
		}
		TEST_METHOD(TestMethod_MUL)
		{
			std::string s("1. 1/2 ¡Á 2/3 =");
			std::istringstream iss(s);
			std::vector<std::string> words;
			std::string word;
			while (iss >> word)
			{
				words.push_back(word);
			}
			Question q(words);
			std::string res("1/3");
			Fraction f(1, 3);
			Assert::IsTrue(res == q.res);
			Assert::IsTrue(f == q.result);
		}
		TEST_METHOD(TestMethod_DIV)
		{
			std::string s("1. 1/2 ¡Â 2/3 =");
			std::istringstream iss(s);
			std::vector<std::string> words;
			std::string word;
			while (iss >> word)
			{
				words.push_back(word);
			}
			Question q(words);
			std::string res("3/4");
			Fraction f(3, 4);
			Assert::IsTrue(res == q.res);
			Assert::IsTrue(f == q.result);
		}
	};
}
