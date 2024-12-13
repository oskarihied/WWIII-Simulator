#ifndef VECTOR_HPP
#define VECTOR_HPP

#include <utility>

//represents a position in 2d world
class Vector {
 public:
  Vector();
  Vector(float x, float y);
  Vector(Vector& v);

  //return x and y coordinates
  float GetX();
  float GetY();

  //params: new position
  void Update(float x, float y);
  //params: addition to position
  void IncrementBy(float x, float y);
  
  //distance between this position and an other
  //params: the other position
  float Distance(Vector& v);

 private:
  //x and y coordinates
  float x_;
  float y_;
};

#endif