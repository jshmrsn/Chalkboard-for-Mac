#include "MathVector.h"
#include "Quat.h"
#include "Math.h"
#include "Utility.h"

using namespace std;

MathVector::MathVector()
{
	x = 0;
	y = 0;
	z = 0;
}

MathVector::MathVector(double nx) {
	x = nx;
	y = nx;
	z = nx;
}

MathVector::MathVector(double nx, double ny) {
	x = nx;
	y = ny;
	z = 0;
}

MathVector::MathVector(double nx, double ny, double nz) {
	x = nx;
	y = ny;
	z = nz;
}

void MathVector::normalize()
{
	double s = size();
	*this *= 1/math.min(0.00001, s ); 
}

MathVector MathVector::normalized()
{
	return *this * 1/math.min(0.00001, size() );
}

MathVector MathVector::cross(MathVector b)
{
	MathVector a = *this;
	MathVector c;
		c.x=a.y*b.z-a.z*b.y;
		c.y=a.z*b.x-a.x*b.z;
		c.z=a.x*b.y-a.y*b.x;
	return  c;		
}

double MathVector::dot(MathVector b)
{
	MathVector a = *this;
	return a.x*b.x + a.y*b.y + a.z*b.z ;
}


MathVector MathVector::rotated(MathVector in)
{
	MathVector u = in; u.normalize();
	double phi = in.size() * math.pi()/180; 
	MathVector va = math.dot(*this, u) * u;
	MathVector vb = *this - va;
	MathVector vc = u.cross(vb);
	return va + vb * cos(phi) + vc * sin(phi);
}



MathVector MathVector::addRotation(MathVector in)
{
	Quat a =  math.rot2Quat(*this) * math.rot2Quat(in);
	return  a.rotation();
}

MathVector MathVector::vect2Rot()
{
	MathVector in = *this;
	double pi = 3.141592;
	double az, el;
	az = atan2(-in.z, in.x);
	el = asin(in.y/ in.size());
	MathVector rot1 = 180/pi * az * MathVector(0,1,0);
	MathVector rot2 = 180/pi * el * MathVector(0,0,1);
	Quat quat1 = math.rot2Quat(rot1); 
	Quat quat2 = math.rot2Quat(rot2);
	Quat quat3 = quat2 * quat1;
	return quat3.rotation(); 
}

MathVector MathVector::rot2Vect(MathVector direction)
{
	MathVector inv = *this;
	double invs = inv.size();
	MathVector uv;
	MathVector a;
	MathVector b;
	MathVector c;
	uv = inv;
	uv.normalize();
	a = math.dot(direction, uv) * uv;
	b = direction - a;
	c = math.cross(uv, b);
	return a +  cos(invs * math.pi()/180) * b +  sin(invs * math.pi()/180) * c;
}

RotationMatrix MathVector::euler2matrix()
{
	RotationMatrix xMatrix, yMatrix, zMatrix;
		
		double c = cos(x);
		double s = sin(x);
		
		xMatrix.x[0] = 1;
		xMatrix.x[1] = 0;
		xMatrix.x[2] = 0;				

		xMatrix.y[0] = 0;
		xMatrix.y[1] = c;
		xMatrix.y[2] = -s;
	
		xMatrix.z[0] = 0;
		xMatrix.z[1] = s;
		xMatrix.z[2] = c;		
		
		c = cos(y);
		s = sin(y);
		
		yMatrix.x[0] = c;
		yMatrix.x[1] = 0;
		yMatrix.x[2] = s;				
        
		yMatrix.y[0] = 0;
		yMatrix.y[1] = 1;
		yMatrix.y[2] = 0;
	    
		yMatrix.z[0] = -s;
		yMatrix.z[1] = 0;
		yMatrix.z[2] = c;		
  
		c = cos(z);
		s = sin(z);
		
		zMatrix.x[0] = c;
		zMatrix.x[1] = -s;
		zMatrix.x[2] = 0;				
        
		zMatrix.y[0] = s;
		zMatrix.y[1] = c;
		zMatrix.y[2] = 0;
	    
		zMatrix.z[0] = 0;
		zMatrix.z[1] = 0;
		zMatrix.z[2] = 1;				
	return zMatrix * yMatrix * xMatrix;
}

double MathVector::size()
{
	MathVector a = *this;
	return sqrt(a.x*a.x + a.y*a.y + a.z*a.z);
}

