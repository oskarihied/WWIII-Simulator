
#include "entity.hpp"

Entity::Entity() 
    : pos_(Pos(0, 0)) {}

Entity::Entity(float x, float y) 
    : pos_(Pos(x, y)) {}

Entity::Entity(float x, float y, std::string image) 
    : image_(image), pos_(Pos(x, y)) {

    texture_.loadFromFile(image_);
    sprite_.setTexture(texture_);
    sprite_.setOrigin(0, 0);
}

Pos Entity::GetPos() {
    return pos_;
}

void Entity::MoveTo(float x, float y) {
    pos_.Change(x, y);
}

void Entity::MoveTo(Pos pos) {
    pos_.Change(pos);
}

std::pair<float, float> Entity::Move(float x, float y) {
    return pos_.Add(x, y);
}

std::pair<float, float> Entity::Move(Pos pos) {
    return pos_.Add(pos);
}

sf::Sprite &Entity::GetSprite() {
    return (sprite_);
}