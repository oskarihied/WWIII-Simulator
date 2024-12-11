#include "entity.hpp"

#include "fileManager.hpp"

Entity::Entity(float x, float y) { 
  pos_ = Vector(x, y); 
  }

Vector& Entity::GetPos() { return pos_; }

Vector& Entity::GetVel() { return vel_; }

void Entity::UpdateVel(float xVel, float yVel) { vel_ = Vector(xVel, yVel); }

void Entity::SetTexture(const std::string name) {
  std::unique_ptr<sf::Texture>& t = FileManager::GetTexture(name);
  sprite_.setTexture(*t);
  sprite_.setOrigin((*t).getSize().x / 2, (*t).getSize().y / 2);
}

void Entity::MoveTo(float x, float y) { pos_.Update(x, y); }

sf::Sprite& Entity::GetSprite() { return sprite_; }

sf::Sprite Entity::CopySprite() { return sprite_; }

void Entity::BecomeDamaged() {}

void Entity::RotationTo(float x) { rotation_ = x; }

const float& Entity::GetRotation() { return rotation_; }

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

const float& Entity::GetHealth() { return health_; }

const float& Entity::GetMaxHealth() { return maxHealth_; }

const float& Entity::GetWidth() { return width_; };

const float& Entity::GetHeight() { return height_; };

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

void Entity::SetSound(std::string str) { sound_ = str;}

std::string Entity::GetSound() {return sound_;}