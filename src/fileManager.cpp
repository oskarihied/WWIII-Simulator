#include "fileManager.hpp"

#include <filesystem>
#include <fstream>
#include <sstream>

#include "game.hpp"

namespace FileManager {

namespace {

Vector ParseCoords(std::istringstream &ss, std::string &str) {
  std::getline(ss, str, ',');
  int x = std::stoi(str);
  std::getline(ss, str);
  int y = std::stoi(str);
  return Vector(x, y);
}

void AddEntityToLevel(char entityType, std::string &info,
                      std::unique_ptr<Level> &level) {
  std::istringstream ss(info);
  std::string str;
  switch (entityType) {
    case 'C': {
      Vector v = ParseCoords(ss, str);
      auto concrete = std::make_unique<Concrete>(v.GetX(), v.GetY(), level->GetTextures());
      level->AddPhysical(std::move(concrete));
    } break;

    case 'W': {
      Vector v = ParseCoords(ss, str);
      auto wood = std::make_unique<Wood>(v.GetX(), v.GetY(), level->GetTextures());
      level->AddPhysical(std::move(wood));
    } break;

    case 'G': {
      Vector v = ParseCoords(ss, str);
      auto glass = std::make_unique<Glass>(v.GetX(), v.GetY(), level->GetTextures());
      level->AddPhysical(std::move(glass));
    } break;

    case 'E': {
      Vector v = ParseCoords(ss, str);
      auto enemy = std::make_unique<Enemy>(v.GetX(), v.GetY(), level->GetTextures());
      level->AddPhysical(std::move(enemy));
    } break;

    case '*':
      std::getline(ss, str);
      switch (str.front()) {
        case 'A': {
          auto rifle = std::make_unique<Rifle>(0.0f, -0.2f, level->GetTextures());
          level->AddGun(std::move(rifle));
        } break;

        case 'R': {
          auto launcher = std::make_unique<RocketLauncher>(0.0f, -0.2f, level->GetTextures());
          level->AddGun(std::move(launcher));
        } break;

        default:
          throw std::exception();
      }
      break;

    case '+':
      std::getline(ss, str);
      {
        auto leader = std::make_unique<Entity>(0.0f, 0.0f, level->GetTextures());
        leader->SetTexture(str);
        level->AddNonPhysicalEntity(std::move(leader));
      }
      break;

    case '-':
      if (level->IsMultiplayer()) {
        std::getline(ss, str);
        {
          auto leader = std::make_unique<Entity>(40.0f, 0.0f, level->GetTextures());
          leader->SetTexture(str);
          level->AddNonPhysicalEntity(std::move(leader));
        }
      }
      break;

    default:
      throw std::exception();
  }
}

}  // namespace

bool SaveScore(const std::string &filename,
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

std::vector<std::pair<std::string, int>> LoadScore(
    const std::string &filename) {
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

std::unique_ptr<Level> LoadLevel(const std::string &filename, Game &game) {
  std::ifstream file(filename);

  if (!file.is_open()) {
    throw std::exception();
  }

  auto level = std::make_unique<Level>(game);

  char entityType;
  while (file.get(entityType)) {
    std::string info;
    while (std::getline(file, info, ';')) {
      AddEntityToLevel(entityType, info, level);
      if (file.peek() == '\n') {
        file.ignore();
        break;
      }
    }
  }

  file.close();

  return level;
}

void LoadTextures(std::map<std::string, sf::Texture> &map,
                  const std::string path) {
  map.clear();

  int i = 0;

  for (const auto &entry : std::filesystem::directory_iterator(path)) {
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

void LoadSFX(std::map<std::string, sf::SoundBuffer> &map,
             const std::string path) {
  map.clear();

  int i = 0;

  for (const auto &entry : std::filesystem::directory_iterator(path)) {
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

}  // namespace FileManager