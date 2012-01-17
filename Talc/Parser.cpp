#include "Parser.h"
#include "Utility.h"
#include "Keyword.h"
#include "Math.h"
using namespace std;

Parser::Parser()
{
	
}


Function Parser::parse(vector<string> content)
{
	vector<string> datas = utility.getCodeOf(content);
	string function_name = utility.getPropertyOf("cname", content, "myFunction");
	string function_inputs = utility.getPropertyOf("inputs", content, "");
	
	Function function;
	
	function.setName(function_name);
	
	vector<string> inps = utility.split(function_inputs, " ,");
	
	for(int z = 0; z < inps.size(); z++)
	{
		inps[z] = utility.strip(inps[z], " ");
		if(inps[z].length() &&  isAWord(inps[0]) )
			function.inputs.push_back(Variable(inps[z]));								
	}
	
	for(int i = 0; i < datas.size(); i++)
	{		
		int prevType = -1;
		for(int j = 0; j < datas[i].length(); j++)
		{
			int type = -1;
			string temp;
			temp += datas[i][j];
			
			if(isANumber(temp))
				type = 0;
			else if(isAWord(temp))
				type = 1;
			else if(temp == "(")
				type = 2;
			else if(temp == ")")
				type = 3;
						
			if(type != prevType && !(type == -1 || prevType == -1) && type < 2 && prevType < 2)
			{
				datas[i].insert(datas[i].begin() + j, ' ');
			}
			else if(type == 2 && prevType != -1 && prevType != type)
			{
				datas[i].insert(datas[i].begin() + j, ' ');			
			}
			else if(prevType == 3 && type != -1 && type != 2 && type != 3)
			{
				datas[i].insert(datas[i].begin() + j, ' ');			
			}
			prevType = type;
		}
	}
	
	
	for(int i = 0; i < datas.size(); i++)
	{
		string ndata = "";
		bool comment = false;
		for(int j = 0; j < datas[i].length(); j++)
		{
			if(datas[i][j] == '#')
				comment = !comment;
				
			if(comment)
				{}
			else
				ndata += datas[i][j];
		}
		datas[i] = ndata;
	}

	
	if(datas.size() > 0)
	{
		function.expressions.clear();

		int ln = 0;
		while(ln < datas.size())
		{
			vector<string> data;
			doNotPrintData = false;
			bool firstDataRead = true;
				while((firstDataRead || (data.size() > 0 && data[data.size()-1] == ":")) && ln < datas.size())
				{
					firstDataRead = false;
						string tem = "";
						vector<string> nextData = utility.split(datas[ln], tem + " -_+/*%<>?,!|•#@^[]\\{}()=;:&");
						for(int j = 0; j < nextData.size(); j++)
							nextData[j] = utility.strip(nextData[j], " \t\b\e\f\n\r\v");  //strip out any non relivent characters		
						
             
						for(int j = 0; j < nextData.size(); j++) //discard any empty data segments
							if(nextData[j] == "")
							{
								nextData.erase(nextData.begin() + j);
								j--;
							}						
				
						for(int j = 0; j < nextData.size(); j++)
							data.push_back(nextData[j]);
						
						ln++;
				}
				
				if(data.size() > 0 && data[data.size()-1] == ";")
					doNotPrintData = true;
				
				for(int j = 0; j < data.size(); j++)
					data[j] = utility.strip(data[j], ":;"); 
						
				for(int j = 0; j < data.size(); j++) //discard any empty data segments
					if(data[j] == "")
					{
						data.erase(data.begin() + j);
						j--;
					}
					
			setMathShortcuts(data);
			setLists(data);
			setOrders(data);
			setOperatorInput(data);
			
			
			for(int i = 0; i < data.size(); i++)
			{
				cout << data[i];
			}
			cout << endl;
			
			
			if(data.size() > 0)
			{
				if(data[0] == key.header_comment)
				{
				}			
				else
				{
					int i = 0;
					Expression expression = getExpression(data, i);
					expression.silenced = doNotPrintData;
					function.expressions.push_back(expression);
				}
			}
		}		
	}
	
	
	return function;
}

void Parser::setLists(vector<string>& data)
{
	for(int i = 0; i < data.size(); i++)
		if(data[i] == key.scope_list_open)
		{
			data.insert(data.begin()+i, "alloc");
			i++;
		}
		
	for(int i = 0; i < data.size(); i++)
		if(data[i] == key.scope_list_open)
			data[i] = key.scope_function_input_open;
		else if(data[i] == key.scope_list_close)
			data[i] = key.scope_function_input_close;
}


