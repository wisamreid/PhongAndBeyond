#ifndef LIGHT_H
#define LIGHT_H

#include "vector.h"
#include "color.h"

// stl :: string theory labs (taking over a universe near you) 
namespace stl
{

class Light {
 private:
  Color i;
 public:
  Light();
  Light(Color i);
  const Color getIntensity() const;
  virtual const Vector getDirectionAt(Vector point) const = 0;
  virtual void moveLight(Vector v) = 0;
  virtual void stream_to(std::ostream& os) const = 0;
};

class PointLight: public Light {
 private:
  Vector pos;
 public:
  PointLight(Vector pos);
  PointLight(Vector pos, Color i);
  void setPosition(Vector pos);
  void moveLight(Vector v);
  const Vector getDirectionAt(Vector point) const;
  void stream_to(std::ostream& os) const;
};

class DirectionLight: public Light {
 private:
  Vector dir;
 public:
  DirectionLight(Vector dir);
  DirectionLight(Vector dir, Color i);
  void setDirection(Vector dir);
  void moveLight(Vector v);
  const Vector getDirectionAt(Vector point) const;
  void stream_to(std::ostream& os) const;
};

static inline std::ostream& operator << (std::ostream& os, const Light& l) {l.stream_to(os); return os;}

}

#endif
