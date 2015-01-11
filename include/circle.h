/*
Authors:
Wisam Reid cs184-ds
Eddie Groshev cs184-en
*/

#ifndef CIRCLE_H
#define CIRCLE_H

#include "shape.h"

// stl :: String Theory Labs (taking over a universe near you) 
namespace stl
{

class Circle : public Shape {
 private:
  double radius;
  Vector center;
  Color ka;
  Color kd;
  Color ks;
  double sp;
  double nu;
  double nv;
  
  bool outline;
  int quantize;
  bool anisotropic;

  bool perlin;
  double zoom;
  double decayRate;
  int octaves;

  Vector getNormal(Vector point) const;
  Color BRDF(Color _Intensity, Vector _lightDirection, Vector _viewer, Vector _normal);

 public:
  // constructors
  Circle();
  Circle(Vector c_, double r_);

  // gets
  Vector getCenter() const;

  // sets
  void setOutline(bool outline);
  void setQuantize(int amount);
  void setPerlinTexture(bool perlin, double zoom, double decayRate, int octaves);

  void setCenter(Vector c_);
  void setRadius(double r_);
  void setAmbientCoef(Color ka_);
  void setDiffuseCoef(Color ka_);
  void setSpecularCoef(Color ka_);
  void setSpecularPow(double sp_);
  void setAnisotropicCoef(double nu_, double nv_);

  // methods
  void draw(); // Draw's the shape in the viewport
  void resize(); // Resizes the shape and keeps in centered in the view port
  Color texturize(Vector point, double w, const Color& c); // Texturize the surface
  double random(double x, double y);
  Vector perlinTexture(int i, int j, Vector normal);
  Vector gaussianVector(double mean, double variance);


};

}

#endif
