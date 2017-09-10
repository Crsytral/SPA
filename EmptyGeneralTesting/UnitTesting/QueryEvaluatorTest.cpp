#include "stdafx.h"
#include "CppUnitTest.h"
#include "../SPA/QPS/QueryEvaluator.h"
#include "../SPA/QPS/QueryObject.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTesting
{
	TEST_CLASS(QueryEvaluatorTest)
	{
	public:

		TEST_METHOD(testConstructor)
		{
			QueryObject query;
			QueryEvaluator qe(query);
			Result result = qe.getRawResult();
			string s = result.toString();
			Assert::AreEqual(s, (std::string)"");
			return;
		}
	};
}