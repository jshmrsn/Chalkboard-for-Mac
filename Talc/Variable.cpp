#include "Variable.h"
#include "Utility.h"
#include "Operation.h"
#include "Expression.h"
#include "Variable.h"
#include "Function.h"
#include "Program.h"
#include "Keyword.h"
#include "Math.h"

using namespace std;

Variable::Variable()
{
	setName("");
	setValue("0");
	complex = 0;
}

Variable::Variable(string in)
{
	setName(in);
	setValue("0");
	complex = 0;	
}

double Variable::getValuef()
{
	return strtod(value.c_str(), NULL);
}

string Variable::getValue()
{
	return value;
}

string Variable::getValueFriendly()
{
	if(variables.size() > 0)
	{
		string listingText = "{";
		
		for(int i = 0; i < variables.size(); i++)
		{				
			listingText += variables[i].getValueFriendly();
			
			if(i != variables.size()-1)
				listingText += ", ";
		}
		
		listingText += "}";
		
		return listingText;
	}
	else if(value.length())
	{
		string temp = utility.strip(value, "\"");
		
		if(math.abs(complex) != 0)
			temp +=  " + " + utility.double2string(complex) + key.constant_complex;
		
		return temp;
	}
	
	return "0";
}

void Variable::setValue(string in)
{
	value = in;
}

void Variable::setValue(double in)
{
	value = utility.double2string(in);
}

void Variable::set(Variable in)
{
	variables = in.variables;
	value = in.value;
	complex = in.complex;		
}

string Variable::getName()
{
	return name;
}

void Variable::setName(string in)
{
	name = in;
}

void Variable::allocate(int depth, int size)
{
	if(depth)
		for(int i = 0; i < variables.size(); i++)
			variables[i].allocate(depth-1, size);
	else
	{
		while(variables.size() < size && size > 0)
		{
			Variable v;
			v.setName("");
			v.setValue("0");
			variables.push_back(v);
		}
	}
}

Variable* Variable::getVariable(int depth, vector<Expression>& index, Function* origin)
{
	if(index.size() <= 0)
	{
		return this;
	}
	if(depth == index.size() || !origin)
	{
		return this;
	}
	else
	{	
		if(depth < index.size() && depth >= 0)
		{
			Expression a = index[depth];
			Variable v = a.evaluate(origin);
			int i = v.getValuef();
			if(i < variables.size() && i >= 0)
			{
				return variables[i].getVariable(depth+1, index, origin);	
			}
			else
			{
				return this;
			}
		}
		else
		{
			return this;
		}
	}		
	return this;
}


