#ifndef _Quat_h_included_
#define _Quat_h_included_

#include "MathVector.h"

using namespace std;

// Not Documented
// Quaternion
// Used for rotation math

class Quat 
{
	public:
		Quat();
		Quat(double, MathVector);
		
		MathVector axes();
		double angle();
		MathVector rotation();	
			
		MathVector v;
		double scale;
		friend Quat operator*(const Quat& left, const Quat& right) 
		{
			Quat result;
			MathVector leftV = left.v;
			MathVector rightV = right.v;
			result.scale = left.scale * right.scale - leftV.dot(rightV);
			result.v = right.scale * left.v + left.scale * right.v + rightV.cross(leftV);
			return result;
		}
};

#endif


