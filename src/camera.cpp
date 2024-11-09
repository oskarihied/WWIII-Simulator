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
    return zoom_;
}

std::pair<int, int> Camera::Move(float x, float y) {
    return pos_.Add(x, y);
}