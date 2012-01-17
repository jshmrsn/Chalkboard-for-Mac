#ifndef _MathVector_h_included_
#define _MathVector_h_included_

#include <cstdlib>
#include <iostream>

using namespace std;

class RotationMatrix;

class MathVector {
	public:
		// Initialize
		MathVector();
		MathVector(double);
		MathVector(double, double);	
		MathVector(double, double, double);		
		// Variables
		double x;
		double y;
		double z;
		void normalize();
		MathVector normalized();		
		MathVector rotated(MathVector in); //return rotated vector
		MathVector addRotation(MathVector in);
		
		MathVector cross(MathVector b);
		double dot(MathVector b);
		double size();
		
		MathVector rot2Vect(MathVector direction);
		MathVector vect2Rot();
		RotationMatrix euler2matrix();
		
		// Operators
		MathVector &operator+=(const MathVector& b) {
			x += b.x;
			y += b.y;
			z += b.z;
			return *this;
		}
		MathVector &operator+=(const double b) {
			x += b;
			y += b;
			z += b;
			return *this;
		}
		MathVector &operator*=(const double b) {
			x *= b;
			y *= b;
			z *= b;
			return *this;
		}
		MathVector &operator*=(const MathVector& b) {
			x *= b.x;
			y *= b.y;
			z *= b.z;
			return *this;
		}
		
		MathVector &operator/=(const double b) {
			x /= b;
			y /= b;
			z /= b;
			return *this;
		}
		MathVector &operator/=(const MathVector& b) {
			x /= b.x;
			y /= b.y;
			z /= b.z;
			return *this;
		}		
		
		MathVector &operator-=(const MathVector& b) {
			x -= b.x;
			y -= b.y;
			z -= b.z;
			return *this;
		}
		MathVector &operator-=(const double b) {
			x -= b;
			y -= b;
			z -= b;
			return *this;
		}
		MathVector &operator=(double b) {
			x = b;
			y = b;
			z = b;
			return *this;
		}
		friend MathVector operator+(const MathVector& left, const MathVector& right) {
			MathVector result;
			result.x = left.x + right.x;
			result.y = left.y + right.y;
			result.z = left.z + right.z;
			return result;
		}
		
		bool operator==(const MathVector& b) {
			return x == b.x && y == b.y && z == b.z;
		}

		bool operator!=(const MathVector& b) {
			return x != b.x || y != b.y || z != b.z;
		}

		friend MathVector operator-(const MathVector& left, const MathVector& right) {
			MathVector result;
			result.x = left.x - right.x;
			result.y = left.y - right.y;
			result.z = left.z - right.z;
			return result;
		}

		friend MathVector operator*(const MathVector& left, const MathVector& right) {
			MathVector result;
			result.x = left.x * right.x;
			result.y = left.y * right.y;
			result.z = left.z * right.z;
			return result;
		}
		
		friend MathVector operator*(const double& left, const MathVector& right) {
			MathVector result;
			result.x = left * right.x;
			result.y = left * right.y;
			result.z = left * right.z;
			return result;
		}
		
		friend MathVector operator*( const MathVector& right, const double& left) {
			MathVector result;
			result.x = left * right.x;
			result.y = left * right.y;
			result.z = left * right.z;
			return result;
		}
		
		friend MathVector operator/(const MathVector& left, const MathVector& right) {
			MathVector result;
			result.x = left.x / right.x;
			result.y = left.y / right.y;
			result.z = left.z / right.z;
			return result;
		}		
};


#endif


