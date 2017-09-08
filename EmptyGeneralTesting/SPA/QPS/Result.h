//header guard at start of header file
#ifndef RESULT_H
#define RESULT_H	

#include <stdio.h>
#include <vector>
#include <string>

using namespace std;

class Result {
private:
	bool isValid;
	vector <string> asgnData; //TEMP storage for assignment/var/stmt stmtLst (Eg: assign a, variable v, stmt s. To handle ALL queries scenario), should be stmtLst instead of string
	vector <string> queryResult; //TEMP storage for results to the query, should be stmtLst instead of string

public:
	Result();
	Result(string data); //to remove after merging
	Result(vector <string> data);
	void setValid(bool isValid);
	bool getIsValid() const;
	void setAsgnData(string data);
	vector <string> getAsgnData() const;
	void setQueryResult(string data);
	vector <string> getQueryResult() const;
	string toString();
};

//End guard at bottom of header file
#endif 