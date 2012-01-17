#include "Range.h"

using namespace std;


Range::Range()
{
     min = -1;
     max = 1;             
}

Range::Range(double nmin, double nmax)
{
     min = nmin;
     max = nmax;             
}

double Range::size()
{
	return max - min;
}

RangeVect::RangeVect()
{
	
}

