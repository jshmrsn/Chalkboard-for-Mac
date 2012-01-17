#ifndef _Operation_h_included_
#define _Operation_h_included_

#include "Expression.h"


using namespace std;

class Function;
class Variable;
class Operation
{
private:

public:
	int processIndex;
	bool isAStatement;
	vector<Expression> inputs;
	string information;
	string assignmentType;
	Operation();
	Operation(string ninformation);
	void setInformation(string in);
	Variable evaluate(Variable current, Function* origin);
	Expression assignment;
	
	Variable* getReference(Function* origin);	
};

#endif

