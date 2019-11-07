#include <fstream>
#include <cmath>

#include "Vec3.h"
#include "Sphere.h"
#include "HitableList.h"

Vec3 random_vector() {
  Vec3 p;
  p = Vec3(drand48(), drand48(), drand48())*2.0 - Vec3(1,1,1);
  p = p.normalize()*drand48();
  return p;
}

Vec3 linearBlend(const Ray& r) {
  float t = 0.5*(r.direction.y + 1.0);
  Vec3 color = Vec3(1.0, 1.0, 1.0)*(1.0-t) + Vec3(0.5, 0.7, 1.0)*t;
  return color;
}

Vec3 colorPixel(const Ray& r, Hitable *world) {
  hit_record rec;
  if (world->hit(r, 0.0, MAXFLOAT, rec)) {
    const Vec3 P = rec.p;
    const Vec3 N = rec.normal;
    const Vec3 target = P + N + random_vector();
    const Vec3 val = colorPixel( Ray(P, target-P), world )*0.6;
    return val*0.5 + rec.color*sqrt(dot(val, val));
  } else {

    return linearBlend(r);

  }
} 

void clamp255(Vec3& col) {
  col.x = sqrt(col.x)*255.59;
  col.y = sqrt(col.y)*255.99;
  col.z = sqrt(col.z)*255.99;

  col.x = (col.x > 255) ? 255 : (col.x < 0) ? 0 : col.x;
  col.y = (col.y > 255) ? 255 : (col.y < 0) ? 0 : col.y;
  col.z = (col.z > 255) ? 255 : (col.z < 0) ? 0 : col.z;
}

int main() {

  const int H = 2000;
  const int W = 2000;
  const int D = 1200;

  const int R = 150;

  const Vec3 white(255, 255, 255);
  const Vec3 black(0, 0, 0);
  const Vec3 red(255, 0, 0);
  const Vec3 green(0, 255, 0);
  const Vec3 blue(0, 0, 255);

  const Vec3 top_left_corner(-W/2, -H/2, D);
  const Vec3 horizontal(W, 0, 0);
  const Vec3 vertical(0, H, 0);
  const Vec3 origin(0, 0, 0);

  Hitable *list[5];

  
  //surface
  list[0] = new Sphere(top_left_corner + Vec3(W*0.5, H*0.5+D*10000.5  , D ), D*10000, Vec3(0.00, 0.05, 0.05));
  
  list[1] = new Sphere(top_left_corner + Vec3(W*0.5, H*0.5      , D     ), D*0.5, Vec3(0.9, 0.7, 0.1));
  list[2] = new Sphere(top_left_corner + Vec3(W*0.1, H*0.5-D*0.2, D*0.5 ), D*0.7, Vec3(0.9, 0.4, 0.0));
  list[3] = new Sphere(top_left_corner + Vec3(W*0.7, H*0.5+D*0.3, D*0.5 ), D*0.2, Vec3(0.3, 0.4, 0.1));
  list[4] = new Sphere(top_left_corner + Vec3(W*1.2, H*0.5+D*0.1, D*1.1 ), D*0.4, Vec3(0.2, 0.7, 0.9));

  Hitable *world = new HitableList(list, 5);

  std::ofstream out("out.ppm");
  out << "P3\n" << W << ' ' << H << ' ' << "255\n";

  double t;
  Vec3 pix_col(black);

  for (int y = 0; y < H; ++y) {
    for (int x = 0; x < W; ++x) {
      const float u = (float) x/W;
      const float v = (float) y/H;

      const Vec3 direction = (top_left_corner - origin) + (horizontal*u) + (vertical*v) ;
      const Ray ray(origin, direction);

      Vec3 pix_col = colorPixel(ray, world);
      
      clamp255(pix_col);

      out << (int)pix_col.x << ' '  
          << (int)pix_col.y << ' '
          << (int)pix_col.z << '\n';
    }
  }
}