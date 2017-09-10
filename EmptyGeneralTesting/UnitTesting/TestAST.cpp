#include "stdafx.h"
#include "CppUnitTest.h"
#include "../SPA/PKB/PKB.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTesting
{		
	TEST_CLASS(BasicPKB)
	{
	public:
		
		TEST_METHOD(Trivial)
		{
			PKB PKBTest;
			vector<int> expected(2, 2);
			Assert::AreEqual(1, 1);
			Assert::AreEqual(
				//Expected value:
				expected[0],
				//Actual value:
				PKBTest.followStar(1)[0],
				//Message:
				L"Basic test failed",
				//Line number - used if there is no PDB file:
				LINE_INFO()
			);

			return;
		}

	};
}