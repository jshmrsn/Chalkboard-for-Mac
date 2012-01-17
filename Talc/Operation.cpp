#include "Operation.h"
#include "Expression.h"
#include "Variable.h"
#include "Function.h"
#include "Utility.h"
#include "Program.h"
#include <complex>
#include "Keyword.h"
//#import "Organizer.h"
//#import "OutputListing.h"
#include "Math.h"
#include "Process.h"

using namespace std;


Operation::Operation()
{
	assignmentType == "none";
	processIndex = 0;
	isAStatement = false;
}

Operation::Operation(string ninformation)
{
	assignmentType == "none";
	setInformation(ninformation);
	processIndex = 0;	
}

void Operation::setInformation(string in)
{
	information = in;

	processIndex = processManager_statement.getProcessIndex(in);
	if(processIndex >= 0)
		isAStatement = true;
	else
		processIndex = processManager.getProcessIndex(in);
}

Variable Operation::evaluate(Variable current, Function* origin)
{
	if(isAStatement && processManager_statement.runIndex(processIndex, current, origin, inputs))
	{}
	else
		if(origin && origin->skipping <= 0)
			if(information.length() > 0 &&  ((information[0] >= '0' && information[0] <= '9') || information[0] == '.') )
			{
				if(information[0] == '.')
				{
					information = "0"+information;
				}
				Variable v;
				v.setValue(information);
				return v;
			}
			else if(processManager.runIndex(processIndex, current, origin, inputs))
			{}
			else if(information.length() > 0 && information[0] == '\"')
			{
				Variable v;
				v.setValue(information);
				return v;
			}
			else
			{
				Function* function = program.getFunction(information);
				if(function)
				{
					function = program.getFunction(information, inputs.size());
					if(function)
					{
						Function f = *function;
						vector<Variable> functionInputs;
						for(int i = 0; i < inputs.size(); i++)
							functionInputs.push_back(inputs[i].evaluate(origin));
						return f.evaluate(functionInputs);				
					}
					else
					{
						Variable v;
						v.setValue("Inputs do not match function");
						return v;
					}
				}
				else
				{		
					if(origin)
					{
						Variable* vptr = origin->getVariable(information);

						if(!vptr)
						{
							Variable v(information);
							origin->variables.push_back(v);
							vptr = &origin->variables[origin->variables.size()-1];
						}

						for(int j = 0; j < inputs.size(); j++)
						{	
							int size = inputs[j].evaluate(origin).getValuef();
							vptr->allocate(j, size+1);
						}					
						
						if(origin && assignmentType == key.operator_equal && vptr)
						{	
							Variable result = assignment.evaluate(origin);

							vptr = origin->getVariable(information);
							vptr = vptr->getVariable(0, inputs, origin);

							vptr->set(result);

							return result;
						}
						else
						{
							if(vptr)
							{
								vptr = vptr->getVariable(0, inputs, origin);
								if(vptr)
									return *vptr;
							}
							return Variable();
						}
					}
				}
	}

	return current;	
}
	

Variable* Operation::getReference(Function* origin)
{
		if(origin && origin->skipping <= 0)
		{
			Function* function = program.getFunction(information);
			if(function)
			{
				return 0;
			}
			else
			{
				Variable* vptr = origin->getVariable(information);
				
				if(!vptr)
				{
					Variable v(information);
					origin->variables.push_back(v);
					vptr = &origin->variables[origin->variables.size()-1];
				}				
				
				for(int j = 0; j < inputs.size(); j++)
				{	
					int size = inputs[j].evaluate(origin).getValuef();
					vptr->allocate(j, size+1);
				}					
				
				
				if(vptr)
				{
					vptr = vptr->getVariable(0, inputs, origin);
					if(vptr)
						return vptr;
				}
				
				return 0;
			}
		}

	return 0;	
}
	

