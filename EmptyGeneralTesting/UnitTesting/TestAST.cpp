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
			Assert::AreNotEqual(
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

		TEST_METHOD(AddProcedure) {
			PKB PKBTest;
			vector<string> cases;
			cases.push_back("Sun");
			PKBTest.addProcedure(cases[0]);
			cases.push_back("Moon");
			PKBTest.addProcedure(cases[1]);
			//check whether the procedures are in the allProcedures list
			vector<string> allProcNames = PKBTest.getAllProcedures();
			for (int i = 0; i < allProcNames.size(); i++) {
				Assert::AreEqual(cases[i], allProcNames[i], L"Add Procedure fails", LINE_INFO());
			}
			//check whether the procedures are added to the currStmtContainer stack
			//probably true, but I can't think of any reasonable way to test this
			return;
		}

		TEST_METHOD(AddVar) {
			PKB PKBTest;
			//Add var if var not added before
			//Ignore if var alr added
			vector<Variable*> cases = {
				new Variable("x"),
				new Variable("y"),
				new Variable("z"),
				new Variable("t")
			};
			for (int i = 0; i < cases.size(); i++) {
				PKBTest.addVariable(cases[i]);
			}
			vector<string> allVars = PKBTest.getAllVariables();
			for (int i = 0; i < cases.size(); i++) {
				Assert::AreEqual(cases[i]->getName(), allVars[i], L"Add variable fails", LINE_INFO());
			}
			//Try adding var that has been added before
			Variable* duplicate = new Variable("x");
			allVars = PKBTest.getAllVariables();
			Assert::AreEqual(cases.size(), allVars.size(), L"Duplicate variable added", LINE_INFO());
		}

		TEST_METHOD(AddAssign) {
			PKB PKBTest;
			string p = "Sun";
			PKBTest.addProcedure(p);
			//add an Assignment statement into the existing procedure
			return; 
		}
	};
}