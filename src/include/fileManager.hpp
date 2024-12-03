#ifndef FILE_MANAGER_HPP
#define FILE_MANAGER_HPP

#include <map>
#include <string>
#include <vector>

#include "box.hpp"
#include "level.hpp"

class FileManager {
 public:
  bool SaveScore(const std::string& filename,
                 std::vector<std::pair<std::string, int>> scores);
  std::vector<std::pair<std::string, int>> LoadScore(
      const std::string& filename);

  /*bool SaveLevel(const std::string& filename, const std::vector<Entity*>&
   * entities);*/

  void AddEntityToLevel(Level* level, std::string type, int x, int y,
                        std::map<std::string, sf::Texture> textures);

  Level* LoadLevel(const std::string& filename,
                   std::map<std::string, sf::Texture>& textures,
                   const bool& multiplayer);

  void LoadTextures(std::map<std::string, sf::Texture>& map, std::string path);
};

#endif