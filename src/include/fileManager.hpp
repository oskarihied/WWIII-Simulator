#ifndef FILE_MANAGER_HPP
#define FILE_MANAGER_HPP

#include <SFML/Audio.hpp>
#include <map>
#include <string>
#include <vector>

#include "level.hpp"

namespace FileManager {

bool SaveScore(const std::string& filename,
               std::vector<std::pair<std::string, int>> scores);

std::vector<std::pair<std::string, int>> LoadScore(const std::string& filename);

/*bool SaveLevel(const std::string& filename, const std::vector<Entity*>&
 * entities);*/

std::unique_ptr<Level> LoadLevel(const std::string& filename, Game& game);

void LoadTextures(std::map<std::string, sf::Texture>& map,
                  const std::string path);

void LoadSFX(std::map<std::string, sf::SoundBuffer>& map,
             const std::string path);
};  // namespace FileManager

#endif