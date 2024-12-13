#ifndef ENTITY_HPP
#define ENTITY_HPP

#include <SFML/Graphics.hpp>
#include <iostream>
#include <optional>
#include <string>
#include <vector>

#include "vector.hpp"

//Entity depicts an object in the GameView
//Has a sprite for rendering
class Entity {
 public:
  //Entity types for physics handling
  enum class EntityType {
    UNDEFINED,
    BOX,
    GROUND,
    BULLET,
    ENEMY,
    EXPLOSION,
    GUN
  };

  //params: x and y coordinates
  Entity(float x, float y);

  //returns position and velocity of the entity
  Vector& GetPos();
  Vector& GetVel();

  //Sets the entity velocity to new values
  //params: new velocity components
  void UpdateVel(float xVel, float yVel);

  //Moves the entity to new position
  //params: new x and y coordinates
  void MoveTo(float x, float y);
  //Sets entity rotation to new value
  //params: new rotation value
  void RotationTo(float x);

  //return variables of the entity
  const float& GetRotation();
  const float& GetHealth();
  const float& GetMaxHealth();
  int GetPoints();
  const float& GetWidth();
  const float& GetHeight();

  //virtual method for changing texture of damaged entities
  virtual void BecomeDamaged();

  //params: new health
  void SetHealth(float health);
  //changes health by wanted amount
  //params: amount of health. Negative value for damaging, positive for healing
  void ChangeHealth(float amount);

  //Sets a new texture for the entity
  //params: name of the new texture
  void SetTexture(const std::string name);

  //returns: the sprite of the entity
  sf::Sprite& GetSprite();
  //return: a copy of the sprite
  sf::Sprite CopySprite();

  //sets a entity type
  //params: new type
  void SetType(enum EntityType type);
  enum EntityType GetType();

  //Sets dead to true
  void Die();
  //returns: true if dead, false if not
  bool IsDead();

  //returns: whether the entity is an explosive or not
  bool Explodes();
  //sets a value that represents if the entity explodes when its hp hits zero.
  //params: true->explodes, false->doesn't explode
  void SetExplodes(bool explodes);
  
  //params: entitys sound. Played when hp hits zero.
  void SetSound(std::string str);
  //returns: entitys sound
  std::string GetSound();

  //sets a side for the entity. To decide winner in multiplayer
  //false->player 1, true->player 2
  void SetSide(bool side);
  //returns: side of the entity
  bool GetSide();
  

 protected:
  //type of the entity
  enum EntityType type_ = EntityType::UNDEFINED;

  //sprite for rendering
  sf::Sprite sprite_;

  //position and velocity
  Vector pos_;
  Vector vel_ = Vector();

  //entity dimensions and rotation
  float width_ = 1.0f;
  float height_ = 1.0f;
  float rotation_ = 0.0f;

  //hp
  float health_ = 1000;
  float maxHealth_ = 1000;

  //points that are awarded to the player when the entity dies
  int points_ = 0;

  //true if the entity is dead
  bool dead_ = false;

  //true if the entity is an explosive
  bool explodes_ = false;

  //dying sound
  std::string sound_ = "";

  //false if plr1, true if plr2
  bool side_ = false;
};

#endif