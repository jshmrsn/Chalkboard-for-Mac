#ifndef _Program_h_included_
#define _Program_h_included_

#include "Function.h"
#include "Parser.h"

using namespace std;


class Program
{
private:

public:
	Function* getFunction(string in);
	Function* getFunction(string in, int inputs);
};


extern Program program;


#endif
