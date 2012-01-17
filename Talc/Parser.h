#ifndef _Parser_h_included_
#define _Parser_h_included_

#include "Operation.h"
#include "Function.h"

#include <iostream>
#include <fstream>

using namespace std;

class Parser
{
	private:
	
	public:
	Parser();
	Function parse(vector<string> datas);	
	Operation getOperation(vector<string>& data, int& i);
	Expression getExpression(vector<string>& data, int& i);
	Expression getInput(vector<string>& data, int& i);
	
	
	vector<Expression> getExpressions(vector<string>& data, int& i);
	vector<Expression> getInputs(vector<string>& data, int& i);

	void setOrder(vector<string>& data, vector<string> operators);
	void setSimpleOrder(vector<string>& data, vector<string> operators);

	void setOperatorInput(vector<string>& data);
	void setLists(vector<string>& data);
	void setOrders(vector<string>& data);
	void setMathShortcuts(vector<string>& data);

	bool isAOperator(string in);
	bool isAStatement(string in);
	
	bool isAWord(string in);
	bool isANumber(string in);
	
	bool doNotPrintData;
	
	double getLengthOfLongestLine(string in);
	double getNumLines(string in);

};

#endif

