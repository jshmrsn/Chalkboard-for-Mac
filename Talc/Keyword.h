#ifndef Keywords_included
#define Keywords_included

#include <string>
#include <vector>
#import "Utility.h"
using namespace std;

class Keyword
{
public:
	Keyword();
	
	string operator_add;
	string operator_subtract;
	string operator_multiply[2];
	string operator_divide;			
	string operator_mod;
	string operator_root;
	string operator_exponent;

	string operator_equal;

	string operator_equal_add;
	string operator_equal_subtract;	
	string operator_equal_multiply[2];
	string operator_equal_divide;
		
	string operator_compare_less;
	string operator_compare_greater;
	
	string operator_compare_less_equal;
	string operator_compare_greater_equal;		

	string operator_compare_equal;
	
	string operator_compare_and;
	string operator_compare_or;	
	
	string operator_compare_invert;
		
	string header_function;
	string header_comment;
	
	string constant_pi;
	string constant_e;
	string constant_complex;
	string constant_boolean_true;
	string constant_boolean_false;	

	string scope_function_input_open;
	string scope_function_input_close;

	string scope_list_open;
	string scope_list_close;

	string scope_math_open;
	string scope_math_close;
	
	string statement_if;
	string statement_else;
	string statement_end;
	string statement_loop;
	string statement_out;
	string statement_print;
	string separator;
	
	string statement_list;

	string defaultPath;
	string defaultSourceName;
	string defaultExt;
	string organizerListBackground;
	string editorOutputBackground;
	string editorBackground;
	string splash;
	string editorFont;
	
	bool autoSizeFont;
	int editorFontSize;	
};

extern Keyword key;

#endif