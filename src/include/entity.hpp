#ifndef ENTITY_HPP
#define ENTITY_HPP

#include <SFML/Graphics.hpp>
#include <iostream>
#include <optional>
#include <string>
#include <vector>

#include "vector.hpp"

class Entity {
 public:
  enum class EntityType {
    UNDEFINED,
    BOX,
    GROUND,
    BULLET,
    ENEMY,
    EXPLOSION,
    GUN
  };

  Entity(float x, float y);

  Vector& GetPos();
  Vector& GetVel();

  void UpdateVel(float xVel, float yVel);

  void MoveTo(float x, float y);

  void RotationTo(float x);

  const float& GetRotation();

  const float& GetHealth();
  const float& GetMaxHealth();

  virtual void BecomeDamaged();

  void SetHealth(float health);
  void ChangeHealth(float amount);

  void SetTexture(const std::string name);

  sf::Sprite& GetSprite();

  sf::Sprite CopySprite();

  void SetType(enum EntityType type);
  enum EntityType GetType();

  int GetPoints();

  const float& GetWidth();
  const float& GetHeight();

  void Die();

  bool Explodes();
  bool IsDead();

  void SetSound(std::string str);
  std::string GetSound();

 protected:
  enum EntityType type_ = EntityType::UNDEFINED;

  sf::Sprite sprite_;

  Vector pos_;
  Vector vel_ = Vector();

  float width_ = 1.0f;
  float height_ = 1.0f;
  float rotation_ = 0.0f;

  float health_ = 1000;
  float maxHealth_ = 1000;

  int points_ = 0;

  bool dead_ = false;
  bool explodes_ = false;

  std::string sound_ = "";
};

#endif