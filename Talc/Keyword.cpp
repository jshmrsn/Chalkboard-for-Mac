#include "Keyword.h"

Keyword::Keyword()
{
	operator_add = "+";
	operator_subtract = "-";
	operator_multiply[0] = "*";
	operator_multiply[1] = "•";
	operator_divide = "/";	
	operator_mod = "%";
	operator_root = "\\";
	operator_exponent = "^";
	
	operator_equal = "=";
	
	operator_equal_add = "+=";
	operator_equal_subtract = "-=";	
	operator_equal_multiply[0] = "*=";
	operator_equal_multiply[1] = "•=";
	operator_equal_divide = "/=";

	operator_compare_less = "<";
	operator_compare_greater = ">";

	operator_compare_less_equal = "<=";
	operator_compare_greater_equal = ">=";		

	operator_compare_equal = "<>";

	operator_compare_and = "&";
	operator_compare_or = "|";	

	operator_compare_invert = "!";

	scope_function_input_open = "[";
	scope_function_input_close = "]";

	scope_list_open = "{";
	scope_list_close = "}";
	
	separator = ",";

	scope_math_open = "(";
	scope_math_close = ")";

	header_comment = "#";
	header_function = "@";

	constant_pi = "pi";
	constant_e = "e";
	constant_complex = "i";
	constant_boolean_true = "true";
	constant_boolean_false = "false";
	
	statement_if = "if";
	statement_else = "else";
	statement_end = "end";
	statement_loop = "loop";
	statement_out = "out";	
	statement_list = "list";
	statement_print = "print";

	defaultPath = "/Chalkboard/Sources/";
	defaultSourceName = "source";
	defaultExt = "talc";

	organizerListBackground = "Parchment.png";
	editorOutputBackground = "Paper.png";
	editorBackground = "GreenBoard.png";
	splash = "Default.png";
	editorFont = "Marker Felt";
	editorFontSize = 16;
	autoSizeFont = true;
}

Keyword key;