void Parser::setMathShortcuts(vector<string>& data)
{
	for(int i = 0; i < data.size(); i++)
		if(data[i] == "e")
		{
			data[i] = "*";
			i++;
			data.insert(data.begin()+i, "10");
			i++;
			data.insert(data.begin()+i, "^");
		}

		
	int prevType = -1;
	for(int j = 0; j < data.size(); j++)
	{	
		int type = -1;

		if(isAStatement(data[j]))
			type = 4;
		else if(isANumber(data[j]))
			type = 0;
		else if(isAWord(data[j]))
			type = 1;
		else if(data[j] == "(")
			type = 2;
		else if(data[j] == ")")
			type = 3;
			
		if(type == 4 || prevType == 4);
		else if(type != prevType && !(type == -1 || prevType == -1) && type < 2 && prevType < 2)
		{
			data.insert(data.begin() + j, "*");
			j++;
		}
		else if(type == 2 && prevType != -1 && prevType != type)
		{
			data.insert(data.begin() + j, "*");	
			j++;
		}
		else if(prevType == 3 && type != -1 && type != 2 && type != 3)
		{
			data.insert(data.begin() + j, "*");			
			j++;
		}
		prevType = type;
	}

	for(int i = 0; i < data.size(); i++)
		if(data[i] == key.scope_math_close && (i+1)<data.size() && data[i+1] == key.scope_math_open)
		{
			i++;
			data.insert(data.begin()+i, key.operator_multiply[0]);
		}
		


}

void Parser::setOrders(vector<string>& data)
{

	
	vector<string> ops;

	ops.push_back("\\");

	setSimpleOrder(data, ops);
	ops.clear();

	ops.push_back(key.operator_compare_invert);
	setOrder(data, ops);
	ops.clear();		

	ops.push_back(key.operator_exponent);
	setOrder(data, ops);
	ops.clear();
	
	ops.push_back(key.operator_multiply[0]);
	ops.push_back(key.operator_multiply[1]);
	ops.push_back(key.operator_divide);
	ops.push_back(key.operator_mod);
	setOrder(data, ops);
	ops.clear();
					
	ops.push_back(key.operator_add);
	ops.push_back(key.operator_subtract);
	setOrder(data, ops);
	ops.clear();

	ops.push_back(key.operator_compare_greater);
	ops.push_back(key.operator_compare_less);
	ops.push_back(key.operator_compare_greater_equal);
	ops.push_back(key.operator_compare_less_equal);
	ops.push_back(key.operator_compare_equal);						
	setOrder(data, ops);
	ops.clear();	

	ops.push_back(key.operator_compare_and);
	ops.push_back(key.operator_compare_or);
	setOrder(data, ops);
	ops.clear();

	ops.push_back(key.operator_equal);
	ops.push_back(key.operator_equal_add);
	ops.push_back(key.operator_equal_subtract);
	ops.push_back(key.operator_equal_multiply[0]);
	ops.push_back(key.operator_equal_multiply[1]);
	ops.push_back(key.operator_equal_divide);
				
	setOrder(data, ops);
	ops.clear();			
}

void Parser::setOrder(vector<string>& data, vector<string> operators)
{
			int i = 0;
			while(i < data.size())
			{
				bool shouldOrder = false;
				
				for(int j = 0; j < operators.size(); j++)
					if(data[i] == operators[j])
						shouldOrder = true;
				
//				if((i+1) < data.size())
//				{
//					cout << "d " << data[i+1] << endl;
//					if(data[i+1] == "[")
//						shouldOrder = false;
//				}
//				
				if(shouldOrder)
				{
					int k = i + 1; //preserve index of operator
					int within = 0; //within (s and )s
					while(k < data.size()) //continue to the right to find closing index
					{
						if(data[k] == key.scope_math_open || data[k] == key.scope_function_input_open || data[k] == key.scope_list_open)
							within++;
						else if(data[k] == key.scope_math_close || data[k] == key.scope_function_input_close ||data[k] == key.scope_list_close)
							within--;
							
						k++;
						
						if(!within)
						{	
							if(k < data.size() && data[k] == key.scope_function_input_open)
							{
								within++;
								k++;
							}
							else
								break;
						}
					}

					data.insert(data.begin() + k, key.scope_math_close);
					
					k = i - 1;
					within = 0; //within (s and )s
					while(k >= 0) //continue to the left to find opening index
					{
						if(data[k] == "=")
							break;
						if(data[k] == key.scope_math_open || data[k] == key.scope_function_input_open || data[k] == key.scope_list_open)
							within--;
						else if(data[k] == key.scope_math_close || data[k] == key.scope_function_input_close ||data[k] == key.scope_list_close)
							within++;

						k--;

						if(within == 0)
						{
							if(k < data.size() && k>=0 && data[k] == key.scope_function_input_close)
							{
								within++;
								k--;
							}
							break;
						}
						else if(within < 0)
						{
							k++;
							break;
						}						
					}
					
					if(data[k+1] == key.scope_function_input_open)
						k--;
					k = math.min(-1, k);
					data.insert(data.begin() + k + 1, key.scope_math_open);
					i++;		
				}
				i++;
			}
}

