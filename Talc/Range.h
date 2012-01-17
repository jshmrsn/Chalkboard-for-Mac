#ifndef _Range_h_included_
#define _Range_h_included_

#include "MathVector.h"

using namespace std;

//Contains a minimum and maximum, mainly used for connivance when working with random
class Range
{
	public:
    double min, max;
    Range();
    Range(double, double);
	double size();
};

class RangeVect
{
	public:
	RangeVect();
	MathVector min, max;
};

#endif
