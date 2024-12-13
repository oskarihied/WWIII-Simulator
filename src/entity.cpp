#include "entity.hpp"

#include "fileManager.hpp"

Entity::Entity(float x, float y) { pos_ = Vector(x, y); }

Vector& Entity::GetPos() { return pos_; }

Vector& Entity::GetVel() { return vel_; }

void Entity::UpdateVel(float xVel, float yVel) { vel_ = Vector(xVel, yVel); }

void Entity::MoveTo(float x, float y) { pos_.Update(x, y); }

void Entity::RotationTo(float x) { rotation_ = x; }

const float& Entity::GetRotation() { return rotation_; }

const float& Entity::GetHealth() { return health_; }

const float& Entity::GetMaxHealth() { return maxHealth_; }

int Entity::GetPoints() { return points_; }

const float& Entity::GetWidth() { return width_; };

const float& Entity::GetHeight() { return height_; };

void Entity::BecomeDamaged() {}

void Entity::SetHealth(float health) {
  //set health to max maxhealth
  if (health > maxHealth_) {
    health_ = maxHealth_;
  } else if (health < 0) {
    health_ = 0;
  } else {
    health_ = health;
  }
}

void Entity::ChangeHealth(float amount) {
  if (type_ != EntityType::UNDEFINED && type_ != EntityType::GROUND) {
    float futureHealth = health_ + amount;
    //checks if the entity should be dead
    if (futureHealth < 0) {
      health_ = 0;
    } else if (futureHealth > maxHealth_) {
      health_ = maxHealth_;
    } else {
      health_ = futureHealth;
    }
  }
}

void Entity::SetTexture(const std::string name) {
  std::unique_ptr<sf::Texture>& t = FileManager::GetTexture(name);
  sprite_.setTexture(*t);
  sprite_.setOrigin((*t).getSize().x / 2, (*t).getSize().y / 2);
}

sf::Sprite& Entity::GetSprite() { return sprite_; }

sf::Sprite Entity::CopySprite() { return sprite_; }

void Entity::SetType(enum EntityType type) { type_ = type; }

enum Entity::EntityType Entity::GetType() { return type_; }

void Entity::Die() { dead_ = true; }

bool Entity::IsDead() { return dead_; }

bool Entity::Explodes() { return explodes_; }

void Entity::SetExplodes(bool explodes) {explodes_ = explodes;}

void Entity::SetSound(std::string str) { sound_ = str; }

std::string Entity::GetSound() {return sound_;}

bool Entity::GetSide() {return side_;}
void Entity::SetSide(bool side) {side_ = side;}