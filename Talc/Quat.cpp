#include "Quat.h"
#include "Math.h"

using namespace std;

Quat::Quat()
{}

Quat::Quat(double ns, MathVector nv) 
{
	v = nv;
	scale = ns;
}

MathVector Quat::axes()
{
	return v.normalized();
}

double Quat::angle()
{
	return 2*acos(scale);
}

MathVector Quat::rotation()
{
    return 180/math.pi() *  angle()  * axes();
}
