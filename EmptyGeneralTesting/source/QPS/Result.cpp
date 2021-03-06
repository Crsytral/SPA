#include "Result.h"

Result::Result() {}

Result::Result(string data) { // to remove
	Result::isValid = false;
}

Result::Result(vector <string> data) {
	Result::asgnData = data;
	Result::isValid = false;
}

void Result::setValid(bool valid) {
	Result::isValid = valid;
}

bool Result::getIsValid() const {
	return isValid;
}

void Result::setAsgnData(string data) {
	Result::asgnData.push_back(data);
}

vector <string> Result::getAsgnData() const {
	return asgnData;
}

void Result::setQueryResult(string data) {
	Result::queryResult.push_back(data);
}

vector <string> Result::getQueryResult() const {
	return queryResult;
}

string Result::toString() {
	string output = "";
	if (isValid == true) {
		for each (string data in asgnData)
		{
			output += data + "\n";
		}
		for each (string data in queryResult)
		{
			output += data + "\n";
		}
	}
	else {
		output = "No Result";
	}
	
	return	output;
}