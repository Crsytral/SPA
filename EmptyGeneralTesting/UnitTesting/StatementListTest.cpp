#include "stdafx.h"
#include "CppUnitTest.h"
#include "Statement.h"
#include "StatementList.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTesting
{
	TEST_CLASS(StatementListTest)
	{
	public:

		TEST_METHOD(testConstructorWithNullParents)
		{
			StatementList stmtList(nullptr);
			Statement* parent = stmtList.getParent();

			Assert::IsNull(parent);
		}

		TEST_METHOD(testConstructor)
		{
			Statement stmt1(1, nullptr, nullptr);
			StatementList stmtList(&stmt1);

			Statement* parent = stmtList.getParent();

			Assert::IsTrue(parent == &stmt1);
		}


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


	};
}