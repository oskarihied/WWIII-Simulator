#include "entity.hpp"

class Physical : public Entity {
 public:
  Physical(float x, float y);
  Physical(float x, float y, std::string image, float mass, float width,
           float height);
  Physical(float x, float y, float xVel, float yVel, std::string image,
           float mass, float width, float height);

  float GetWidth();
  float GetHeight();

 protected:
  float mass_;
  float width_;
  float height_;
};