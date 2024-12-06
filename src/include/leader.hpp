#ifndef LEADER_HPP
#define LEADER_HPP

#include "entity.hpp"

class Leader : public Entity {
 public:
  Leader(float x, float y, const std::string leaderName,
         std::map<std::string, sf::Texture>& textures);
};

#endif