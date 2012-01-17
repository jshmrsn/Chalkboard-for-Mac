#ifndef _RotationMatrix_h_included_
#define _RotationMatrix_h_included_

#include "MathVector.h"

using namespace std;

class RotationMatrix 
{
public:
	double x[3]; 
	double y[3]; 
	double z[3];
	RotationMatrix();
	friend MathVector operator*(const RotationMatrix& left, const MathVector& right) {
		MathVector result;
		result.x =  left.x[0]*right.x + left.x[1] * right.y + left.x[2]*right.z;
		result.y =  left.y[0]*right.x + left.y[1] * right.y + left.y[2]*right.z;
		result.z =  left.z[0]*right.x + left.z[1] * right.y + left.z[2]*right.z;
		return result;
	}
	friend RotationMatrix operator*(const RotationMatrix& left, const RotationMatrix& right) {
		RotationMatrix result;
		result.x[0] =  left.x[0]*right.x[0] + left.x[1] * right.y[0] + left.x[2]*right.z[0];
		result.x[1] =  left.x[0]*right.x[1] + left.x[1] * right.y[1] + left.x[2]*right.z[1];
		result.x[2] =  left.x[0]*right.x[2] + left.x[1] * right.y[2] + left.x[2]*right.z[2];

		result.y[0] =  left.y[0]*right.x[0] + left.y[1] * right.y[0] + left.y[2]*right.z[0];
		result.y[1] =  left.y[0]*right.x[1] + left.y[1] * right.y[1] + left.y[2]*right.z[1];
		result.y[2] =  left.y[0]*right.x[2] + left.y[1] * right.y[2] + left.y[2]*right.z[2];

		result.z[0] =  left.z[0]*right.x[0] + left.z[1] * right.y[0] + left.z[2]*right.z[0];
		result.z[1] =  left.z[0]*right.x[1] + left.z[1] * right.y[1] + left.z[2]*right.z[1];
		result.z[2] =  left.z[0]*right.x[2] + left.z[1] * right.y[2] + left.z[2]*right.z[2];
		return result;
	}
	
	void initialize()
	{
		x[0] = 1;
		x[1] = 0;	
		x[2] = 0;	
            
		y[0] = 0;	
		y[1] = 1;	
		y[2] = 0;	
            
		z[0] = 0;	
		z[1] = 0;	
		z[2] = 1;		
	}
	
	RotationMatrix transposed()
	{
		RotationMatrix out;
		out.x[0] = x[0];
		out.x[1] = y[0];	
		out.x[2] = z[0];	
		
		out.y[0] = x[1];
		out.y[1] = y[1];
		out.y[2] = z[1];	
    
		out.z[0] = x[2];	
		out.z[1] = y[2];	
		out.z[2] = z[2];
		return out;		
	}
	
	MathVector matrix2Rot()
	{
		return (*this * MathVector(1,1,1)).vect2Rot();
	}
};

#endif

