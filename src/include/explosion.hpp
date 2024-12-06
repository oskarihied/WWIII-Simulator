#ifndef EXPLOSION_HPP
#define EXPLOSION_HPP

#include "entity.hpp"

class Explosion : public Entity {
 public:
  Explosion(float x, float y, std::map<std::string, sf::Texture>& textures);

  const int& GetCount() const;

  void NextSprite();

 private:
  int count_ = 0;
};

#endif