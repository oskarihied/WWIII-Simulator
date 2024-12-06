#include "leader.hpp"

Leader::Leader(float x, float y, const std::string leaderName,
               std::map<std::string, sf::Texture>& textures)
    : Entity(x, y, textures) {
  SetTexture(leaderName);
}