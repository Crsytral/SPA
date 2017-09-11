#include "Parser.h"
#include "Token.h"
#include "VarToken.h"
#include "OperatorToken.h"
#include "NumToken.h"
#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <stack>
#include <queue> 
using namespace std;
// token types:


const string EOL = "EOL";
const string NEWLINE = "NEWLINE";

const string INTEGER = "INTEGER";
const string NAME = "NAME";
const string VARIABLE = "VARIABLE";


const string PROCEDURE = "procedure";

const string EMPTY_TOKEN = "EMPTY TOKEN";

const string EQUAL_STRING = "=";
const string PLUS_STRING = "+";
const string MINUS_STRING = "-";
const string MUL_STRING = "*";
const string SPACE_STRING = " ";
const string EMPTY_STRING = "";
const string LINE_FEED_STRING = "\n";
const string TAB_STRING = "\t";
const string SEMI_COLON_STRING = ";";
const int MAX_LENGTH = 1024;

const char NONE = '\0';
const char LINE_FEED = '\n';
const char TAB = '\t';
const char SPACE = ' ';
const char SEMI_COLON = ';';
const char EQUAL = '=';
const char PLUS = '+';

const string BLOCK_START = "{";
const string BLOCK_END = "}";
//const string PLUS, MINUS, MULTIPLY, DIVIDE, EQUAL = "PLUS", "MINUS", "MULTIPLY", "DIVIDE", "EQUAL";

bool isLegalSymbol(char symbol)
{
	return (symbol == '{' || symbol == '}' || symbol == ';' || symbol == '+' || symbol == '=');
}
bool isIllegalSymbol(char symbol)
{
	return false;
}
void clearQueue(queue<Token> &q)
{
	queue<Token> empty;
	swap(q, empty);
}


Parser::Parser(string filename) : filename(filename), currentToken(EMPTY_TOKEN)
{
	ifstream ifs(filename);
	string content((istreambuf_iterator<char>(ifs)),
		(istreambuf_iterator<char>()));

	text = content;
	cout << text << endl;
	line = 1;
	//text = text;
	position = 0;
	currentChar = text[position];
	currentToken = Token(EMPTY_TOKEN);

	bufferPosition = 0;
}


