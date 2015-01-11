#include "light.h"
#include "vector.h"

using namespace stl;

#include "viewport.h"
extern Viewport viewport; //This is a hack used to complete assignment specs
extern double sphereRadius; //This is a hack used to complete assignment specs

//Light class
Light::Light(): i(0.0) {}
Light::Light(Color i_): i(i_) {}
const Color Light::getIntensity() const {return i;}

//PointLight class
PointLight::PointLight(Vector pos_, Color i_): Light(i_), pos(pos_) {}
PointLight::PointLight(Vector pos_): Light(), pos(pos_) {}
void PointLight::setPosition(Vector pos_) {pos=pos_;}
void PointLight::moveLight(Vector v) {setPosition(v);}
const Vector PointLight::getDirectionAt(Vector pointInWorldFrame) const {
  Vector dir = pointInWorldFrame-pos*sphereRadius-Vector(viewport.getW()/2.0,viewport.getH()/2.0,0); //This is a hack used to complete assignment specs
  return (dir)/dir.magnitude();
}
void PointLight::stream_to(std::ostream& os) const {os<<"pLight("<<pos<<": "<<getIntensity()<<")";}

//DirectionLight class
DirectionLight::DirectionLight(Vector dir_, Color i_): Light(i_), dir(dir_) {}
DirectionLight::DirectionLight(Vector dir_): Light(), dir(dir_) {}
void DirectionLight::setDirection(Vector dir_) {dir=dir_;}
void DirectionLight::moveLight(Vector v) {setDirection(-v);}
const Vector DirectionLight::getDirectionAt(Vector point) const {return dir/dir.magnitude();}
void DirectionLight::stream_to(std::ostream& os) const {os<<"dLight("<<dir<<": "<<getIntensity()<<")";}

//SpotLight class
//TODO: Create SpotLight class! (Mix of directional and point, with a direction vector that loses magnitude when deviating from direction)
