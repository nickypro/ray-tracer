#ifndef HITABLEH
#define HITABLEH

#include "Vec3.h"
#include "Ray.h"

struct hit_record {
  float t;
  Vec3  p;
  Vec3  normal;
  Vec3 color;
  hit_record() {t=0; Vec3 p(0,0,0); Vec3 normal(0,0,0); Vec3 color(0.5, 0.5, 0.5);}
};

class Hitable {
  public:
    virtual bool hit(const Ray& ray, float tmin, float tmax, hit_record& rec) const = 0;
};

#endif