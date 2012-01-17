#include "Function.h"
#include "Operation.h"
#include "Expression.h"
#include "Variable.h"
#include "Utility.h"
#include "Program.h"
#include "Keyword.h"

using namespace std;


Function::Function()
{
	setName("");
}

string Function::getName()
{
	return name;
}

string Function::setName(string in)
{
	return name = in;
}

Variable* Function::getVariable(string in)
{		
	for(int i = 0; i <	variables.size(); i++)
	{
		if(utility.equalsNoCase(variables[i].getName(), in))
		{
			return &variables[i];
		}
	}
	return 0;
}	

bool Function::variableExists(string in)
{
	for(int i = 0; i <	variables.size(); i++)
	{
		if(utility.equalsNoCase(variables[i].getName(), in))
		{
			return true;
		}
	}
	return false;
}	

string Function::getDescription()
{
	string out = getName();
	out += key.scope_function_input_open;
		if(inputs.size() > 0)
			out += inputs[0].getName();
		for(int i = 1; i < inputs.size(); i++)
			out += ", " + inputs[i].getName();
	out += key.scope_function_input_close;
	

	return out;
}

Variable Function::evaluate()
{
	vector<Variable> v;
	return evaluate(v);
}

Variable Function::evaluate(vector<Variable> inputValues)
{
	variables.clear();
	utility.evaluationCounter+=30;
	for(int i = 0; i < inputValues.size() && i < inputs.size(); i++)
	{
		Variable variable;
		variable.setName(inputs[i].getName());
		variable.setValue(inputValues[i].getValue());
		variable.variables = inputValues[i].variables;
		variables.push_back(variable);
	}
	
	skipping = 0;
	loops.clear();
	
	for(current = 0; current < expressions.size() && utility.evaluationCounter < utility.maxEvals; current++)
	{
		utility.evaluationCounter++;
		shouldOut = false;
		Variable output = expressions[current].evaluate(this);
		if(shouldOut)
		{
			return output;
		}
	}
	
	return Variable();
}

