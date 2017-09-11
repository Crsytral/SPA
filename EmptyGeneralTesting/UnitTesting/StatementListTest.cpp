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

		TEST_METHOD(testConstructorWithNullParents)
		{
			StatementList stmtList(nullptr);
			StatementContainer* parent = stmtList.getParentContainer();

			Assert::IsNull(parent);
		}


		TEST_METHOD(testConstructor)
		{
			Procedure proc("Proc");
			StatementList stmtList(&proc);

			StatementContainer* parent = stmtList.getParentContainer();

			Assert::IsTrue(parent == &proc);
		}
		

		TEST_METHOD(TestAdd)
		{
			
			Procedure proc("Proc"); 
			StatementList stmtList(&proc);

			stmtList.addStatement(1);
			stmtList.addStatement(2);
			stmtList.addStatement(3);

			vector<Statement> stmtList1;
			
			for each (Statement* stmt in stmtList.getAllStatement())
			{
				stmtList1.push_back(*stmt);
			}
			
			Statement find1(1,nullptr,nullptr);
			vector<Statement>::iterator stmt1 = find(stmtList1.begin(), stmtList1.end(), find1);

			StatementContainer* stmtC = stmt1->getParentContainer();
			Assert::IsTrue(&proc == stmtC);

			Statement* stmt = stmt1->getFollow();
			Assert::IsNull(stmt);


			Statement find2(2, nullptr, nullptr);
			vector<Statement>::iterator stmt2 = find(stmtList1.begin(), stmtList1.end(), find2);

			stmtC = stmt2->getParentContainer();
			Assert::IsTrue(&proc == stmtC);

			stmt = stmt2->getFollow();
			Assert::IsTrue(stmt1->operator==(*stmt));

			stmt = stmt1->getFollowBy();
			Assert::IsTrue(stmt2->operator==(*stmt));
			
			stmt = stmt2->getFollowBy();
			Assert::IsNull(stmt);

		}

		TEST_METHOD(TestAddWhileStatement)
		{
			Procedure proc("Proc");
			StatementList stmtList(&proc);

			stmtList.addWhileStatement(1,nullptr);

			vector<Statement> stmtList1;

			for each (Statement* stmt in stmtList.getAllStatement())
			{
				stmtList1.push_back(*stmt);
			}

			Statement find1(1, nullptr, nullptr);
			vector<Statement>::iterator it = find(stmtList1.begin(), stmtList1.end(), find1);

			Assert::IsTrue(typeid(it) == typeid(WhileStatement));
		}

		TEST_METHOD(TestAddAssignStatement)
		{
			Procedure proc("Proc");
			StatementList stmtList(&proc);

			stmtList.addAssignStatement(1, nullptr,nullptr,nullptr);

			vector<Statement> stmtList1;

			for each (Statement* stmt in stmtList.getAllStatement())
			{
				stmtList1.push_back(*stmt);
			}

			Statement find1(1, nullptr, nullptr);
			vector<Statement>::iterator it = find(stmtList1.begin(), stmtList1.end(), find1);

			Assert::IsTrue(typeid(it) == typeid(AssignStatement));
		}

		TEST_METHOD(TestIsChild)
		{
			Procedure proc("Proc");
			StatementList stmtList(&proc);
			stmtList.addAssignStatement(1, nullptr, nullptr, nullptr);

			Assert::IsTrue(stmtList.isChild(1));
		}
		
	};
}