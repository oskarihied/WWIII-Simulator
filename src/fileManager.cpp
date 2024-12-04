#include "fileManager.hpp"

#include <filesystem>
#include <fstream>
#include <sstream>

#include "boxes.hpp"
#include "enemy.hpp"

bool FileManager::SaveScore(const std::string& filename,
                            std::vector<std::pair<std::string, int>> scores) {
  std::ofstream file(filename);

  if (!file.is_open()) {
    return false;
  }

  for (auto it : scores) {
    file << it.first << ";" << it.second << "\n";
  }

  file.close();
  return true;
}

std::vector<std::pair<std::string, int>> FileManager::LoadScore(
    const std::string& filename) {
  std::vector<std::pair<std::string, int>> scores;
  std::ifstream file(filename);

  if (!file.is_open()) {
    return scores;
  }

  std::string line;
  while (std::getline(file, line)) {
    std::istringstream stream(line);
    std::string name;
    int score;
    std::getline(stream, name, ';');
    stream >> score;
    scores.push_back(std::make_pair(name, score));
  }

  file.close();
  return scores;
}

/*bool FileManager::SaveLevel(const std::string& filename, const
std::vector<Entity*>& entities){ std::ofstream file(filename);

    if(!file.is_open()){
        return false;
    }

    for(auto it : entities){
        file << it->GetPos
    }
}*/

void FileManager::AddEntityToLevel(
    Level* level, std::string type, float x, float y,
    std::map<std::string, sf::Texture> textures) {
  if (type == "C") {
    level->AddBox(new Concrete(x, y, textures));
  } else if (type == "W") {
    level->AddBox(new Wood(x, y, textures));
  } else if (type == "G") {
    level->AddBox(new Glass(x, y, textures));
  } else if (type == "E") {
    level->AddEnemy(new Enemy(x, y, textures));
  } else if (type == "A") {
    level->AddGun(new Rifle(x, y, textures));
  } else if (type == "R") {
    level->AddGun(new RocketLauncher(x, y, textures));
  }
}

Level* FileManager::LoadLevel(const std::string& filename,
                              std::map<std::string, sf::Texture>& textures,
                              std::map<std::string, sf::SoundBuffer>& sfx,
                              const bool& multiplayer) {
  std::ifstream file(filename);

  if (!file.is_open()) {
    return nullptr;
  }

  Level* level = new Level(textures.at("background1"), sfx);

  std::string line;
  while (std::getline(file, line)) {
    std::string type;
    float x, y;

    std::istringstream stream(line);

    if (stream.peek() == '*') {
      stream.ignore();
      x = 0;
      y = -0.2;
      while (std::getline(stream, type, ';')) {
        AddEntityToLevel(level, type, x, y, textures);
        if (multiplayer) {
          int mirrorX = 20 + (20 - x);
          AddEntityToLevel(level, type, mirrorX, y, textures);
        }
      }
    } else if (stream.peek() == '+') {
      stream.ignore();
      x = 0;
      y = 0;
      std::string icon;
      std::getline(stream, icon);
      level->AddNonPhysicalEntity(new Entity(x, y, textures.at(icon)));
    } else if (stream.peek() == '-') {
      if (multiplayer) {
        stream.ignore();
        x = 40;
        y = 0;
        std::string icon;
        std::getline(stream, icon);
        level->AddNonPhysicalEntity(new Entity(x, y, textures.at(icon)));
      } else {
        std::string byeBye;
        std::getline(stream, byeBye);
      }
    } else {
      std::getline(stream, type, ';');
      stream >> x;
      stream.ignore();
      stream >> y;
      AddEntityToLevel(level, type, x, y, textures);
      if (multiplayer) {
        int mirrorX = 20 + (20 - x);
        AddEntityToLevel(level, type, mirrorX, y, textures);
      }
    }
  }

  file.close();
  return level;
}

void FileManager::LoadTextures(std::map<std::string, sf::Texture>& map,
                               const std::string path) {
  map.clear();

  int i = 0;

  for (const auto& entry : std::filesystem::directory_iterator(path)) {
    sf::Texture thisTexture;
    thisTexture.loadFromFile(entry.path());

    std::string name = entry.path();
    name.erase(0, (int)(path.length() + 1));
    name.erase(name.length() - 4);

    map.insert({name, thisTexture});

    // std::cout << name  << " " << i << std::endl;

    i++;
  }
}

void FileManager::LoadSFX(std::map<std::string, sf::SoundBuffer>& map,
                          const std::string path) {
  map.clear();

  int i = 0;

  for (const auto& entry : std::filesystem::directory_iterator(path)) {
    sf::SoundBuffer buffer;
    buffer.loadFromFile(entry.path());

    std::string name = entry.path();
    name.erase(0, (int)(path.length() + 1));
    name.erase(name.length() - 4);

    map.insert({name, buffer});

    // std::cout << name << " " << i << std::endl;

    i++;
  }
}