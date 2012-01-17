#include "Expression.h"
#include "Variable.h"
#include "Utility.h"
#include <complex>
#include "Keyword.h"
#include "Math.h"
#include "Function.h"
//#import "OutputListing.h"
#import "Expression.h"
#import "Parser.h"

using namespace std;

class Function;
class Variable;

class Process
{
private:
	string identifier;
public:
	string getIdentifier()
	{
		return identifier;
	}
	void setIdentifier(string in)
	{
		identifier = in;
	}	
	virtual void run(Variable& current, Function* origin, vector<Expression>& inputs){};
};

class Process_operator_add : public Process
{
public:
	Process_operator_add(string in)
	{ setIdentifier(in); }
	void run(Variable& current, Function* origin, vector<Expression>& inputs)
	{
		Process::run(current, origin, inputs);
		if(inputs.size() > 0)
		{
			if(current.getValue().find("\"") == string::npos)
			{
				complex<double> currentComplex = complex<double>(current.getValuef(), current.complex);
				complex<double> inComplex = complex<double>(inputs[0].evaluate(origin).getValuef(), inputs[0].evaluate(origin).complex);
				
				currentComplex += inComplex;
				
				current.setValue(utility.stringOf(currentComplex.real()));
				current.complex = currentComplex.imag();
			}
			else
			{
				current.setValue("\"" + utility.strip(current.getValue(), "\"") +  utility.strip(inputs[0].evaluate(origin).getValue(), "\"") + "\"" );
			}		 
		}
	}	
};

class Process_operator_subtract : public Process
{
public:
	Process_operator_subtract(string in)
	{ setIdentifier(in); }
	void run(Variable& current, Function* origin, vector<Expression>& inputs)
	{
		Process::run(current, origin, inputs);
		if(inputs.size() > 0)
		{
			if(current.getValue().find("\"") == string::npos)
			{
				complex<double> currentComplex = complex<double>(current.getValuef(), current.complex);
				
				Variable v = inputs[0].evaluate(origin);
				complex<double> inComplex = complex<double>(v.getValuef(), v.complex);
				
				currentComplex -= inComplex;
				
				current.setValue(utility.stringOf(currentComplex.real()));
				current.complex = currentComplex.imag();
			}
			else
			{
				current.setValue("\"" + utility.strip(current.getValue(), "\"") +  utility.strip(inputs[0].evaluate(origin).getValue(), "\"") + "\"" );
			}		 
		}
	}	
};

class Process_operator_multiply : public Process
{
public:
	Process_operator_multiply(string in)
	{ setIdentifier(in); }
	
	void run(Variable& current, Function* origin, vector<Expression>& inputs)
	{
		if(inputs.size() > 0)
		{	
			complex<double> currentComplex = complex<double>(current.getValuef(), current.complex);
			
			Variable v = inputs[0].evaluate(origin);
			complex<double> inComplex = complex<double>(v.getValuef(), v.complex);
			
			currentComplex *= inComplex;
			
			current.setValue(utility.stringOf(currentComplex.real()));
			current.complex = currentComplex.imag();
		}
	}
};

class Process_statement_if : public Process
{
public:
	Process_statement_if(string in)
	{ setIdentifier(in); }
	void run(Variable& current, Function* origin, vector<Expression>& inputs)
	{
		if( origin->skipping || (inputs.size() > 0 && inputs[0].evaluate(origin).getValuef() <= 0 && origin) )
		{
			origin->skipping++;
		}
	}	
};

class Process_statement_else : public Process
{
public:
	Process_statement_else(string in)
	{ setIdentifier(in); }
	void run(Variable& current, Function* origin, vector<Expression>& inputs)
	{
		if(origin->skipping == 1)
			origin->skipping = 0;
		else if(origin->skipping == 0)
			origin->skipping = 1;	
	}	
};

