#ifndef _Function_h_included_
#define _Function_h_included_


#include "Variable.h"

using namespace std;

class Function
{
private:
public:
	string name;
	vector<Variable> inputs;
	vector<Variable> variables;
	vector<Expression> expressions;
	
	Function();
	
	string getName();
	string getDescription();
	string setName(string in);
	
	Variable* getVariable(string in);
	bool variableExists(string in);
	bool shouldOut;
	vector<int> expectedEnds; // 0 loop, 1 if, 2 else
	Variable evaluate(vector<Variable> inputValues);
	Variable evaluate();
	int skipping;
	vector<int> loops;
	int current;
};

#endif

