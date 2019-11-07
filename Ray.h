#ifndef RAYH
#define RAYH

#include "Vec3.h"

struct Ray {
  Vec3 origin, direction;
  Vec3 point_at_parameter(float t) const { return origin + direction*t; }
  Ray(const Vec3& o, const Vec3& d) : origin(o), direction(d.normalize()) {}
};

#endif