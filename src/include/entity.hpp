#ifndef ENTITY_HPP
#define ENTITY_HPP

#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include <vector>

#include "pos.hpp"

class Entity {
 public:

  enum class EntityType {
    UNDEFINED,
    BOX,
    GROUND,
    BULLET,
    ENEMY
  };

  Entity();
  Entity(float x, float y);
  Entity(float x, float y, std::string sprite);
  Entity(float x, float y, sf::Texture& texture);
  Entity(float x, float y, float xVel, float yVel, sf::Texture& texture);
  Entity(float x, float y, float xVel, float yVel, std::string sprite);

  Pos GetPos();
  Pos GetVel();

  void UpdateVel(float xVel, float yVel);

  void MoveTo(float x, float y);
  void MoveTo(Pos pos);

  void RotationTo(float x);

  float GetRotation();

  float GetHealth();
  void SetHealth(float health); 
  float ChangeHealth(float amount);

  void ChangeTexture(sf::Texture& texture);

  std::string GetImage();

  sf::Sprite* GetSprite();

  std::pair<float, float> Move(float x, float y);
  std::pair<float, float> Move(Pos pos);

  void SetType(enum EntityType type);
  enum EntityType GetType();

  bool Explodes();

 protected:
  std::string image_ = "";
  Pos pos_;
  Pos vel_;
  float rotation_ = 0.0f;
  sf::Texture texture_;
  sf::Sprite sprite_;
  enum EntityType type_ = EntityType::UNDEFINED;
  float health_ = 1000;
  float maxHealth = 1000;
  float mass = 10;

  bool explode_ = false;
};

#endif