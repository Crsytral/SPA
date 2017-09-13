#include "stdafx.h"
#include "CppUnitTest.h"
#include "../SPA/PKB/Statement.h"
#include "../SPA/PKB/StatementContainer.h"
#include "../SPA/PKB/Procedure.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTesting
{
	TEST_CLASS(StatementTest)
	{
	public:

		TEST_METHOD(testConstructorWithBothNullptr)
		{
			Statement stmt(1, nullptr, nullptr);

			int stmtNo = stmt.getStmtNo();
			Assert::AreEqual(stmtNo, 1);

			Statement* follow = stmt.getFollow();
			Assert::IsNull(follow);

			Statement* followBy = stmt.getFollowBy();
			Assert::IsNull(followBy);

			StatementContainer* parent = stmt.getParentContainer();
			Assert::IsNull(parent);

			return;
		}

		TEST_METHOD(testConstructorWithNullFollowingStatement)
		{
			Statement stmt1(1, nullptr, nullptr);
			StatementContainer stmtC;
			Statement stmt2(2, &stmtC, nullptr);

			int stmtNo = stmt2.getStmtNo();
			Assert::AreEqual(stmtNo, 2);

			Statement* follow = stmt2.getFollow();
			Assert::IsNull(follow);

			Statement* followBy = stmt2.getFollowBy();
			Assert::IsNull(followBy);

			StatementContainer* parent = stmt2.getParentContainer();
			Assert::IsTrue(parent == &stmtC);

			return;
		}

		TEST_METHOD(testConstructorWithNullParentStatement)
		{
			Statement stmt1(1, nullptr, nullptr);
			Statement stmt2(2, nullptr, &stmt1);

			int stmtNo = stmt2.getStmtNo();
			Assert::AreEqual(stmtNo, 2);

			Statement* follow = stmt2.getFollow();
			Assert::IsTrue(follow == &stmt1);

			Statement* followBy = stmt2.getFollowBy();
			Assert::IsNull(followBy);

			StatementContainer* parent = stmt2.getParentContainer();
			Assert::IsNull(parent);

			return;
		}

		TEST_METHOD(testConstructor)
		{
			Statement stmt1(1, nullptr, nullptr);
			StatementContainer stmtC;
			Statement stmt2(2, &stmtC, &stmt1);

			int stmtNo = stmt2.getStmtNo();
			Assert::AreEqual(stmtNo, 2);

			Statement* follow = stmt2.getFollow();
			Assert::IsTrue(follow == &stmt1);

			Statement* followBy = stmt2.getFollowBy();
			Assert::IsNull(followBy);

			StatementContainer* parent = stmt2.getParentContainer();
			Assert::IsTrue(parent == &stmtC);

			return;
		}
		TEST_METHOD(TestSetFollow)
		{
			Statement stmt1(1, nullptr, nullptr);
			stmt1.setFollowedBy(nullptr);

			Statement* followBy = stmt1.getFollowBy();
			Assert::IsNull(followBy);
		}
		TEST_METHOD(TestSetFollowwithNullptr)
		{
			Statement stmt1(1, nullptr, nullptr);
			Statement stmt2(2, nullptr, nullptr);
			stmt1.setFollowedBy(&stmt2);

			Statement* followBy = stmt1.getFollowBy();
			Assert::IsTrue(followBy == &stmt2);
		}
		TEST_METHOD(TestNotEqualStatement)
		{
			Statement stmt1(1, nullptr, nullptr);
			Statement stmt2(2, nullptr, nullptr);

			Assert::IsFalse(stmt1==stmt2);
		}

		TEST_METHOD(TestEqualStatement)
		{
			Statement stmt1(1, nullptr, nullptr);
			StatementContainer stmtC;
			Statement stmt2(1, &stmtC, nullptr);

			Assert::IsTrue(stmt1==stmt2);
		}
		TEST_METHOD(TestgetStatementNo)
		{
			Statement stmt1(1, nullptr, nullptr);

			Assert::IsTrue(stmt1.getStmtNo() == 1);
		}

		TEST_METHOD(TestIsParentForStatement)
		{
			Procedure proc("PrcName");
			Variable var("var1");
			WhileStatement stmt1(1,nullptr,nullptr,&var);
			Statement stmt2(2, &proc, nullptr);
			Statement stmt3(3, &stmt1,nullptr);

			Assert::IsTrue(stmt3.isParent(1));
			Assert::IsFalse(stmt3.isParent("PrcName"));
			Assert::IsTrue(stmt2.isParent("PrcName"));
			Assert::IsFalse(stmt2.isParent(2));
		}
		TEST_METHOD(TestIsFollow)
		{
			int const1 = 1, const2 = 2;
			Statement stmt1(const1, nullptr, nullptr);
			Statement stmt2(const2, nullptr, &stmt1);

			Assert::IsTrue(stmt2.isFollow(1));
			Assert::IsFalse(stmt2.isFollow(2));
			Assert::IsFalse(stmt1.isFollow(1));
		}
		TEST_METHOD(TestIsFollowBy)
		{
			Statement stmt1(1, nullptr, nullptr);
			Statement stmt2(2, nullptr, nullptr);

			stmt2.setFollowedBy(&stmt1);

			Assert::IsTrue(stmt2.isFollowBy(1));
			Assert::IsFalse(stmt2.isFollowBy(2));
			Assert::IsFalse(stmt1.isFollowBy(1));
		}

		TEST_METHOD(TestAddModVar)
		{
			Statement stmt1(1, nullptr, nullptr);
			Variable var1("three");

			stmt1.addModVar(&var1);
			vector<Variable*> varList = stmt1.getModVar();

			bool isFound = false;
			for each (Variable* var in varList)
			{
				string str1 = var->getName();
				if (var->getName().compare("three") == 0) {
					isFound = true;
					break;
				}
			}
			Assert::IsTrue(isFound);
		}
		TEST_METHOD(TestAddUseVar)
		{
			Statement stmt1(1, nullptr, nullptr);
			Variable var("three");

			stmt1.addUseVar(&var);
			vector<Variable*> varList = stmt1.getUseVar();

			bool isFound = false;
			for each (Variable* var in varList)
			{
				if (var->getName().compare("three") == 0) {
					isFound = true;
					break;
				}
			}
			Assert::IsTrue(isFound);
		}
		TEST_METHOD(TestIsModVar)
		{
			Statement stmt1(1, nullptr, nullptr);
			Variable var("three");

			stmt1.addModVar(&var);

			Assert::IsTrue(stmt1.isMod("three"));
		}
		TEST_METHOD(TestIsUseVar)
		{
			Statement stmt1(1, nullptr, nullptr);
			Variable var("three");

			stmt1.addUseVar(&var);

			Assert::IsTrue(stmt1.isUse("three"));
		}
	};
}