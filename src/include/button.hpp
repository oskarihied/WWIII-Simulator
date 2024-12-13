#ifndef BUTTON_HPP
#define BUTTON_HPP

#include "entity.hpp"

//UI Button for the Menu
class Button : public Entity {
 public:
  //params: x and y coordinates, width and height of the button, texture name of the button
  Button(float x, float y, float w, float h, const std::string textureName);

  //params: mouses x and y coordinates
  //returns: true if the mouse is over the button, else false.
  bool IsTouching(float x, float y);
};

#endif