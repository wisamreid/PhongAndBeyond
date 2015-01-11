/* 
Authors: 
Wisam Reid cs184-ds
Eddie Groshev cs184-en
*/

#include "vector.h"
#include <cmath>

// stl :: String Theory Labs (Taking over a universe near you)
using namespace stl;

// constructors 
Vector::Vector() : x(0.0), y(0.0), z(0.0) { /* Intentionally Empty */ }
Vector::Vector(double x_, double y_, double z_) : x(x_), y(y_), z(z_) { /* Intentionally Empty */ }
Vector::Vector(double c) : x(c), y(c), z(c) { /* Intentionally Empty */ }

// sets
void Vector::setX(double x){ this->x = x; }
void Vector::setY(double y){ this->y = y; }
void Vector::setZ(double z){ this->z = z; }

// gets
const double Vector::getX() const { return this->x; }
const double Vector::getY() const { return this->y; }
const double Vector::getZ() const { return this->z; }

// bracket operator 
double Vector::operator [] (size_t i) const { if (i==0) return x; else if (i==1) return y; else return z; }

// create new vector: vector addition/subtraction 
Vector Vector::operator + (const Vector& v2) const { return Vector(this->x + v2.x, this->y + v2.y, this->z + v2.z); }
Vector Vector::operator - (const Vector& v2) const { return Vector(this->x - v2.x, this->y - v2.y, this->z - v2.z); }

// create new vector: point-wise multiplication
Vector Vector::operator * (const Vector& v2) const { return Vector(this->x * v2.x, this->y * v2.y, this->z * v2.z); }

// create new vector: operations with a constant
Vector Vector::operator + (double c) const { return Vector(this->x + c, this->y + c, this->z + c); }
Vector Vector::operator - (double c) const { return Vector(this->x - c, this->y - c, this->z - c); }
Vector Vector::operator * (double c) const { return Vector(this->x * c, this->y * c, this->z * c); }
Vector Vector::operator / (double c) const { return Vector(this->x / c, this->y / c, this->z / c); }

// create new vector: unary negation
Vector Vector::operator - () const { return Vector(-this->x, -this->y, -this->z); }

// override vector: vector addition/subtraction 
Vector& Vector::operator += (const Vector& v2) { this->x += v2.x; this->y += v2.y; this->z += v2.z; return *this; }
Vector& Vector::operator -= (const Vector& v2) { this->x -= v2.x; this->y -= v2.y; this->z -= v2.z; return *this; }

// override vector: operations with a constant
Vector& Vector::operator += (double c) { this->x += c; this->y += c; this->z += c; return *this; }
Vector& Vector::operator -= (double c) { this->x -= c; this->y -= c; this->z -= c; return *this; }
Vector& Vector::operator *= (double c) { this->x *= c; this->y *= c; this->z *= c; return *this; }
Vector& Vector::operator /= (double c) { this->x /= c; this->y /= c; this->z /= c; return *this; }

// cross and dot product
double Vector::dot(const Vector& v2) const{return (this->x * v2.x) + (this->y * v2.y) + (this->z * v2.z); }
Vector Vector::cross(const Vector& v2) const { return Vector(this->y * v2.z - this->z * v2.y, this->z * v2.x - this->x * v2.z, this->x  * v2.y - this->y * v2.x); }
double Vector::magnitude() const { return std::sqrt( x*x + y*y + z*z ); }

// io stuff
void Vector::stream_to(std::ostream& os) const {os<<"<"<<x<<","<<y<<","<<z<<">";}