class Process_operator_divide : public Process
{
public:
	Process_operator_divide(string in)
	{ setIdentifier(in); }
	void run(Variable& current, Function* origin, vector<Expression>& inputs)
	{
		if(inputs.size() > 0)
		{	
			complex<double> currentComplex = complex<double>(current.getValuef(), current.complex);
			
			Variable v = inputs[0].evaluate(origin);
			complex<double> inComplex = complex<double>(v.getValuef(), v.complex);
			
			if(inComplex.real() != 0)
			{
				currentComplex /= inComplex;
				current.setValue(utility.stringOf(currentComplex.real()));
				current.complex = currentComplex.imag();
			}
			else
			{
				//				UIAlertView* av = [[UIAlertView alloc] initWithTitle:@"Warning" message:@"Divide by zero detected, skipping." delegate:nil cancelButtonTitle:@"Okay" otherButtonTitles:nil];
				//				[av show];			
				current.setValue("0");
				current.complex = 0;
			}
		}
	}
};

class Process_operator_root : public Process
{
public:
	Process_operator_root(string in)
	{ setIdentifier(in); }
	void run(Variable& current, Function* origin, vector<Expression>& inputs)
	{
		if(inputs.size() > 0)
		{	
			complex<double> currentComplex = complex<double>(current.getValuef(), current.complex);
			
			Variable v = inputs[0].evaluate(origin);
			
			complex<double> inComplex = complex<double>(v.getValuef(), v.complex);
			
			currentComplex =  sqrt(inComplex);
			
			current.setValue(utility.stringOf(currentComplex.real()));
			current.complex = currentComplex.imag();
		}		
	}	
};



class Process_round : public Process
{
public:
	Process_round(string in)
	{ setIdentifier(in); }
	void run(Variable& current, Function* origin, vector<Expression>& inputs)
	{
		if(inputs.size() == 1)
		{	
			current.setValue(round(inputs[0].evaluate(origin).getValuef()));
			current.complex = 0;
		}
		else if(inputs.size() > 1)
		{
			float val = inputs[0].evaluate(origin).getValuef();
			int digit = inputs[1].evaluate(origin).getValuef();
			current.setValue(round( val * pow(10.0f, digit)) / pow(10.0f, digit));
			current.complex = 0;
		}
	}	
};


class Process_floor : public Process
{
public:
	Process_floor(string in)
	{ setIdentifier(in); }
	void run(Variable& current, Function* origin, vector<Expression>& inputs)
	{
		if(inputs.size() > 0)
		{	
			current.setValue(floor(inputs[0].evaluate(origin).getValuef()));
			current.complex = 0;
		}
	}	
};

class Process_sin : public Process
{
public:
	Process_sin(string in)
	{ setIdentifier(in); }
	void run(Variable& current, Function* origin, vector<Expression>& inputs)
	{
		if(inputs.size() > 0)
		{	
			complex<double> currentComplex = complex<double>(current.getValuef(), current.complex);
			
			Variable v = inputs[0].evaluate(origin);
			complex<double> inComplex = complex<double>(v.getValuef(), v.complex);			
			
			inComplex *= math.pi()/180;
			
			currentComplex = sin( inComplex );	
			
			current.setValue(utility.stringOf(currentComplex.real()));
			current.complex = currentComplex.imag();
		}
	}	
};

class Process_log : public Process
{
public:
	Process_log(string in)
	{ setIdentifier(in); }
	void run(Variable& current, Function* origin, vector<Expression>& inputs)
	{
		if(inputs.size() > 0)
		{	
			complex<double> currentComplex = complex<double>(current.getValuef(), current.complex);
			
			Variable v = inputs[0].evaluate(origin);
			complex<double> inComplex = complex<double>(v.getValuef(), v.complex);			
			
			currentComplex = log( inComplex );	
			
			current.setValue(utility.stringOf(currentComplex.real()));
			current.complex = currentComplex.imag();
		}
	}	
};



class Process_cos : public Process
{
public:
	Process_cos(string in)
	{ setIdentifier(in); }
	void run(Variable& current, Function* origin, vector<Expression>& inputs)
	{
		if(inputs.size() > 0)
		{	
			complex<double> currentComplex = complex<double>(current.getValuef(), current.complex);
			
			Variable v = inputs[0].evaluate(origin);
			complex<double> inComplex = complex<double>(v.getValuef(), v.complex);			
			
			inComplex *= math.pi()/180;
			
			currentComplex = cos( inComplex );	
			
			current.setValue(utility.stringOf(currentComplex.real()));
			current.complex = currentComplex.imag();
		}			
	}	
};



