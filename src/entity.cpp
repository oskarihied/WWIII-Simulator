#include "entity.hpp"

Entity::Entity() : pos_(Pos()) {}

Entity::Entity(float x, float y) : pos_(Pos(x, y)) {}

Entity::Entity(float x, float y, std::string image)
    : image_(image), pos_(Pos(x, y)) {
  if (image_ != "") {
    texture_.loadFromFile(image_);
    sprite_.setTexture(texture_);
    sprite_.setOrigin(texture_.getSize().x / 2, texture_.getSize().y / 2);
    // std::cout << &sprite_ << std::endl;
  }
}

Entity::Entity(float x, float y, float xVel, float yVel, std::string image)
    : image_(image), pos_(Pos(x, y)), vel_(Pos(xVel, yVel)) {
  if (image_ != "") {
    texture_.loadFromFile(image_);
    sprite_.setTexture(texture_);
    sprite_.setOrigin(texture_.getSize().x / 2, texture_.getSize().y / 2);
    // std::cout << &sprite_ << std::endl;
  }
}

Pos Entity::GetPos() { return pos_; }

Pos Entity::GetVel() { return vel_; }

void Entity::UpdateVel(float xVel, float yVel) { vel_ = Pos(xVel, yVel); }

std::string Entity::GetImage() { return image_; }

void Entity::MoveTo(float x, float y) { pos_.Change(x, y); }

void Entity::MoveTo(Pos pos) { pos_.Change(pos); }

std::pair<float, float> Entity::Move(float x, float y) {
  return pos_.Add(x, y);
}

std::pair<float, float> Entity::Move(Pos pos) { return pos_.Add(pos); }

sf::Sprite* Entity::GetSprite() {
  sprite_.setTexture(texture_);
  return (&sprite_);
}

void Entity::RotationTo(float x) { rotation_ = x; }

float Entity::GetRotation() { return rotation_; }