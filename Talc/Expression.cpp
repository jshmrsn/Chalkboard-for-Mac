#include "Expression.h"
#include "Operation.h"
#include "Expression.h"
#include "Variable.h"
#include "Function.h"
#include "Utility.h"
#include "Program.h"

using namespace std;

Expression::Expression()
{
	silenced = true;
}

Variable Expression::evaluate(Function* origin)
{
	Variable current;
	current.setValue("0");
	
	for(int i = 0; i < operations.size(); i++)
	{
		current = operations[i].evaluate(current, origin);
	}
	
	
//	[utility.outputController addOutputVariable:current];
	if(!silenced && origin && origin->skipping <= 0)
		utility.output = utility.output + current.getValueFriendly() + "\n";
	
	return current;
}

Variable* Expression::getReference(Function* origin)
{
	if(operations.size())
		return operations[0].getReference(origin);
	return 0;
}