class Process_tan : public Process
{
public:
	Process_tan(string in)
	{ setIdentifier(in); }
	void run(Variable& current, Function* origin, vector<Expression>& inputs)
	{
		if(inputs.size() > 0)
		{	
			complex<double> currentComplex = complex<double>(current.getValuef(), current.complex);
			
			Variable v = inputs[0].evaluate(origin);
			complex<double> inComplex = complex<double>(v.getValuef(), v.complex);			
			
			inComplex *= math.pi()/180.0;
			
			currentComplex = tan( inComplex );	
			
			current.setValue(utility.stringOf(currentComplex.real()));
			current.complex = currentComplex.imag();
		}	
	}	
};

class Process_imag : public Process
{
public:
	Process_imag(string in)
	{ setIdentifier(in); }
	void run(Variable& current, Function* origin, vector<Expression>& inputs)
	{
		if(inputs.size() > 0)
		{	
			Variable v = inputs[0].evaluate(origin);
			
			current.setValue(utility.stringOf(v.complex));
			current.complex = 0;			
		}
	}
};

class Process_real : public Process
{
public:
	Process_real(string in)
	{ setIdentifier(in); }
	
	void run(Variable& current, Function* origin, vector<Expression>& inputs)
	{
		if(inputs.size() > 0)
		{	
			Variable v = inputs[0].evaluate(origin);
			
			current.setValue(v.getValue());
			current.complex = 0;			
		}
	}
};

class Process_asin : public Process
{
public:
	Process_asin(string in)
	{ setIdentifier(in); }
	void run(Variable& current, Function* origin, vector<Expression>& inputs)
	{
		if(inputs.size() > 0)
		{	
			current.setValue(utility.stringOf(asin( inputs[0].evaluate(origin).getValuef()) *180/math.pi()));
		}
	}	
};

class Process_acos : public Process
{
public:
	Process_acos(string in)
	{ setIdentifier(in); }
	void run(Variable& current, Function* origin, vector<Expression>& inputs)
	{
		if(inputs.size() > 0)
		{
			current.setValue(utility.stringOf(acos(inputs[0].evaluate(origin).getValuef()) *180/math.pi() ));
		}
	}	
};

class Process_atan : public Process
{
public:
	Process_atan(string in)
	{ setIdentifier(in); }
	void run(Variable& current, Function* origin, vector<Expression>& inputs)
	{
		if(inputs.size() > 0)
		{	
			current.setValue(utility.stringOf(atan(inputs[0].evaluate(origin).getValuef()) *180/math.pi()));
		}
	}	
};

class Process_operator_mod : public Process
{
public:
	Process_operator_mod(string in)
	{ setIdentifier(in); }
	void run(Variable& current, Function* origin, vector<Expression>& inputs)
	{
		if(inputs.size() > 0)
		{	
			Variable v = inputs[0].evaluate(origin);
			
			current.setValue(utility.stringOf(fmod(current.getValuef(), v.getValuef())));
		}
	}	
};

class Process_operator_exponent : public Process
{
public:
	Process_operator_exponent(string in)
	{ setIdentifier(in); }
	void run(Variable& current, Function* origin, vector<Expression>& inputs)
	{
		if(inputs.size() > 0)
		{	
			complex<double> currentComplex = complex<double>(current.getValuef(), current.complex);
			
			Variable v = inputs[0].evaluate(origin);
			complex<double> inComplex = complex<double>(v.getValuef(), v.complex);			
			
			currentComplex = pow(currentComplex, inComplex);	
			
			current.setValue(utility.stringOf(currentComplex.real()));
			current.complex = currentComplex.imag();
		}		
	}	
};

