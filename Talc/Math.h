#ifndef _Math_h_included_
#define _Math_h_included_

#include "MathVector.h"
#include "Quat.h"
#include "Range.h"
#include "RotationMatrix.h"

using namespace std;

/* Conveniently makes math functions available */

class Math
{
private:	
public:
	double pi();
	Math();
	bool coplaner(MathVector a, MathVector b, MathVector c, MathVector point); 
	bool intersect(MathVector a, MathVector b, MathVector c, MathVector origin, MathVector direction); // Does data(origin, direction) intersect triangle(a,b,c)
	bool intersect(MathVector a, MathVector b, MathVector c, MathVector origin, MathVector direction, MathVector& inter);	 // inter = where it intercepts
	double distance(MathVector a, MathVector b); // distance between a & b
	Quat rot2Quat(MathVector in); // convert a Rotation to a Quaternion
	MathVector cross(MathVector a, MathVector b); // cross product	
	double dot(MathVector a, MathVector b); // dot product
	double size(MathVector in);
	MathVector normal(MathVector a, MathVector b, MathVector c); // Get the normal of a triangle, represented by 3 points
	
	double ratio(double value, Range range); // convert value of range.min to range.max to value of 0 to 1
	double ratio(double min, double value, double max); // convert value of min to max to value of 0 to 1	
	
	double abs(double in); // Absolute value

	
	double clamp(double min, double current, double max); // limit current to the min and the max
	double min(double min, double current); // limit current to the min
	double max(double current, double max); // limit current to the max	
	
					//Is point(x,y) inside box (center, width, height) 
	bool squareIntersect(double pointx, double pointy, double boxcentx, double boxcenty, double boxw, double boxh);	//TODO: overload
	
	double random(); // 0 - 1 
	double random(double min, double max); // min - max	
	double random(Range); // range.min - range.max
	MathVector random(MathVector min, MathVector max);	 // min.(x,y,z) - max.(x,y,z)
	MathVector random(RangeVect rangeVect);  // rangeV.min.(x,y,z) - rangeV.max.(x,y,z)
};

extern Math math;

#endif

