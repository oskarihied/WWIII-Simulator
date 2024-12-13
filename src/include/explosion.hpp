#ifndef EXPLOSION_HPP
#define EXPLOSION_HPP

#include "entity.hpp"

//An explosion class to track the explosion animation
class Explosion : public Entity {
 public:
  //params: x and y coordinates
  Explosion(float x, float y);

  //returns: what texture does the explosion have currently
  const int& GetCount() const;

  //changes a new texture
  void NextSprite();

 private:
  //texture index
  int count_ = 0;
};

#endif