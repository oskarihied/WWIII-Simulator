#ifndef VECTOR_HPP
#define VECTOR_HPP

#include <utility>

class Vector {
 public:
  Vector();
  Vector(float x, float y);
  Vector(Vector& v);

  float GetX();
  float GetY();

  void Update(float x, float y);

  void IncrementBy(float x, float y);

  float Distance(Vector& v);

 private:
  float x_;
  float y_;
};

#endif