class Process_operator_compare_less : public Process
{
public:
	Process_operator_compare_less(string in)
	{ setIdentifier(in); }
	void run(Variable& current, Function* origin, vector<Expression>& inputs)
	{
		if(inputs.size() > 0)
		{
			current.setValue(utility.stringOf((int)(current.getValuef() < inputs[0].evaluate(origin).getValuef())));				
		}		
	}	
};

class Process_operator_compare_greater : public Process
{
public:
	Process_operator_compare_greater(string in)
	{ setIdentifier(in); }
	void run(Variable& current, Function* origin, vector<Expression>& inputs)
	{
		if(inputs.size() > 0)
		{
			current.setValue(utility.stringOf((int)(current.getValuef() > inputs[0].evaluate(origin).getValuef())));				
		}		
	}	
};

class Process_operator_compare_less_equal : public Process
{
public:
	Process_operator_compare_less_equal(string in)
	{ setIdentifier(in); }
	void run(Variable& current, Function* origin, vector<Expression>& inputs)
	{
		if(inputs.size() > 0)
		{
			current.setValue(utility.stringOf((int)(current.getValuef() <= inputs[0].evaluate(origin).getValuef())));				
		}
	}	
};

class Process_operator_compare_greater_equal : public Process
{
public:
	Process_operator_compare_greater_equal(string in)
	{ setIdentifier(in); }
	void run(Variable& current, Function* origin, vector<Expression>& inputs)
	{
		if(inputs.size() > 0)
		{
			current.setValue(utility.stringOf((int)(current.getValuef() >= inputs[0].evaluate(origin).getValuef())));				
		}		
	}	
};

class Process_operator_compare_equal : public Process
{
public:
	Process_operator_compare_equal(string in)
	{ setIdentifier(in); }
	void run(Variable& current, Function* origin, vector<Expression>& inputs)
	{
		if(inputs.size() > 0)
		{
			current.setValue(utility.stringOf((int)(current.getValue() == inputs[0].evaluate(origin).getValue())));				
		}		
	}	
};

class Process_operator_compare_and : public Process
{
public:
	Process_operator_compare_and(string in)
	{ setIdentifier(in); }
	void run(Variable& current, Function* origin, vector<Expression>& inputs)
	{
		if(inputs.size() > 0)
		{
			current.setValue(utility.stringOf((int)(current.getValuef() && inputs[0].evaluate(origin).getValuef())));				
		}		
	}	
};

class Process_operator_compare_or : public Process
{
public:
	Process_operator_compare_or(string in)
	{ setIdentifier(in); }
	void run(Variable& current, Function* origin, vector<Expression>& inputs)
	{
		if(inputs.size() > 0)
		{
			current.setValue(utility.stringOf((int)(current.getValuef() || inputs[0].evaluate(origin).getValuef())));				
		}		
	}	
};

class Process_operator_compare_invert : public Process
{
public:
	Process_operator_compare_invert(string in)
	{ setIdentifier(in); }
	void run(Variable& current, Function* origin, vector<Expression>& inputs)
	{
		if(inputs.size() > 0)
		{
			current.setValue(utility.stringOf(!inputs[0].evaluate(origin).getValuef()));				
		}
	}	
};

class Process_constant_boolean_true : public Process
{
public:
	Process_constant_boolean_true(string in)
	{ setIdentifier(in); }
	void run(Variable& current, Function* origin, vector<Expression>& inputs)
	{
		current.setValue(utility.stringOf(1));		
	}	
};

class Process_constant_boolean_false : public Process
{
public:
	Process_constant_boolean_false(string in)
	{ setIdentifier(in); }
	void run(Variable& current, Function* origin, vector<Expression>& inputs)
	{
		current.setValue(utility.stringOf(0));						
	}	
};

class Process_constant_pi : public Process
{
public:
	Process_constant_pi(string in)
	{ setIdentifier(in); }
	void run(Variable& current, Function* origin, vector<Expression>& inputs)
	{
		current.setValue(utility.stringOf(math.pi()));
	}	
};

class Process_constant_e : public Process
{
public:
	Process_constant_e(string in)
	{ setIdentifier(in); }
	void run(Variable& current, Function* origin, vector<Expression>& inputs)
	{
		current.setValue(utility.stringOf(2.71828183));		
	}	
};

