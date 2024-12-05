#include <iostream>

#include "vector.hpp"

class Camera {
 public:
  Camera(float x, float y);
  Camera(Vector pos);

  Vector GetPos();
  float GetZoom();

  void MoveTo(float x, float y);

  void ShiftBy(float x, float y);

  float Zoom(float add);
  void ZoomTo(float zoom);

  float GetTimer();
  void AddTimer(float time);
  void ResetTimer();

  bool GetAnimation();

  void AnimationStep(float time);
  void NewAnimation(Vector goal, float zoom, float time);

 private:
  Vector pos_;
  float zoom_ = 10;

  bool animation_ = false;
  float timer_ = 0;
  float goalTime_ = 0;

  Vector start_;
  Vector goal_;

  float startZoom_ = 1;
  float goalZoom_ = 1;
};