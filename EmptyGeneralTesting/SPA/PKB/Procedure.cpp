#include <string>
using namespace std;

#include "Procedure.h"

Procedure::Procedure(string name) {
	StatementList lst(this);
	stmtLst = &lst;
	procName = name;
}