class Process_date_year : public Process
{
public:
	Process_date_year(string in)
	{ setIdentifier(in); }
	void run(Variable& current, Function* origin, vector<Expression>& inputs)
	{
		CFGregorianDate gregDate = CFAbsoluteTimeGetGregorianDate(CFAbsoluteTimeGetCurrent(), CFTimeZoneCopyDefault());
		current.setValue(utility.stringOf((int)gregDate.year));		
	}	
};


class Process_date_month : public Process
{
public:
	Process_date_month(string in)
	{ setIdentifier(in); }
	void run(Variable& current, Function* origin, vector<Expression>& inputs)
	{
		CFGregorianDate gregDate = CFAbsoluteTimeGetGregorianDate(CFAbsoluteTimeGetCurrent(), CFTimeZoneCopyDefault());
		current.setValue(utility.stringOf(gregDate.month));		
	}	
};


class Process_date_day : public Process
{
public:
	Process_date_day(string in)
	{ setIdentifier(in); }
	void run(Variable& current, Function* origin, vector<Expression>& inputs)
	{
		CFGregorianDate gregDate = CFAbsoluteTimeGetGregorianDate(CFAbsoluteTimeGetCurrent(), CFTimeZoneCopyDefault());
		current.setValue(utility.stringOf(gregDate.day));		
	}	
};

class Process_date_hour : public Process
{
public:
	Process_date_hour(string in)
	{ setIdentifier(in); }
	void run(Variable& current, Function* origin, vector<Expression>& inputs)
	{
		CFGregorianDate gregDate = CFAbsoluteTimeGetGregorianDate(CFAbsoluteTimeGetCurrent(), CFTimeZoneCopyDefault());
		current.setValue(utility.stringOf(gregDate.hour));		
	}	
};

class Process_date_minute : public Process
{
public:
	Process_date_minute(string in)
	{ setIdentifier(in); }
	void run(Variable& current, Function* origin, vector<Expression>& inputs)
	{
		CFGregorianDate gregDate = CFAbsoluteTimeGetGregorianDate(CFAbsoluteTimeGetCurrent(), CFTimeZoneCopyDefault());
		current.setValue(utility.stringOf(gregDate.minute));		
	}	
};

class Process_date_second : public Process
{
public:
	Process_date_second(string in)
	{ setIdentifier(in); }
	void run(Variable& current, Function* origin, vector<Expression>& inputs)
	{
		CFGregorianDate gregDate = CFAbsoluteTimeGetGregorianDate(CFAbsoluteTimeGetCurrent(), CFTimeZoneCopyDefault());
		current.setValue(utility.stringOf(gregDate.second));		
	}	
};


class Process_constant_deg : public Process
{
public:
	Process_constant_deg(string in)
	{ setIdentifier(in); }
	void run(Variable& current, Function* origin, vector<Expression>& inputs)
	{
		current.setValue(utility.stringOf(180 / math.pi()));		
	}	
};

class Process_constant_rad : public Process
{
public:
	Process_constant_rad(string in)
	{ setIdentifier(in); }
	void run(Variable& current, Function* origin, vector<Expression>& inputs)
	{
		current.setValue(utility.stringOf(math.pi() / 180));		
	}	
};

class Process_constant_complex : public Process
{
public:
	Process_constant_complex(string in)
	{ setIdentifier(in); }
	void run(Variable& current, Function* origin, vector<Expression>& inputs)
	{
		current.setValue("0");
		current.complex = 1;		
	}	
};


class Process_avg : public Process
{
public:
	Process_avg(string in)
	{ setIdentifier(in); }
	
	void run(Variable& current, Function* origin, vector<Expression>& inputs)
	{
		double total = 0;
		vector<Variable> v; 
		for(int i = 0; i < inputs.size(); i++)
		{
			Variable iv = inputs[i].evaluate(origin);
			if(iv.variables.size())
				for(int j = 0; j < iv.variables.size(); j++)
					v.push_back(iv.variables[j]);
			else
				v.push_back(iv);
		}
		for(int i = 0; i < v.size(); i++)
			total += v[i].getValuef();
		
		if(v.size())
			current.setValue(utility.stringOf(total/v.size()));
		else
		{
//			UIAlertView* av = [[UIAlertView alloc] initWithTitle:@"Warning" message:@"No units to average." delegate:nil cancelButtonTitle:@"Okay" otherButtonTitles:nil];
//			[av show];
		}
	}	
};

