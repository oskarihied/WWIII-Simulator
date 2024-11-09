
#include "pos.hpp"

Pos::Pos(float x, float y) : x_(x), y_(y) {}

float Pos::GetX() { return x_; }
float Pos::GetY() { return y_; }

std::pair<float, float> Pos::GetXY() { return std::pair(x_, y_); }

std::pair<float, float> Pos::Add(Pos other) {
  x_ += other.GetX();
  y_ += other.GetY();
  return (this->GetXY());
}

std::pair<float, float> Pos::Add(float x, float y) {
  x_ += x;
  y_ += y;
  return (this->GetXY());
}

void Pos::Change(Pos other) {
  x_ = other.GetX();
  y_ = other.GetY();
}

void Pos::Change(float x, float y) {
  x_ = x;
  y_ = y;
}