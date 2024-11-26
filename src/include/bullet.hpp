#ifndef BULLET_HPP
#define BULLET_HPP

#include "rigid.hpp"

class Bullet : public Rigid {
       public:
              Bullet(float x, float y, float xVel, float yVel, std::string image, float w,
              float h, float mass, int hp);
              
              Bullet(float x, float y, float xVel, float yVel, sf::Texture& texture, float w,
                     float h, float mass, int hp);

              float CalculateDmg();
};


class RegularBullet : public Bullet {
 public:
  RegularBullet(float x, float y, float xVel, float yVel);
      //: Bullet(0, 0, xVel, yVel, "images/bullet.png", 0.4f, 0.1f, 20, 1) {}
};

class RifleBullet : public Bullet {
    public:
        RifleBullet(float x, float y, std::map<std::string, sf::Texture> textures);
           // : Bullet(x, y, 0, 0, textures.at("bullet"), 0.4f, 0.1f, 20, 1) {}
};


class Rocket : public Bullet {
    public:
       Rocket(float x, float y, std::map<std::string, sf::Texture> textures);
            //: Bullet(x, y, 0, 0, textures.at("rocket"), 0.4f, 0.1f, 20, 1) {}
};


#endif