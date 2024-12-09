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

void LoadTextures(const std::string path);

std::unique_ptr<sf::Texture>& GetTexture(const std::string name);

void LoadSFX(const std::string path);

void PlaySound(const std::string name);

void DestroySFML();

};  // namespace FileManager

#endif