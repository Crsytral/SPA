#include "Parser.h"
#include "Token.h"

#include <string>
#include <vector>
#include <iostream>

using namespace std;
// token types:
const string LETTER = "LETTER";
const string DIGIT = "DIGIT";
const string PLUS = "PLUS";


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

const string BLOCK_START = "{";
const string BLOCK_END = "}";
//const string PLUS, MINUS, MULTIPLY, DIVIDE, EQUAL = "PLUS", "MINUS", "MULTIPLY", "DIVIDE", "EQUAL";


Parser::Parser(string text) : text(text), currentToken(EMPTY_TOKEN, EMPTY_TOKEN)
{
	line = 1;
	//text = text;
	position = 0;
	currentChar = text[position];
	currentToken = Token(EMPTY_TOKEN, EMPTY_TOKEN);

	bufferPosition = 0;
}


Token Parser::lex()
{
	Token null = Token("null", "null");
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

			cout << "space/newline/tab encountered and ignored" << endl;
			memset(buffer, 0, sizeof(buffer));
			bufferPosition = 0;
			continue;
		}

		/*
		* process parsed words here
		*/

		if (buffer[bufferPosition - 1] == NONE) // if the current buffer array is a string
		{
			//cout << "start of buffer: //" << buffer << "// end of buffer" << endl;

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

			// if not inside an assignment, expect assignment variable
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
							cout << "assignment of var " << currentAssignVar << " finished!" << endl;
							cout << "final assignment is: " << leftFactor << " " << op << " " << rightFactor << endl;
							memset(buffer, 0, sizeof(buffer));
							bufferPosition = 0;
							continue;


						}
						if (buffer == PLUS_STRING)
						{
							cout << "operator is: " << PLUS_STRING << ". " << endl;
							op = "PLUS";
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
						cout << "exp factor is: " << buffer << ". " << endl;
						if (factorCount == 0)
						{
							leftFactor = buffer;
							factorCount++;
						}
						else
						{
							rightFactor = buffer;
						}
						assignExpectOp = true;
					}
					memset(buffer, 0, sizeof(buffer));
					bufferPosition = 0;
					continue;
				}


			}




		}

		if (currentChar == SPACE || currentChar == LINE_FEED || currentChar == TAB) // TODO: if semi colon is seen, do not advance!!
		{
			//cout << "buffer is: " << buffer << " |||| " << endl;
			//cout << "space! tab!!!!" << endl;
			buffer[bufferPosition] = '\0';

			bufferPosition++;
			advance();
			continue;

		}
		else if (currentChar == SEMI_COLON)
		{
			cout << "curr is:" << currentChar << "|||| position is:" << position << endl;
			if (strlen(buffer) == 0)
			{
				cout << "buffer empty" << endl;
				buffer[bufferPosition] = currentChar;
				bufferPosition++;
				advance();
				continue;
			}

			buffer[bufferPosition] = '\0';

			bufferPosition++;
			//advance();

			continue;



			continue;
		}
		else
		{
			buffer[bufferPosition] = currentChar;
			bufferPosition++;
			advance();
			continue;
		}


		//cout << "buffer is: "<< buffer << " |||| " <<endl;
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
