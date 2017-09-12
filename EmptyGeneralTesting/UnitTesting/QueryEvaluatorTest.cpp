#include "stdafx.h"
#include "CppUnitTest.h"
#include "../SPA/QPS/QueryEvaluator.h"
#include "../SPA/QPS/QueryObject.h"
#include "../SPA/QPS/QueryParser.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTesting
{
	TEST_CLASS(QueryEvaluatorTest)
	{
	public:

		TEST_METHOD(testQueryEvaluatorWithoutPKB)
		{
			QueryParser* qp;
			qp = new QueryParser();
			QueryObject queryObj = qp->getQueryObj("assign a; statement s; variable v; Select s such that Parent (2, s)");

			//Need a demo PKB 
			Logger::WriteMessage("Call PKB Stub");

			QueryEvaluator qe(queryObj);
			Result result = qe.getRawResult();
			string s = result.toString();
			Assert::AreEqual(s, (std::string)"");
			return;
		}
	};
}