#ifndef POS_HPP
#define POS_HPP

#include <utility>

class Pos {
 public:
  Pos();
  Pos(float x, float y);

  float GetX();
  float GetY();
  std::pair<float, float> GetXY();

  std::pair<float, float> Add(Pos other);
  std::pair<float, float> Add(float x, float y);

  void Change(Pos other);
  void Change(float x, float y);

 private:
  float x_;
  float y_;
};

#endif