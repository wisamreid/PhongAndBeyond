#ifndef COLOR_H
#define COLOR_H

#include <iostream>
#include "vector.h"

// stl :: string theory labs (taking over a universe near you) 
namespace stl
{

class Color {
 private:
  double r;
  double g;
  double b;

 public:
  Color();
  Color(double m);
  Color(double r, double g, double b);
  const double getR() const;
  const double getG() const;
  const double getB() const;

  Color operator + (const Color& c2) const;
  Color operator - (const Color& c2) const;
  Color operator * (const Color& c2) const;
  Color operator + (double m) const;
  Color operator * (double m) const;
  Color operator / (double m) const;

  Color& operator += (const Color& c2);

  Color descretized(double step);
  Color normalized() const;

  void stream_to(std::ostream& os) const;
};

static inline std::ostream& operator << (std::ostream& os, const Color& c) {c.stream_to(os); return os;}

}

#endif