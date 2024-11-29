#include "camera.hpp"

Camera::Camera(float x, float y) : pos_(Pos(x, y)) {}
Camera::Camera(Pos pos) : pos_(pos) {}

Pos Camera::GetPos() {
    return pos_;
}

float Camera::GetZoom() {
    return zoom_;
}

float Camera::Zoom(float add) {
    zoom_ *= add;
/*
    float ratio = zoom_/50.0f;

    if (add > 1) {
        Move(-ratio, ratio);
    }
    else if (add < 1) {
        Move(ratio, -ratio);
    }
    */
    
    return zoom_;
}

void Camera::ZoomTo(float zoom) {
    zoom_ = zoom;
}

std::pair<int, int> Camera::Move(float x, float y) {
    return pos_.Add(x, y);
}

void Camera::MoveTo(float x, float y) {
    pos_.Change(Pos(x, y));
}

float Camera::GetTimer() {
    return timer_;
}

void Camera::AddTimer(float time) {
    timer_ += time;
}

void Camera::ResetTimer() {
    timer_ = 0;
}

bool Camera::GetAnimation() {
    return animation_;
}

void Camera::AnimationStep(float time) {

    if (animation_) {


        std::cout << "(" << pos_.GetX() << " " << pos_.GetY() << ") " << zoom_ << std::endl;

        if (timer_ < goalTime_) {
            
            MoveTo((start_.GetX() * (1 - (timer_ / goalTime_))) + (goal_.GetX() * (timer_ / goalTime_)), (start_.GetY() * (1 - (timer_ / goalTime_))) + (goal_.GetY() * (timer_ / goalTime_)));
            ZoomTo((startZoom_ * (1 - (timer_ / goalTime_))) + (goalZoom_ * (timer_ / goalTime_)));
            AddTimer(time);
        }

        else {
            MoveTo(goal_.GetX(), goal_.GetY());
            ZoomTo(goalZoom_);
            animation_ = false;
        }
    }
    
}

void Camera::NewAnimation(Pos goal, float zoom, float time) {
    ResetTimer();
    animation_ = true;

    start_ = pos_;
    goal_ = goal;

    startZoom_ = zoom_;
    goalZoom_ = zoom;

    goalTime_ = time;
}