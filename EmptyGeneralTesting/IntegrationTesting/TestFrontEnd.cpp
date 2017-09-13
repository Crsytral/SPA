#include "stdafx.h"
#include "CppUnitTest.h"
#include "../SPA/Parser/Parser.h"
#include "../SPA/PKB/PKB.h"
#include "../SPA/QPS/QueryParser.h"
#include "../SPA/QPS/QueryEvaluator.h"
#include "../SPA/PKB/Expression.h"
#include "../SPA/Parser/VarToken.h"
#include "../SPA/Parser/NumToken.h"
#include "../SPA/Parser/OperatorToken.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace IntegrationTesting
{		
	TEST_CLASS(UnitTest1)
	{
	public:
		
		TEST_METHOD(PkbAndQueryParser)
		{
			// TODO: Your test code here
			PKB p;
			//adding in var list
			vector<string> varNames = { "i", "x", "y", "z" };
			vector<Variable*> vars;
			for (int i = 0; i < varNames.size(); i++) {
				vars.push_back(new Variable(varNames[i]));
				p.addVariable(vars[i]);
			}
			string proc = "Sun";
			//adding in procedure list
			p.addProcedure(proc);
			//adding in the statements
			//first construct the expressions for 3 assignment statements
			queue<Token> q1, q2, q3;
			//add to q1 & build expression 1
			q1.push(*(new NumToken("1")));
			Expression * ex1 = new Expression(q1);
			p.addAssignStatement(vars[1], ex1);
			//add to q2
			q2.push(*(new VarToken("x")));
			q2.push(*(new NumToken("2")));
			q2.push(*(new OperatorToken("+")));
			q2.push(*(new VarToken("z")));
			q2.push(*(new OperatorToken("+")));
			Expression * ex2 = new Expression(q2);
			p.addAssignStatement(vars[2], ex2);
			//add to q3 and build expression 3
			q3.push(*(new NumToken("3")));
			Expression * ex3 = new Expression(q3);
			//add a while statement
			p.addWhileStatement(vars[0]);
			p.addAssignStatement(vars[3], ex3);
			QueryParser* qp = new QueryParser();
			QueryObject queryObj = qp->getQueryObj("assign a; statement s; variable v; Select s such that Parent (3, 4)");
			//Need a demo PKB 
			QueryEvaluator qe(&p, queryObj);
			Result result = qe.getRawResult();
			string s = result.toString();
			Assert::AreEqual(s, (std::string)"1, 2, 3, 4");
		}
	};
}