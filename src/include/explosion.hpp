#ifndef EXPLOSION_HPP
#define EXPLOSION_HPP

#include "entity.hpp"

class Explosion : public Entity {
 public:
  Explosion(float x, float y);

  const int& GetCount() const;

  void NextSprite();

 private:
  int count_ = 0;
};

#endif