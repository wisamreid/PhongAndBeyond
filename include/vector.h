/* 
Authors: 
Wisam Reid cs184-ds
Eddie Groshev cs184-en
*/

#ifndef VECTOR_H
#define VECTOR_H

#include "vector.h"
#include <iostream>

// stl :: String Theory Labs (Taking over a universe near you) 
namespace stl
{

class Vector {
 private:
  double x;
  double y;
  double z;

 public:
  Vector();
  Vector(double x, double y, double z );
  Vector(double c);

  void setX(double x);
  void setY(double y);
  void setZ(double z);

  const double getX() const;
  const double getY() const;
  const double getZ() const;

  // bracket operator 
  double operator [] (size_t i) const;

  // create new vector: vector addition/subtraction 
  Vector operator + (const Vector& v2) const;
  Vector operator - (const Vector& v2) const;

  // create new vector: point-wise multiplication
  Vector operator * (const Vector& v2) const;

  // create new vector: operations with a constant
  Vector operator + (double c) const;
  Vector operator - (double c) const;
  Vector operator * (double c) const;
  Vector operator / (double c) const;


  // create new vector: unary negation
  Vector operator - () const;

  // override vector: vector addition/subtraction 
  Vector& operator += (const Vector& v2);
  Vector& operator -= (const Vector& v2);

  // override vector: operations with a constant
  Vector& operator += (double c);
  Vector& operator -= (double c);
  Vector& operator *= (double c);
  Vector& operator /= (double c);

  // cross and dot product
  double dot(const Vector& v2) const;
  Vector cross(const Vector& v2) const;
  double magnitude() const;

  // io stuff
  void stream_to(std::ostream& os) const;
};

static inline std::ostream& operator << (std::ostream& os, const Vector& v) {v.stream_to(os); return os;}

}

#endif