class Process_add : public Process
{
public:
	Process_add(string in)
	{ setIdentifier(in); }
	
	void run(Variable& current, Function* origin, vector<Expression>& inputs)
	{
		if(inputs.size() == 2)
		{
			Variable* vptr = inputs[0].getReference(origin);
			if(vptr)
			{
				Variable v = inputs[1].evaluate(origin);
				vptr->variables.push_back(v);
			}
		}
		else if(inputs.size() == 3)
		{
			Variable* vptr = inputs[0].getReference(origin);
			if(vptr)
			{
				Variable v = inputs[1].evaluate(origin);
				int index = inputs[2].evaluate(origin).getValuef();
				if(index >= 0 && index < vptr->variables.size())
					vptr->variables.insert(vptr->variables.begin() + index, v);
			}
		}
	}	
};


class Process_remove : public Process
{
public:
	Process_remove(string in)
	{ setIdentifier(in); }
	void run(Variable& current, Function* origin, vector<Expression>& inputs)
	{
		if(inputs.size() == 1)
		{
			Variable* vptr = inputs[0].getReference(origin);
			if(vptr)
			{
				vptr->variables.pop_back();
			}
		}
		else if(inputs.size() == 2)
		{
			Variable* vptr = inputs[0].getReference(origin);
			if(vptr)
			{
				int index = inputs[1].evaluate(origin).getValuef();
				if(index >= 0 && index < vptr->variables.size())
					vptr->variables.erase(vptr->variables.begin() + index);
			}
		}
	}	
};


class Process_sum : public Process
{
public:
	Process_sum(string in)
	{ setIdentifier(in); }
	
	void run(Variable& current, Function* origin, vector<Expression>& inputs)
	{
		double total = 0;
		vector<Variable> v; 
		for(int i = 0; i < inputs.size(); i++)
		{
			Variable iv = inputs[i].evaluate(origin);
			if(iv.variables.size())
				for(int j = 0; j < iv.variables.size(); j++)
					v.push_back(iv.variables[j]);
			else
				v.push_back(iv);
		}
		for(int i = 0; i < v.size(); i++)
			total += v[i].getValuef();
		
		if(v.size())
			current.setValue(utility.stringOf(total));
		else
		{
			//			UIAlertView* av = [[UIAlertView alloc] initWithTitle:@"Warning" message:@"No units to sum." delegate:nil cancelButtonTitle:@"Okay" otherButtonTitles:nil];
			//			[av show];			
		}
	}	
};

class Process_abs : public Process
{
public:
	Process_abs(string in)
	{ setIdentifier(in); }
	
	void run(Variable& current, Function* origin, vector<Expression>& inputs)
	{
		double abs = 0;
		if(inputs.size())
			abs = math.abs((double)inputs[0].evaluate(origin).getValuef());
		current.setValue((utility.stringOf(abs)));		
	}	
};

class Process_max : public Process
{
public:
	Process_max(string in)
	{ setIdentifier(in); }
	
	void run(Variable& current, Function* origin, vector<Expression>& inputs)
	{
		vector<Variable> v; 
		for(int i = 0; i < inputs.size(); i++)
		{
			Variable iv = inputs[i].evaluate(origin);
			if(iv.variables.size())
				for(int j = 0; j < iv.variables.size(); j++)
					v.push_back(iv.variables[j]);
			else
				v.push_back(iv);
		}
		
		double max = 0;
		bool hasMax = false;
		for(int i = 0; i < v.size(); i++)
			if(v[i].getValuef() > max || !hasMax)
			{
				hasMax = true;
				max = v[i].getValuef();
			}
		current.setValue(utility.stringOf(max));		
	}	
};

