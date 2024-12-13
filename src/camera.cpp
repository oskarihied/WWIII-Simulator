#include "camera.hpp"

Camera::Camera(float x, float y) { pos_ = Vector(x, y); }

Camera::Camera(Vector pos) : pos_(pos) {}

Vector Camera::GetPos() { return pos_; }

float Camera::GetZoom() { return zoom_; }

void Camera::MoveTo(float x, float y) { pos_.Update(x, y); }

void Camera::ShiftBy(float x, float y) { pos_.IncrementBy(x, y); }

float Camera::Zoom(float add) {
  zoom_ *= add;
  return zoom_;
}

void Camera::ZoomTo(float zoom) { zoom_ = zoom; }

float Camera::GetTimer() { return timer_; }

void Camera::AddTimer(float time) { timer_ += time; }

void Camera::ResetTimer() { timer_ = 0; }

bool Camera::GetAnimation() { return animation_; }

void Camera::AnimationStep(float time) {
  if (animation_) {
    if (timer_ < goalTime_) {
      //calculates position and zoom based on timer
      MoveTo((start_.GetX() * (1 - (timer_ / goalTime_))) +
                 (goal_.GetX() * (timer_ / goalTime_)),
             (start_.GetY() * (1 - (timer_ / goalTime_))) +
                 (goal_.GetY() * (timer_ / goalTime_)));
      ZoomTo((startZoom_ * (1 - (timer_ / goalTime_))) +
             (goalZoom_ * (timer_ / goalTime_)));
      //add time to timer
      AddTimer(time);
    }

    //if animation if complete
    else {
      MoveTo(goal_.GetX(), goal_.GetY());
      ZoomTo(goalZoom_);
      animation_ = false;
    }
  }
}

void Camera::NewAnimation(Vector goal, float zoom, float time) {
  ResetTimer();
  animation_ = true;

  start_ = pos_;
  goal_ = goal;

  startZoom_ = zoom_;
  goalZoom_ = zoom;

  goalTime_ = time;
}