void Parser::setSimpleOrder(vector<string>& data, vector<string> operators)
{
			int i = 0;
			while(i < data.size())
			{
				bool shouldOrder = false;
				
				for(int j = 0; j < operators.size(); j++)
					if(data[i] == operators[j])
						shouldOrder = true;
				
				if(shouldOrder)
				{
					int k = i + 1; //preserve index of operator
					int within = 0; //within (s and )s
					while(k < data.size()) //continue to the right to find closing index
					{
						if(data[k] == key.scope_math_open || data[k] == key.scope_function_input_open || data[k] == key.scope_list_open)
							within++;
						else if(data[k] == key.scope_math_close || data[k] == key.scope_function_input_close ||data[k] == key.scope_list_close)
							within--;
							
						k++;
						
						if(!within)
						{	
							if(k < data.size() && data[k] == key.scope_function_input_open)
							{
								within++;
								k++;
							}
							else
								break;
						}
					}

					data.insert(data.begin() + k, key.scope_math_close);
					
					k = i - 1;
					
					
					
					k = math.min(-1, k);
					data.insert(data.begin() + k + 1, key.scope_math_open);
					
					
					i++;		
				}
				i++;
			}
}

void Parser::setOperatorInput(vector<string>& data)
{
			int i = data.size() - 1;
			while(i >= 0)
			{
				if(isAStatement(data[i]))
				{
					data.insert(data.begin() + i + 1, key.scope_function_input_open);	
					data.insert(data.begin() + data.size(), key.scope_function_input_close);																	
				}
				else if(isAOperator(data[i]))
				{
					data.insert(data.begin() + i + 1, key.scope_function_input_open);			
		
					int k = i + 2; //preserve index of operator
					int within = 0; //within (s and )s
					while(k < data.size()) //continue to the right to find closing index
					{
						if(data[k] == key.scope_math_open || data[k] == key.scope_function_input_open || data[k] == key.scope_list_open)
							within++;
						else if(data[k] == key.scope_math_close || data[k] == key.scope_function_input_close ||data[k] == key.scope_list_close)
							within--;
							
							k++;	
						if(!within)
						{	
							if(k < data.size() && data[k] == key.scope_function_input_open)
							{
								within++;
								k++;
							}
							else
								break;
						}
					}
					data.insert(data.begin() + k, key.scope_function_input_close);	
				}
				i--;
			}	
}

bool Parser::isAStatement(string in)
{
	string temp = "";
	temp += in[0];
	
	vector<string> operators;

	operators.push_back(key.statement_out);
	operators.push_back(key.statement_if);	
	operators.push_back("next");	
	operators.push_back(key.statement_loop);
	operators.push_back(key.statement_end);
	operators.push_back(key.statement_else);
	operators.push_back(key.statement_print);
	operators.push_back("add");
	operators.push_back("remove");
	operators.push_back("plot");


	if(utility.contains(operators, in))
		return true;
	return false;
}

bool Parser::isAOperator(string in)
{
	string temp = "";
	temp += in[0];
	
	vector<string> operators;
	operators.push_back(key.operator_add);
	operators.push_back(key.operator_subtract);
	operators.push_back(key.operator_multiply[0]);
	operators.push_back(key.operator_multiply[1]);
	
	operators.push_back(key.operator_divide);
	operators.push_back(key.operator_mod);
	operators.push_back(key.operator_compare_less);
	operators.push_back(key.operator_compare_greater);
	operators.push_back(key.operator_compare_equal);
	
	operators.push_back(key.operator_compare_less_equal);
	operators.push_back(key.operator_compare_greater_equal);
	operators.push_back(key.operator_compare_and);
	operators.push_back(key.operator_compare_or);
	operators.push_back(key.operator_exponent);
	operators.push_back(key.operator_root);		

	operators.push_back(key.operator_compare_invert);	

	if(utility.contains(operators, in))
		return true;
	return false;
}