class Process_min : public Process
{
public:
	Process_min(string in)
	{ setIdentifier(in); }
	
	void run(Variable& current, Function* origin, vector<Expression>& inputs)
	{
		vector<Variable> v; 
		for(int i = 0; i < inputs.size(); i++)
		{
			Variable iv = inputs[i].evaluate(origin);
			if(iv.variables.size())
				for(int j = 0; j < iv.variables.size(); j++)
					v.push_back(iv.variables[j]);
			else
				v.push_back(iv);
		}
		
		double min = 0;
		bool hasMin = false;
		for(int i = 0; i < v.size(); i++)
			if(v[i].getValuef() < min || !hasMin)
			{
				hasMin = true;
				min = v[i].getValuef();
			}
		current.setValue(utility.stringOf(min));		
	}	
};

class Process_charAt : public Process
{
public:
	Process_charAt(string in)
	{ setIdentifier(in); }
	
	void run(Variable& current, Function* origin, vector<Expression>& inputs)
	{
		if(inputs.size() == 2)
		{
			int location = inputs[0].evaluate(origin).getValuef();
			string source = utility.strip(inputs[1].evaluate(origin).getValue(),"\"");
			if(location < source.length() && location >= 0)
			{
				string temp;
				temp += source[location];
				current.setValue(temp);
			}
		}
	}	
};

class Process_statement_out : public Process
{
public:
	Process_statement_out(string in)
	{ setIdentifier(in); }
	void run(Variable& current, Function* origin, vector<Expression>& inputs)
	{
		if(inputs.size() > 0)
		{
			if(origin)
			{
				origin->shouldOut = true;
				Variable v = inputs[0].evaluate(origin);
				v.setName(origin->getName());
				current = v;
			}		
		}
	}	
};

class Process_random : public Process
{
public:
	Process_random(string in)
	{ setIdentifier(in); }
	void run(Variable& current, Function* origin, vector<Expression>& inputs)
	{
		double randm = RAND_MAX;
		randm = rand()/randm;
		if(inputs.size() == 0)
			current.setValue(utility.stringOf(randm));
		else if(inputs.size() == 1)
		{
			current.setValue((utility.stringOf(randm * inputs[0].evaluate(origin).getValuef())));
		}		
	}	
};

class Process_statement_end : public Process
{
public:
	Process_statement_end(string in)
	{ setIdentifier(in); }
	void run(Variable& current, Function* origin, vector<Expression>& inputs)
	{
		if(origin->skipping > 0)	
			origin->skipping--;
	}	
};

class Process_statement_next : public Process
{
public:
	Process_statement_next(string in)
	{ setIdentifier(in); }
	void run(Variable& current, Function* origin, vector<Expression>& inputs)
	{
		if(origin->loops.size() > 0 && !origin->skipping)
			origin->current = origin->loops[origin->loops.size() -1] - 1;
		if(origin->skipping > 0)	
			origin->skipping--;						
		
		if(!origin->skipping)
		{
			if(inputs.size())
			{
				Variable* vptr = inputs[0].getReference(origin);
				if(vptr)
				{
					double crnt = vptr->getValuef();
					if(inputs.size() == 2)
					{
						Variable incV = inputs[1].evaluate(origin);
						crnt += incV.getValuef();
					}
					else
						crnt += 1;
					
					vptr->value = utility.stringOf(crnt);
				}
			}
		}
	}
};


class Process_statement_loop : public Process
{
public:
	Process_statement_loop(string in)
	{
		setIdentifier(in);
	}
	
	void run(Variable& current, Function* origin, vector<Expression>& inputs)
	{
		if(!origin->skipping && inputs.size() > 0)	
		{
			if(origin->loops.size() == 0 || origin->loops[origin->loops.size()-1] != origin->current)
			{
				origin->loops.push_back(origin->current);			
			}
			else
			{
				for(int i = 1; i < inputs.size(); i++)
				{
					inputs[i].evaluate(origin);
				}
			}
			if(inputs.size() && inputs[0].evaluate(origin).getValuef() <= 0)
			{
				if(origin->loops.size() > 0 && origin->loops[origin->loops.size()-1] == origin->current)
					origin->loops.pop_back();
				origin->skipping++;
			}
		}
		else
		{
			origin->skipping++;
		}		
	}	
};

