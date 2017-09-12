#include "stdafx.h"
#include "CppUnitTest.h"
#include "../SPA/PKB/Statement.h"
#include "../SPA/PKB/WhileStatement.h"
#include "../SPA/PKB/AssignStatement.h"
#include "../SPA/PKB/StatementList.h"
#include "../SPA/PKB/Procedure.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTesting
{
	TEST_CLASS(StatementListTest)
	{
	public:

		

		TEST_METHOD(TestAdd)
		{
			
			Procedure proc("Proc"); 
			StatementList stmtList;

			stmtList.addStatement(1, &proc);
			stmtList.addStatement(2, &proc);
			stmtList.addStatement(3, &proc);

			vector<Statement> stmtList1;
			
			Statement stmt1, stmt2;
			for each (Statement* stmt in stmtList.getAllStatement())
			{
				if (stmt->getStmtNo() == 1) {
					stmt1 = *stmt;
				}
				if (stmt->getStmtNo() == 2) {
					stmt2 = *stmt;
				}
			}
			

			StatementContainer* stmtC = stmt1.getParentContainer();
			Assert::IsTrue(&proc == stmtC);

			Statement* stmt = stmt1.getFollow();
			Assert::IsNull(stmt);

			stmtC = stmt2.getParentContainer();
			Assert::IsTrue(&proc == stmtC);

			stmt = stmt2.getFollow();
			Assert::IsTrue(stmt1 == *stmt);

			stmt = stmt1.getFollowBy();
			Assert::IsTrue(stmt2 == *stmt);
			
			stmt = stmt2.getFollowBy();
			Assert::IsNull(stmt);

		}

		TEST_METHOD(TestAddWhileStatement)
		{
			Procedure proc("Proc");
			StatementList stmtList;

			Variable var("three");
			stmtList.addWhileStatement(1, &proc, &var);

			Statement stmt1;
			for each (Statement* stmt in stmtList.getAllStatement())
			{
				if (stmt->getStmtNo() == 1) {
					stmt1 = *stmt;
				}
			}

			Assert::IsTrue(typeid(stmt1) == typeid(WhileStatement));
		}

		TEST_METHOD(TestAddAssignStatement)
		{
			Procedure proc("Proc");
			StatementList stmtList;

			stmtList.addAssignStatement(1, &proc,nullptr,nullptr,nullptr);

			Statement stmt1;
			for each (Statement* stmt in stmtList.getAllStatement())
			{
				if (stmt->getStmtNo() == 1) {
					stmt1 = *stmt;
				}
			}

			Assert::IsTrue(typeid(stmt1) == typeid(AssignStatement));
		}

		TEST_METHOD(TestIsChild)
		{
			Procedure proc("Proc");
			StatementList stmtList;
			Variable var("var");
			stmtList.addWhileStatement(1, &proc,&var);

			Assert::IsTrue(stmtList.isChild(1));
		}
		
	};
}