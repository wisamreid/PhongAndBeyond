#include "camera.h"
#include <algorithm>

using namespace stl;

Camera::Camera(): direction(0.0, 0.0, 1.0) { /* Intentionally Empty */ }
Camera::Camera(Vector _direction): direction(_direction.getX(), _direction.getY(), _direction.getZ()){ /* Intentionally Empty */ }
const double Camera::getDirectionAt(Vector point_) const { return this->direction; }
Vector Camera::setDirectionAt(Vector _direction) { 
    this->direction(_direction.getX(), _direction.getY(), _direction.getZ());
}
//void Camera::stream_to(std::ostream& os) const {os<<"Direction:"<< direction;} //fix it Eddie
