#include "stdafx.h"
#include "CppUnitTest.h"
#include "../SPA/PKB/Statement.h"
#include "../SPA/PKB/StatementList.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTesting
{
	TEST_CLASS(StatementListTest)
	{
	public:

		TEST_METHOD(testConstructorWithNullParents)
		{
			StatementList stmtList(nullptr);
			StatementContainer* parent = stmtList.getParentContainer();

			Assert::IsNull(parent);
		}

		/*
		Need to be changed, as Statement now have a parentContainer, not a parentStatement.
		TEST_METHOD(testConstructor)
		{
			Statement stmt1(1, nullptr, nullptr);
			StatementList stmtList(&stmt1);

			StatementContainer* parent = stmtList.getParentContainer();

			Assert::IsTrue(parent == &stmt1);
		}
		*/

		/*
		Need to be changed, as Statement now have a parentContainer, not a parentStatement.
		TEST_METHOD(TestAdd)
		{
			Statement stmt1(1, nullptr, nullptr);
			StatementList stmtList(&stmt1);

			stmtList.addStatement(2);

			Statement* stmt2 = stmtList.getCurr();
			Statement* stmt = stmt2->getParentStatement();
			Assert::IsTrue(&stmt1 == stmt);

			stmt = stmt2->getFollow();
			Assert::IsNull(stmt);

			stmt = stmt2->getFollowBy();
			Assert::IsNull(stmt);

			stmtList.addStatement(3);

			Statement* stmt3 = stmtList.getCurr();

			stmt = stmt3->getParentStatement();
			Assert::IsTrue(&stmt1 == stmt);

			stmt = stmt3->getFollow();
			Assert::IsTrue(stmt2 == stmt);

			stmt = stmt3->getFollowBy();
			Assert::IsNull(stmt);

			stmt = stmt2->getFollowBy();
			Assert::IsTrue(stmt == stmt3);

		}
		*/
		
	};
}