#ifndef _Expression_h_included_
#define _Expression_h_included_

#include <iostream>
#include <sstream> 
#include <string>
#include <vector>
#include <cmath>

using namespace std;

class Function;
class Operation;
class Variable;


class Expression
{
public: 

	Expression();
	vector<Operation> operations;
	Variable evaluate(Function* origin);
	bool silenced; // do not print output
	
	Variable* getReference(Function* origin);
};

#endif

