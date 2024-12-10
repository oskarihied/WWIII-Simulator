#include "fileManager.hpp"

#include <filesystem>
#include <fstream>
#include <sstream>

#include "game.hpp"

namespace FileManager {

namespace {

std::map<std::string, std::unique_ptr<sf::Texture>> textures_;
std::map<std::string, std::unique_ptr<sf::SoundBuffer>> soundBuffers_;

std::vector<std::unique_ptr<sf::Sound>> sounds_;

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
      auto concrete = std::make_unique<Concrete>(v.GetX(), v.GetY());
      level->AddPhysical(std::move(concrete));
    } break;

    case 'W': {
      Vector v = ParseCoords(ss, str);
      auto wood = std::make_unique<Wood>(v.GetX(), v.GetY());
      level->AddPhysical(std::move(wood));
    } break;

    case 'G': {
      Vector v = ParseCoords(ss, str);
      auto glass = std::make_unique<Glass>(v.GetX(), v.GetY());
      level->AddPhysical(std::move(glass));
    } break;

    case 'E': {
      Vector v = ParseCoords(ss, str);
      auto enemy = std::make_unique<Enemy>(v.GetX(), v.GetY());
      level->AddPhysical(std::move(enemy));
    } break;

    case 'H': {
      Vector v = ParseCoords(ss, str);
      auto ground = std::make_unique<Ground>(v.GetX(), v.GetY());
      level->AddPhysical(std::move(ground));
    } break;

    case '*':
      std::getline(ss, str);
      switch (str.front()) {
        case 'A': {
          auto rifle = std::make_unique<Rifle>(0.0f, -0.2f);
          level->AddGun(std::move(rifle));
        } break;

        case 'R': {
          auto launcher = std::make_unique<RocketLauncher>(0.0f, -0.2f);
          level->AddGun(std::move(launcher));
        } break;

        default:
          throw std::exception();
      }
      break;

    case '+':
      std::getline(ss, str);
      {
        auto leader = std::make_unique<Entity>(0.0f, 0.0f);
        leader->SetTexture(str);
        level->AddNonPhysicalEntity(std::move(leader));
      }
      break;

    case '-':
      if (level->IsMultiplayer()) {
        std::getline(ss, str);
        {
          auto leader = std::make_unique<Entity>(40.0f, 0.0f);
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
      } else if (file.peek() == '\r') {
        file.ignore();
        file.ignore();
        break;
      }
    }
  }

  file.close();

  for (auto it = level->GetPhysicals().begin(); it != level->GetPhysicals().end(); ++it) {
    std::unique_ptr<Physical>& entity = *it;
    //std::cout<< "points: " << entity.get()->GetPoints() << std::endl;
    level->AddMaxPoints(entity.get()->GetPoints());
  }

  for (auto it = level->GetGuns().begin(); it != level->GetGuns().end(); ++it) {
    std::unique_ptr<Gun>& entity = *it;
    level->AddMaxPoints(entity.get()->GetPoints());
  }

  return level;
}

void LoadTextures(const std::string path) {
  textures_.clear();

  int i = 0;
  for (const auto &entry : std::filesystem::directory_iterator(path)) {
    auto thisTexture = std::make_unique<sf::Texture>();
    thisTexture->loadFromFile(entry.path());

    std::string name = entry.path();
    name.erase(0, (int)(path.length() + 1));
    name.erase(name.length() - 4);

    textures_.insert({name, std::move(thisTexture)});
    i++;
  }
}

std::unique_ptr<sf::Texture> &GetTexture(const std::string name) {
  return textures_.at(name);
}

void LoadSFX(const std::string path) {
  soundBuffers_.clear();

  int i = 0;
  for (const auto &entry : std::filesystem::directory_iterator(path)) {
    auto buffer = std::make_unique<sf::SoundBuffer>();
    buffer->loadFromFile(entry.path());

    std::string name = entry.path();
    name.erase(0, (int)(path.length() + 1));
    name.erase(name.length() - 4);

    soundBuffers_.insert({name, std::move(buffer)});
    i++;
  }
}

void PlaySound(const std::string name) {
  auto sound = std::make_unique<sf::Sound>(*soundBuffers_.at(name));
  sound->play();

  bool foundNull = false;
  for (auto &s : sounds_) {
    if (s.get() == nullptr) {
      s.reset(sound.release());
      foundNull = true;
      break;
    }
  }

  if (!foundNull) {
    sounds_.push_back(std::move(sound));
  }
}

void DestroySFML() {
  for (auto &t : textures_) {
    t.second = nullptr;
  }

  for (auto &sb : soundBuffers_) {
    sb.second = nullptr;
  }

  for (auto &s : sounds_) {
    s = nullptr;
  }
}

}  // namespace FileManager