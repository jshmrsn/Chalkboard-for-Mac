#include "Math.h"


using namespace std;


Math math;

Math::Math()
{
	srandom(time(NULL));
}

double Math::pi()
{
	return 3.141592653589793238462;
}

MathVector Math::cross(MathVector a, MathVector b)
{
	return a.cross(b);
}

double Math::dot(MathVector a, MathVector b)
{
	return a.x*b.x + a.y*b.y + a.z*b.z ;
}

MathVector Math::normal(MathVector a, MathVector b, MathVector c)
{
MathVector r1;
MathVector r2;
MathVector output;
	r2=c-b;
	r1=b-a;
	output = r1.cross(r2);
	output=(1.0f/output.size())*output;
	return output;
}

double Math::abs(double a)
{
	if(a<0)
	{
		return -a;
	}
	return a;
}

Quat Math::rot2Quat( MathVector in)
{
	MathVector inv = in;
	Quat nq;
	double invs;
	double phi;
	MathVector unitV;
	invs = inv.size();
		if(invs != 0)
		{
			unitV = 1/invs * inv ;
		}
		else
		{
			unitV = MathVector(1,0,0);
		}
	phi = invs * 3.14159265/180;
	nq.v = sin(phi/2) * unitV;
	nq.scale = cos(phi/2);
	return nq;
}

double Math::distance(MathVector a, MathVector b)
{
	MathVector delta = a - b;
	return delta.size();
}

bool Math::coplaner(MathVector a, MathVector b, MathVector c, MathVector point)
{
 	double t1 = math.dot(cross( b - a, point - a), cross(b - a, c - b));


	double t2 = math.dot(cross( c - b, point - b), cross(c - b ,a - c ));
	double t3 = math.dot(cross( a - c, point - c), cross(a - c, b - a));	
		if(t1 >= 0 && t2 >= 0 && t3 >= 0)
		{			
			return true;
		}
	return false;
}

bool Math::intersect(MathVector a, MathVector b, MathVector c, MathVector origin, MathVector direction)
{
	MathVector rp = a;
	MathVector un = math.normal(a, b, c); 
	double alpha = math.dot(rp-origin, un) / math.dot(direction, un);
	MathVector inter = origin + alpha * direction;
	
	return math.coplaner(a, b, c, inter);
}

bool Math::intersect(MathVector a, MathVector b, MathVector c, MathVector origin, MathVector direction, MathVector& inter)
{
	MathVector rp = a;
	MathVector un = math.normal(a, b, c); 
	double alpha = math.dot(rp-origin, un) / math.dot(direction, un);
	inter = origin + alpha * direction;
	
	return math.coplaner(a, b, c, inter);
}

double Math::ratio(double value, Range range)
{
      return (value - range.min) / (range.max - range.min);
}

double Math::ratio(double min, double value, double max)
{
	return ratio(value, Range(min, max));
}

bool Math::squareIntersect(double pointx, double pointy, double boxcentx, double boxcenty, double boxw, double boxh)
{
	if( math.abs(pointx-boxcentx)<0.5*boxw  && math.abs(pointy-boxcenty)<0.5*boxh )
		return true;
	return false;
}




double Math::clamp(double vmin, double current, double vmax)
{
	current = min(vmin, current);
	current = max(current, vmax);
	return current;
}

double Math::min(double vmin, double current)
{
	if(current < vmin)
		current = vmin;
	return current;
}

double Math::max(double vmax, double current)
{
	if(current > vmax)
		current = vmax;
	return current;
}

double Math::size(MathVector in)
{
	return in.size();
}

double Math::random()
{
	double randm = RAND_MAX;
	return rand()/randm;
}

double Math::random(double min, double max)
{
	return (max - min)* math.random() + min;	
}

double Math::random(Range range)
{
      return (range.max-range.min)*math.random() + range.min;
}

MathVector Math::random(MathVector min, MathVector max)
{
    return MathVector( math.random( min.x, max.x ),
				math.random( min.y, max.y ),
				math.random( min.z, max.z ) );         
}

MathVector Math::random(RangeVect rangeVect)
{
    return MathVector( math.random( rangeVect.min.x, rangeVect.max.x ),
				math.random( rangeVect.min.y, rangeVect.max.y ),
				math.random( rangeVect.min.z, rangeVect.max.z ) );         
}










