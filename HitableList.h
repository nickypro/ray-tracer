#ifndef HITABLELIST
#define HITABLELIST
  
#include "Hitable.h"
  
class HitableList: public Hitable {
  public:
    HitableList() {}
    HitableList(Hitable **li, int n) {
      list = li; 
      list_length = n;
    }
    int list_length;
    Hitable **list;
    virtual bool hit(const Ray& r, float tmin, float tmax, hit_record& rec) const;
};
  
bool HitableList::hit(const Ray& ray, float tmin, float tmax, hit_record& rec) const {

  //printf("Hit?");

  hit_record temp_rec;
  bool was_anything_hit = false;
  double closest_so_far = tmax;
  
  for (int i = 0; i < list_length; ++i) {

    if ( list[i]->hit(ray, tmin, tmax, temp_rec) ){
      //printf("hit sphere %d with t = %lf. \n", i,temp_rec.t);
      was_anything_hit = true;
      closest_so_far = temp_rec.t;
      rec = temp_rec;
    }
  
  }
  
  return was_anything_hit;
};
  
#endif