bool Parser::isAWord(string in)
{
	if( (in[0] >= 'A' && in[0] <= 'Z') || (in[0] >= 'a' && in[0] <= 'z') )
		return true;
	return false;
}

bool Parser::isANumber(string in)
{
	if( (in[0] >= '0' && in[0] <= '9') || in[0] == '.' )
		return true;
	return false;
}

Expression Parser::getExpression(vector<string>& data, int& i)
{
	Expression out;
	int within = 0;
	for(i; i < data.size(); i++)
	{
		if(data[i] == key.separator)
			break;
		else if(data[i] == key.scope_math_open)
			within++;
		else if(data[i] == key.scope_math_close)
			within--;
		else
			out.operations.push_back(getOperation(data, i));
			 
		if(within < 0)
			break;
	}
	return out;
}

vector<Expression> Parser::getExpressions(vector<string>& data, int& i)
{
	vector<Expression> out;

	int within = 0;
	for(i; i < data.size(); i++)
	{
		if(data[i] == key.scope_math_open)
			within++;
		else if(data[i] == key.scope_math_close)
			within--;
		else
			out.push_back(getExpression(data, i));
		if(!within)
			break;
	}

	return out;
}


vector<Expression> Parser::getInputs(vector<string>& data, int& i)
{
	vector<Expression> out;
		if(data[i] == key.scope_function_input_open)
		{
			i++;
		}
	for(i; i < data.size(); i++)
	{
		if(data[i] == key.scope_function_input_close)
		{
			break;
		}
//		else if(data[i] == key.scope_math_open)
//			within++;
//		else if(data[i] == key.scope_math_close)
//			within--;
		else if(data[i] == ",")
		{}
		else
		{
			out.push_back(getInput(data, i));
		}

		if( i < data.size() && data[i] == key.scope_function_input_close)
		{	
			i--;
			break;
		}

	}
	return out;
}






Expression Parser::getInput(vector<string>& data, int& i)
{
	Expression out;
	int within = 0;
	for(i; i < data.size(); i++)
	{
		if(data[i] == key.separator)
			break;
		else if(data[i] == key.scope_math_open)
			within++;
		else if(data[i] == key.scope_math_close)
			within--;
		else if(data[i] == key.scope_function_input_close)
		{
			break;
		}
		else
			out.operations.push_back(getOperation(data, i));
			 
		if(within < 0)
			break;
	}
	return out;
}




double getLengthOfLine(string in)
{
	vector<string> lines = utility.split(in, "\n");
	
	double length = 1;
	for(int i = 0; i < in.size(); i++)
		if(in[i] == '.' || in[i] == ',' || in[i] == ';'|| in[i] == '|'|| in[i] == ')'|| in[i] == '}' || in[i] == ']' || in[i] == '('|| in[i] == '{' || in[i] == '[')
			length += 0.5;
		else 
			length += 1;
	
	return length;	
}


double Parser::getNumLines(string in)
{
	return utility.split(in, "\n").size();
}

double Parser::getLengthOfLongestLine(string in)
{
	vector<string> lines = utility.split(in, "\n");
	
	double length = 1;
	for(int i = 0; i < lines.size(); i++)
		if(getLengthOfLine(lines[i]) > length)
			length = getLengthOfLine(lines[i]);
	
	
	
	return length;	
}

Operation Parser::getOperation(vector<string>& data, int& i)
{
	Operation operation;
	if(i < data.size())
		operation.setInformation(data[i]);
	
	
	bool rhs = true;
	
	if(isAStatement(operation.information) || operation.information == "plot")
		doNotPrintData = true;	

	for(i; i < data.size() - 1; i++)
	{
		if(data[i+1] == key.scope_function_input_open)
		{
			rhs = false;
		}
		else if(rhs)
		{
			if(data[i+1] == key.operator_equal || data[i+1] == key.operator_equal_add || data[i+1] == key.operator_equal_subtract 
			|| data[i+1] == key.operator_equal_multiply[0] || data[i+1] == key.operator_equal_divide
			|| data[i+1] == key.operator_equal_multiply[1])
			{
				i++;
				if( (i+1) < data.size() )
				{
					doNotPrintData = true;	
					operation.assignmentType = data[i];
					i++;
					operation.assignment = getExpression(data, i);
					break;
				}
			}
			else 
			{
				break;
			}
		}
		else 
		{
			i++;
			if(data[i] == "]")
			{
				operation.inputs.clear();
				return operation;
			}
			else
				operation.inputs = getInputs(data, i);
			rhs = true;	
		}
	}
	return operation;
}
