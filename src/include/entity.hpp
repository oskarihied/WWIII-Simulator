#ifndef ENTITY_HPP
#define ENTITY_HPP

#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include <vector>

#include "pos.hpp"

enum Type {
  CONCRETE,
  WOOD,
  GLASS,
  ENEMY
};

class Entity {
 public:
  Entity();
  Entity(float x, float y);
  Entity(float x, float y, std::string sprite);

  Pos GetPos();
  void MoveTo(float x, float y);
  void MoveTo(Pos pos);

  void RotationTo(float x);

  float GetRotation();

  std::string GetImage();

  sf::Sprite* GetSprite();

  std::pair<float, float> Move(float x, float y);
  std::pair<float, float> Move(Pos pos);

  void setType(enum Type type);
  enum Type getType();

 protected:
  std::string image_ = "";
  Pos pos_;
  float rotation_ = 0.0f;
  sf::Texture texture_;
  sf::Sprite sprite_;
  enum Type type_;
};

#endif