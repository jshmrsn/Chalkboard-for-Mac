#ifndef _Variable_h_included_
#define _Variable_h_included_


#include <iostream>
#include <sstream> 
#include <string>
#include <vector>
#include <cmath>

using namespace std;

class Expression;
class Function;
class Operation;

class Variable
{

public:
	string name;
	
	string value;
	double complex;
	
	vector<Variable> variables;
	
	Variable();
	Variable(string in);
	
	string getName();
	void setName(string in);

	double getValuef();
	string getValue();
	string getValueFriendly();


	void setValue(string in);
	void setValue(double in);
	void set(Variable in);
	
	void allocate(int depth, int size);
	int totalSize()
	{
		int size = 0;
		for(int i = 0; i < variables.size(); i++)
			size += variables[i].totalSize();
		return size + variables.size();
	}
	Variable* getVariable(int depth, vector<Expression>& index, Function* origin);
	
};

#endif

