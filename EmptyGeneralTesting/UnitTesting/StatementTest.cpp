#include "stdafx.h"
#include "CppUnitTest.h"
#include "../SPA/PKB/Statement.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTesting
{
	TEST_CLASS(StatementTest)
	{
	public:
		/*
		TEST_METHOD(testConstructorWithBothNullptr)
		{
			Statement stmt(1, nullptr, nullptr);

			int stmtNo = stmt.getStmtNo();
			Assert::AreEqual(stmtNo, 1);

			Statement* follow = stmt.getFollow();
			Assert::IsNull(follow);

			Statement* followBy = stmt.getFollowBy();
			Assert::IsNull(followBy);

			Statement* parent = stmt.getParentStatement();
			Assert::IsNull(parent);

			return;
		}

		TEST_METHOD(testConstructorWithNullFollowingStatement)
		{
			Statement stmt1(1, nullptr, nullptr);
			Statement stmt2(2, &stmt1, nullptr);

			int stmtNo = stmt2.getStmtNo();
			Assert::AreEqual(stmtNo, 2);

			Statement* follow = stmt2.getFollow();
			Assert::IsNull(follow);

			Statement* followBy = stmt2.getFollowBy();
			Assert::IsNull(followBy);

			Statement* parent = stmt2.getParentStatement();
			Assert::IsTrue(parent == &stmt1);

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

			Statement* parent = stmt2.getParentStatement();
			Assert::IsNull(parent);

			return;
		}

		TEST_METHOD(testConstructor)
		{
			Statement stmt1(1, nullptr, nullptr);
			Statement stmt2(2, &stmt1, &stmt1);

			int stmtNo = stmt2.getStmtNo();
			Assert::AreEqual(stmtNo, 2);

			Statement* follow = stmt2.getFollow();
			Assert::IsTrue(follow == &stmt1);

			Statement* followBy = stmt2.getFollowBy();
			Assert::IsNull(followBy);

			Statement* parent = stmt2.getParentStatement();
			Assert::IsTrue(parent == &stmt1);

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

			Assert::IsFalse(stmt1.equals(&stmt2));
		}

		TEST_METHOD(TestEqualStatement)
		{
			Statement stmt1(1, nullptr, nullptr);
			Statement stmt2(1, &stmt1, nullptr);

			Assert::IsTrue(stmt1.equals(&stmt2));
		}

		TEST_METHOD(TestIsParent)
		{
			Statement stmt1(1, nullptr, nullptr);
			Statement stmt2(2, &stmt1, nullptr);

			Assert::IsTrue(stmt2.isParent(1));
			Assert::IsFalse(stmt2.isParent(2));
			Assert::IsFalse(stmt1.isParent(1));
		}
		TEST_METHOD(TestIsFollow)
		{
			Statement stmt1(1, nullptr, nullptr);
			Statement stmt2(2, nullptr, &stmt1);

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
		*/
	};
}