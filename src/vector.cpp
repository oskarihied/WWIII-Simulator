#include "vector.hpp"

#include <math.h>

Vector::Vector() : x_(0), y_(0) {}

Vector::Vector(float x, float y) : x_(x), y_(y) {}

Vector::Vector(Vector& v) {
  x_ = v.GetX();
  y_ = v.GetY();
}

float Vector::GetX() { return x_; }

float Vector::GetY() { return y_; }

void Vector::Update(float x, float y) {
  x_ = x;
  y_ = y;
}

void Vector::IncrementBy(float x, float y) {
  x_ += x;
  y_ += y;
}

float Vector::Distance(Vector& v) {
  return (pow(v.GetX() - x_, 2) + pow(v.GetY() - y_, 2));
}