class Process_statement_list : public Process
{
public:
	Process_statement_list(string in)
	{
		setIdentifier(in);
	}
	
	void run(Variable& current, Function* origin, vector<Expression>& inputs)
	{
		Variable v;
		for(int j = 0; j < inputs.size(); j++)
		{		
			int size = inputs[j].evaluate(origin).getValuef();
			v.allocate(j, size);
		}
		current = v;		
	}	
};

class Process_statement_alloc : public Process
{
public:
	Process_statement_alloc(string in)
	{
		setIdentifier(in);
	}
	
	void run(Variable& current, Function* origin, vector<Expression>& inputs)
	{
		Variable n;
		for(int i = 0; i < inputs.size(); i++)
		{
			n.variables.push_back(inputs[i].evaluate(origin));
		}	
		current = n;		
	}	
};


class Process_plot : public Process
{
public:
	Process_plot(string in)
	{
		setIdentifier(in);
	}
	
	void run(Variable& current, Function* origin, vector<Expression>& inputs)
	{
		if(inputs.size())
		{
			// Removed on the Mac for now.
//			OutputListing* listing = [[OutputListing alloc] init];
//			listing.type = 1;		
//			listing.variable = new Variable;
//			for(int i = 0; i < inputs.size(); i++)
//			{
//				listing.variable->variables.push_back(inputs[i].evaluate(origin));	
//			}
//			
//			[utility.outputController addOutput:listing];
		}
		current = Variable();
	}	
};

class Process_print : public Process
{
public:
	Process_print(string in)
	{ setIdentifier(in); }
	
	void run(Variable& current, Function* origin, vector<Expression>& inputs)
	{
		Variable printV;
		string fullData;
		for(int i = 0; i < inputs.size(); i++)
		{
			fullData += inputs[i].evaluate(origin).getValue();
		}
		printV.setValue(fullData);
		
		//			[utility.outputController addOutputVariable:printV];		
	}	
};

class Process_eval : public Process
{
public:
	Process_eval(string in)
	{
		setIdentifier(in);
	}
	
	void run(Variable& current, Function* origin, vector<Expression>& inputs)
	{
		Variable printV;
		string fullData;
		for(int i = 0; i < inputs.size(); i++)
		{
			fullData += inputs[i].evaluate(origin).getValue();
		}
		fullData = utility.strip(fullData, "\"");
		current.setValue(fullData);
		
		vector<string> data = utility.split(fullData, " -_+/*%<>?,!|•#@^[]\\{}()=;:&");
		
		for(int j = 0; j < data.size(); j++)
		{
			data[j] = utility.strip(data[j], " :;"); 
		}
		
		//discard any empty data segments
		for(int j = 0; j < data.size(); j++)
		{
			if(data[j] == "")
			{
				data.erase(data.begin() + j);
				j--;
			}
		}
		
		Parser parser;
		parser.setMathShortcuts(data);
		parser.setLists(data);
		parser.setOrders(data);
		parser.setOperatorInput(data);
		
		int x = 0;
		Expression e = parser.getExpression(data, x);
		
		current.setValue(e.evaluate(origin).getValue());
	}
};

class Process_size : public Process
{
public:
	Process_size(string in)
	{ setIdentifier(in); }
	
	void run(Variable& current, Function* origin, vector<Expression>& inputs)
	{
		if(inputs.size())
			current.setValue(utility.stringOf((int)inputs[0].evaluate(origin).variables.size()));		
	}	
};

class ProcessManager
{
public:
	vector<Process*> contents;
	int getProcessIndex(string identifier);
	bool runIndex(int in, Variable& current, Function* origin, vector<Expression>& inputs);
	~ProcessManager();
	ProcessManager();
};

class ProcessManager_statement : public ProcessManager
{
public:
	ProcessManager_statement();
};

extern ProcessManager processManager;
extern ProcessManager_statement processManager_statement;
