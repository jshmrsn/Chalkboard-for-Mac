#include "Process.h"

#include "Operation.h"
#include "Expression.h"
#include "Variable.h"
#include "Function.h"
#include "Utility.h"
#include "Program.h"
#include <complex>
#include "Keyword.h"
#include "Math.h"

//#import "Organizer.h"
//#import "OutputListing.h"

ProcessManager::ProcessManager()
{
	contents.push_back(new Process_operator_add("+"));
	contents.push_back(new Process_operator_subtract("-"));
	contents.push_back(new Process_operator_multiply("*"));
	contents.push_back(new Process_operator_multiply("•"));
	contents.push_back(new Process_operator_divide("/"));
	contents.push_back(new Process_operator_root("\\"));
	contents.push_back(new Process_sin("sin"));
	contents.push_back(new Process_cos("cos"));
	contents.push_back(new Process_tan("tan"));
	contents.push_back(new Process_asin("asin"));
	contents.push_back(new Process_acos("acos"));
	contents.push_back(new Process_atan("atan"));	
	contents.push_back(new Process_operator_mod("%"));
	contents.push_back(new Process_operator_exponent("^"));
	contents.push_back(new Process_operator_compare_less("<"));
	contents.push_back(new Process_operator_compare_greater(">"));
	contents.push_back(new Process_operator_compare_less_equal("<="));
	contents.push_back(new Process_operator_compare_greater_equal(">="));
	contents.push_back(new Process_operator_compare_equal("<>"));
	contents.push_back(new Process_operator_compare_and("&"));
	contents.push_back(new Process_operator_compare_or("|"));
	contents.push_back(new Process_operator_compare_invert("!"));
	contents.push_back(new Process_constant_boolean_true("true"));
	contents.push_back(new Process_constant_boolean_false("false"));
	contents.push_back(new Process_constant_pi("pi"));
	contents.push_back(new Process_constant_e("exp"));
	contents.push_back(new Process_constant_rad("rad"));
	contents.push_back(new Process_constant_deg("deg"));
	contents.push_back(new Process_constant_complex("i"));
	contents.push_back(new Process_avg("avg"));

	contents.push_back(new Process_round("round"));
	contents.push_back(new Process_floor("floor"));

	
	contents.push_back(new Process_add("add"));
	contents.push_back(new Process_remove("remove"));
	
	contents.push_back(new Process_log("log"));

	contents.push_back(new Process_sum("sum"));
	contents.push_back(new Process_abs("abs"));
	contents.push_back(new Process_max("max"));
	contents.push_back(new Process_min("min"));
	contents.push_back(new Process_charAt("charAt"));
	contents.push_back(new Process_statement_out("out"));
	contents.push_back(new Process_random("random"));
	contents.push_back(new Process_random("rand"));
	
	contents.push_back(new Process_plot("plot"));
	contents.push_back(new Process_statement_list("list"));
	contents.push_back(new Process_statement_alloc("alloc"));
	contents.push_back(new Process_size("size"));

	contents.push_back(new Process_imag("imag"));
	contents.push_back(new Process_real("real"));
	
	contents.push_back(new Process_date_year("tyear"));
	contents.push_back(new Process_date_month("tmonth"));
	contents.push_back(new Process_date_day("tday"));
	contents.push_back(new Process_date_hour("thour"));
	contents.push_back(new Process_date_minute("tminute"));
	contents.push_back(new Process_date_second("tsecond"));

}

ProcessManager_statement::ProcessManager_statement()
{
	contents.push_back(new Process_statement_loop("loop"));
	contents.push_back(new Process_statement_if("if"));
	contents.push_back(new Process_statement_else("else"));
	contents.push_back(new Process_statement_end("end"));	
	contents.push_back(new Process_statement_next("next"));	

	contents.push_back(new Process_eval("eval"));
}


int ProcessManager::getProcessIndex(string identifier)
{
	for(int i = 0; i < contents.size(); i++)
		if(contents.at(i) && utility.equalsNoCase(contents.at(i)->getIdentifier(), identifier))
			return i;
	return -1;
}

bool ProcessManager::runIndex(int in, Variable& current, Function* origin, vector<Expression>& inputs)
{
	if(in >= 0 && in < contents.size())
	{
		contents.at(in)->run(current, origin, inputs);
		return true;
	}
	return false;
}

ProcessManager::~ProcessManager()
{
	for(int i = 0; i < contents.size(); i++)
		delete contents[i];
}

//void Process_add::run(Variable& current, Function* origin, vector<Expression>& inputs)
//{
//	Process::run(current, origin, inputs);
//	if(inputs.size() > 0)
//	{
//		if(current.getValue().find("\"") == string::npos)
//		{
//			complex<double> currentComplex = complex<double>(current.getValuef(), current.complex);
//			complex<double> inComplex = complex<double>(inputs[0].evaluate(origin).getValuef(), inputs[0].evaluate(origin).complex);
//		
//			currentComplex += inComplex;
//			
//			current.setValue(utility.stringOf(currentComplex.real()));
//			current.complex = currentComplex.imag();
//		}
//		else
//		{
//			current.setValue("\"" + utility.strip(current.getValue(), "\"") +  utility.strip(inputs[0].evaluate(origin).getValue(), "\"") + "\"" );
//		}		 
//	}
//}

ProcessManager processManager;
ProcessManager_statement processManager_statement;