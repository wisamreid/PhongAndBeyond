#ifndef CAMERA_H
#define CAMERA_H

#include <iostream>
#include "vector.h"

// stl :: string theory labs (taking over a universe near you) 
namespace stl
{

class Camera {
  private:
    Vector direction;

  public:
    // constructors
    Camera();
    Camera(Vector _direction);

    // gets/sets
    void setDirectionAt(Vector _direction);
    Vector getDirectionAt(Vector point_) const;

    void stream_to(std::ostream& os) const; // Eddie?
};

//static inline std::ostream& operator << (std::ostream& os, const Camera& c) {c.stream_to(os); return os;}

}

#endif
