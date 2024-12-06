#include "entity.hpp"

Entity::Entity(float x, float y, sf::Texture& texture) : texture_(texture) {
  pos_ = Vector(x, y);
  sprite_.setTexture(texture_);
  sprite_.setOrigin(texture_.getSize().x / 2, texture_.getSize().y / 2);
}

bool Entity::CanBeDamaged() {
  if (damagedTexture_)
    return true;
  else
    return false;
}

std::optional<sf::Texture> Entity::GetDamagedTexture() {
  return damagedTexture_;
}

Vector& Entity::GetPos() { return pos_; }

Vector& Entity::GetVel() { return vel_; }

void Entity::UpdateVel(float xVel, float yVel) { vel_ = Vector(xVel, yVel); }

void Entity::ChangeTexture(sf::Texture& texture) {
  texture_ = texture;
  sprite_.setTexture(texture_);
}

void Entity::ChangeToDamaged() {
  if (CanBeDamaged() && !damaged_) {
    ChangeTexture(damagedTexture_.value());
    damaged_ = true;
  }
}

void Entity::MoveTo(float x, float y) { pos_.Update(x, y); }

sf::Sprite* Entity::GetSprite() {
  sprite_.setTexture(texture_);
  return (&sprite_);
}

void Entity::RotationTo(float x) { rotation_ = x; }

float Entity::GetRotation() { return rotation_; }

void Entity::SetType(enum EntityType type) { type_ = type; }

enum Entity::EntityType Entity::GetType() { return type_; }

void Entity::ChangeHealth(float amount) {
  if (type_ != EntityType::UNDEFINED && type_ != EntityType::GROUND) {
    float futureHealth = health_ + amount;
    if (futureHealth < 0) {
      health_ = 0;
    } else if (futureHealth > maxHealth_) {
      health_ = maxHealth_;
    } else {
      health_ = futureHealth;
    }
  }
}

float Entity::GetHealth() { return health_; }

float Entity::GetMaxHealth() { return maxHealth_; }

void Entity::SetHealth(float health) {
  if (health > maxHealth_) {
    health_ = maxHealth_;
  } else if (health < 0) {
    health_ = 0;
  } else {
    health_ = health;
  }
}

bool Entity::Explodes() { return explodes_; }

int Entity::GetPoints() { return points_; }

void Entity::Die() { dead_ = true; }

bool Entity::IsDead() { return dead_; }