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
  void ChangeHealth(float amount);

  void ChangeTexture(sf::Texture& texture);

  bool CanBeDamaged();

  std::optional<sf::Texture> GetDamagedTexture();

  sf::Sprite* GetSprite();

  void SetType(enum EntityType type);
  enum EntityType GetType();

  int GetPoints();

  void Die();

  bool Explodes();
  bool IsDead();

 protected:
  enum EntityType type_ = EntityType::UNDEFINED;

  std::map<std::string, sf::Texture> textures_;

  sf::Texture texture_;

  std::optional<sf::Texture> damagedTexture_ = std::nullopt;

  sf::Sprite sprite_;

  Vector pos_;
  Vector vel_;

  float rotation_ = 0.0f;
  float health_ = 1000;
  float maxHealth_ = 1000;

  int points_ = 0;

  bool damaged_ = false;
  bool dead_ = false;
  bool explodes_ = false;
};

#endif