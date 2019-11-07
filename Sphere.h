#ifndef SPHEREH
#define SPHEREH

#include "Hitable.h"

class Sphere: public Hitable {
  public:
    Vec3 center;
    double radius;
    Vec3 color;
    Sphere() {};
    Sphere(const Vec3& cen, double r, const Vec3& col) : center(cen), radius(r), color(col) {}
    Vec3 getNormal(const Vec3& poi) const { return (poi - center) / radius; }
    virtual bool hit(const Ray& ray, float tmin, float tmax, hit_record& rec) const;
};

bool Sphere::hit(const Ray& r, float t_min, float t_max, hit_record& rec) const {
    Vec3 oc = r.origin - center;
    float a = dot(r.direction, r.direction);
    float b = dot(oc, r.direction);
    float c = dot(oc, oc) - radius*radius;
    float discriminant = b*b - a*c;
    if (discriminant > 0) {
        float temp = (-b - sqrt(discriminant))/a;
        if (temp < t_max && temp > t_min) {
            rec.t = temp;
            rec.p = r.point_at_parameter(rec.t);
            rec.normal = (rec.p - center) / radius;
            rec.color = color;
            return true;
        }
        temp = (-b + sqrt(discriminant)) / a;
        if (temp < t_max && temp > t_min) {
            rec.t = temp;
            rec.p = r.point_at_parameter(rec.t);
            rec.normal = (rec.p - center) / radius;
            rec.color = color;
            return true;
        }
    }
    return false;
}

/*
bool Sphere::hit(const Ray& ray, float tmin, float tmax, hit_record& rec) const {
  const Vec3 o = ray.origin;
  const Vec3 d = ray.direction;
  const Vec3 oc = o - center;
  const double b = 2.0 * dot(oc, d);
  const double c = dot(oc, oc) - radius*radius;
  double discriminant = b*b - 4 * c;

  if (discriminant < 1e-4) return false;
      
  const double disc = sqrt(discriminant);

  const double t0 = -b - disc;
  const double t1 = -b + disc;
  const double tsmall = (t0<t1)?t0:t1;
  const double tlarge = (t0<t1)?t1:t0;

  if (tmin < tsmall && tsmall < tmax) {
    rec.t = tsmall;
    rec.p = ray.point_at_parameter(rec.t);
    rec.normal = getNormal(rec.p);
    rec.color = color;
    return true;
  }

  if (tmin < tlarge && tlarge < tmax) {
    rec.t = tlarge;
    rec.p = ray.point_at_parameter(rec.t);
    rec.normal = getNormal(rec.p);
    rec.color = color;
    return true;
  }

  return false;
};
/**/
#endif