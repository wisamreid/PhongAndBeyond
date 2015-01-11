/*
Authors:
Wisam Reid cs184-ds
Eddie Groshev cs184-en
*/

#ifndef SHAPE_H
#define SHAPE_H


#include "vector.h"
#include "color.h"
#include "viewport.h"
#include "light.h"
#include "camera.h"

// stl :: String Theory Labs (Taking over a universe near you) 
namespace stl
{

class Shape {
 public:
  virtual void draw() = 0; // Draw's the shape in the viewport
  virtual void resize() = 0; // Resizes the shape and keeps in centered in the view port

  virtual void setOutline(bool outline) = 0;
  virtual void setQuantize(int amount) = 0;
  virtual void setPerlinTexture(bool perlinTexture, double zoom, double amplitude, int octaves) = 0;
  
  virtual void setAmbientCoef(Color ka_) = 0;
  virtual void setDiffuseCoef(Color ka_) = 0;
  virtual void setSpecularCoef(Color ka_) = 0;
  virtual void setSpecularPow(double sp_) = 0;
  virtual void setAnisotropicCoef(double nu, double nv) = 0;
};

}

#endif
