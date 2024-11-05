#include "camera.hpp"

Camera::Camera(float x, float y) : pos_(Pos(x, y)) {}
Camera::Camera(Pos pos) : pos_(pos) {}

Pos Camera::GetPos() {
    return pos_;
}

float Camera::GetZoom() {
    return zoom_;
}