Token Parser::lex()
{
	Token null = Token("null");
	int parenNum = 0; // ( )
	int braceNum = 0; // { }

	string currentUnknownVar = "";

	string currentAssignVar = "";
	bool assignExpectOp = false;
	// 3 bool: {has var, has equal sign, has exp}
	bool assignVerify[3] = { false, false, false };
	string leftFactor = "";
	string rightFactor = "";
	string op = "";
	int factorCount = 0;

	stack<Token> operatorStack;
	queue<Token> output;
	queue<Token> tokens;

	// 3 bool: {proc keyword found, proc name defined, starting brace found, ending brace found}
	bool procVerify[4] = { false, false, false, false };
	string currentProcName = "";

	while (currentChar != NONE)
	{
		//cout << "start of buffer: //" << buffer << "// end of buffer" << endl;
		// check if invalid var name
		if (bufferPosition != 0 && (!isalpha(buffer[0])))
		{
			if (isalpha(buffer[bufferPosition - 1]))
			{
				cout << "invalid var name" << endl;
				return null;
			}
		}
		if (bufferPosition != 0 && (buffer == SPACE_STRING || buffer == EMPTY_STRING || buffer == TAB_STRING)) {

			//cout << "space/newline/tab encountered and ignored" << endl;
			memset(buffer, 0, sizeof(buffer));
			bufferPosition = 0;
			continue;
		}

		/*
		* process parsed words here
		*/

		if (buffer[bufferPosition - 1] == NONE) // if the current buffer array is a string
		{
			cout << "start of buffer: //" << buffer << "// end of buffer" << endl;

			// ignore space/tab
			if (buffer == EMPTY_TOKEN)
			{
				cout << "space string";
				memset(buffer, 0, sizeof(buffer));
				bufferPosition = 0;
				continue;
			}
			// keyword identification
			// case 1: procedure
			if (buffer == PROCEDURE)
			{
				// if alreaday expecting proc name
				if (procVerify[0])
				{
					cout << "cannot define procedure inside a procedure" << endl;
					return null;
				}
				procVerify[0] = true;
				cout << "procedure is detected" << endl;
				// reset buffer and continue
				memset(buffer, 0, sizeof(buffer));
				bufferPosition = 0;
				continue;
			}

			// case 2: expecting proc name
			if (procVerify[0] && !procVerify[1])
			{
				currentProcName = buffer;
				procVerify[1] = true;
				cout << "proc name is " << currentProcName << endl;
				memset(buffer, 0, sizeof(buffer));
				bufferPosition = 0;
				continue;
			}

			if (buffer == BLOCK_START)
			{
				if (procVerify[0] && procVerify[1])
				{
					cout << "proc block start" << endl;
					memset(buffer, 0, sizeof(buffer));
					bufferPosition = 0;
				}
				continue;
			}

			// if not inside an assignment, expect assignment variable, start parsing assignment
			if (!assignVerify[0])
			{
				/*cout << buffer << ", pointer: " << bufferPosition << endl;*/
				currentAssignVar = buffer;
				cout << "assignment variable is " << currentAssignVar << endl;
				assignVerify[0] = true;
				memset(buffer, 0, sizeof(buffer));
				bufferPosition = 0;
				continue;
			}
			// if already in an assignment
			else {
				// if haven't encountered = sign, and the buffer is not equal sign, error!
				if (!assignVerify[1])
				{
					if (buffer != EQUAL_STRING)
					{
						cout << "Assignmetn statement variable must be followed by = but encountered " << buffer << endl;
						return null;
					}
					else
					{
						cout << "assignment symbol encountered" << endl;
						assignVerify[1] = true;
						memset(buffer, 0, sizeof(buffer));
						bufferPosition = 0;
						continue;
					}
				}
				// if '=' sign already encountered, expect new var or int or op
				else
				{
					//cout << "exp factor is: " << buffer << ". " << endl;
					if (assignExpectOp)
					{
						if (buffer == SEMI_COLON_STRING)
						{
							assignVerify[2] = true;
							while (!operatorStack.empty())
							{
								output.push(operatorStack.top());
								operatorStack.pop();
							}


							cout << "assignment of var " << currentAssignVar << " finished!" << endl;
							cout << "---------- start of output queue" << endl;
							while (!output.empty())
							{

								cout << output.front().getValue() << ", ";
								output.pop();
							}
							cout << '\n';
							clearQueue(output);
							cout << "-------------" << endl;

							cout << "---------- start of op stack" << endl;
							while (!operatorStack.empty())
							{

								cout << operatorStack.top().getValue() << ", ";
								operatorStack.pop();
							}
							cout << "-------------" << endl;

							// reset all variables used here
							currentAssignVar = "";
							assignVerify[0] = false;
							assignVerify[1] = false;
							assignVerify[2] = false;
							assignExpectOp = false;
							memset(buffer, 0, sizeof(buffer));
							bufferPosition = 0;
							continue;


						}
						if (buffer == PLUS_STRING)
						{
							cout << "operator is: " << PLUS_STRING << ". " << endl;
							op = "PLUS";
							operatorStack.push(OperatorToken(buffer));
							assignExpectOp = false;
						}

					}
					else
					{
						if (buffer == SEMI_COLON_STRING)
						{
							cout << "assignment cannot end with operator!" << endl;
							return null;
						}
						if (isdigit(buffer[0]))
						{
							cout << "exp factor is a number: " << buffer << ". " << endl;
							output.push(NumToken(buffer));
						}
						if (isalpha(buffer[0]))
						{
							cout << "exp factor is a variable: " << buffer << ". " << endl;
							output.push(VarToken(buffer));
						}


						assignExpectOp = true;
					}
					memset(buffer, 0, sizeof(buffer));
					bufferPosition = 0;
					continue;
				}


			}




		}

		if (isIllegalSymbol(currentChar))
		{
			cout << "illegal symbol" << endl;
			break;
		}

		if (currentChar == SPACE)
		{
			//cout << "space! buffer is: " << buffer << " |||| position is " << position << "char is: " << currentChar << endl;
			advance();
			continue;
		}
		if (currentChar == LINE_FEED)
		{
			//cout << "linefeed! buffer is: " << buffer << " |||| position is " << position << "char is: " << currentChar << endl;
			advance();
			continue;
		}

		if (isLegalSymbol(currentChar))
		{
			if (isIllegalSymbol(text[position + 1]))
			{
				cout << "illegal symbol" << endl;
				break;
			}
			//cout << "symbol! buffer is: " << buffer << " |||| position is " << position << "char is: " << currentChar << endl;
			buffer[bufferPosition] = currentChar;
			bufferPosition++;

			buffer[bufferPosition] = '\0';
			bufferPosition++;
			advance();
			continue;
		}


		if (text[position + 1] == SPACE)
		{
			//cout << "next char is space! buffer is: " << buffer << " |||| position is " << position << "char is: " << currentChar << endl;

			buffer[bufferPosition] = currentChar;
			bufferPosition++;

			buffer[bufferPosition] = '\0';
			bufferPosition++;

			advance();
			continue;
		}
		if (isLegalSymbol(text[position + 1]))
		{
			buffer[bufferPosition] = currentChar;
			bufferPosition++;

			buffer[bufferPosition] = '\0';
			bufferPosition++;

			advance();
			continue;
		}

		if (isalnum(currentChar))
		{
			//cout << "buffer is: " << buffer << " |||| position is " << position << endl;
			buffer[bufferPosition] = currentChar;
			bufferPosition++;
			advance();
			continue;
		}


		//advance();
	} // end while loop


	for (int i = 0; i < 4; i++)
	{
		cout << procVerify[i] << endl;
	}
	return null;
}

void Parser::advance()
{
	position += 1;
	if (position > text.length() - 1)
	{
		currentChar = NONE;
	}
	else
	{
		currentChar = text[position];
	}
}

