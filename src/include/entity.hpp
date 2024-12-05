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
  enum class EntityType { UNDEFINED, BOX, GROUND, BULLET, ENEMY };

  Entity(float x, float y, sf::Texture& texture);

  Vector& GetPos();
  Vector& GetVel();

  void UpdateVel(float xVel, float yVel);

  void MoveTo(float x, float y);

  void RotationTo(float x);

  float GetRotation();

  float GetHealth();
  float GetMaxHealth();

  void ChangeToDamaged();

  void SetHealth(float health);
  float ChangeHealth(float amount);

  void ChangeTexture(sf::Texture& texture);

  bool CanBeDamaged();

  std::optional<sf::Texture> GetDamagedTexture();

  sf::Sprite* GetSprite();

  void SetType(enum EntityType type);
  enum EntityType GetType();

  bool Explodes();

  int GetPoints();

  void Die();
  bool IsDead();

 protected:
  Vector pos_;
  Vector vel_;
  float rotation_ = 0.0f;
  sf::Texture texture_;
  std::optional<sf::Texture> damaged_ = std::nullopt;
  sf::Sprite sprite_;
  enum EntityType type_ = EntityType::UNDEFINED;
  float health_ = 1000;
  float maxHealth = 1000;
  float mass = 10;

  bool damagedTexture_ = false;

  bool explode_ = false;

  int points_ = 0;

  bool dead_ = false;
};

#endif