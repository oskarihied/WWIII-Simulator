#ifndef LEVEL_HPP
#define LEVEL_HPP

#include <SFML/Audio.hpp>
#include <vector>

#include "enemy.hpp"
#include "explosion.hpp"
#include "gameView.hpp"
#include "gun.hpp"
#include "physics.hpp"

class Game;

class Level : public GameView {
 public:
  Level(Game& game);

  void AddExplosion(Explosion* explosion, float force);

  void AddScore(std::string name, int score);
  void AddScores(std::vector<std::pair<std::string, int>> scores);

  void Fire(float speed);

  void RemoveNonPhysicalEntity(Entity* entity);
  void RemoveExplosion(Explosion* entity);

  std::vector<Explosion*> GetExplosions();

  std::vector<std::pair<std::string, int>> GetLeaderboard();

  void IncrementBulletTimer(float time);
  float GetTimer();
  void SetTimer(bool timer);

  void AddPoints(int points);
  int GetPoints();

  std::vector<std::unique_ptr<Gun>>& GetGuns();
  std::map<std::string, sf::Texture>& GetTextures();

  const bool& IsMultiplayer();

  void StepInTime(sf::RenderWindow& window);

  void RenderAmmo(sf::RenderWindow& window, std::unique_ptr<Gun>& gun,
                  const int& index);

  void Render(sf::RenderWindow& window);

  template <typename T>
  void AddPhysical(std::unique_ptr<T> physical) {
    if (IsMultiplayer() && physical->GetType() != Entity::EntityType::GROUND) {
      float x = physical->GetPos().GetX();
      float y = physical->GetPos().GetY();
      std::unique_ptr<T> mirrored =
          std::make_unique<T>(40.0f - x, y, GetTextures());
      AddPhysicalForReal(std::move(mirrored));
    }
    AddPhysicalForReal(std::move(physical));
  }

  template <typename T>
  void AddGun(std::unique_ptr<T> gun) {
    if (IsMultiplayer()) {
      float x = gun->GetPos().GetX();
      float y = gun->GetPos().GetY();
      std::unique_ptr<T> mirrored =
          std::make_unique<T>(40.0f - x, y, GetTextures());
      guns_.push_back(std::move(gun));
      guns_.push_back(std::move(mirrored));
    } else {
      guns_.push_back(std::move(gun));
    }
  }

 protected:
  std::unique_ptr<Physics> physics_;
  Bullet* currentBullet_ = nullptr;

  std::vector<std::unique_ptr<Physical>> physicals_;
  std::vector<std::unique_ptr<Gun>> guns_;
  std::vector<Explosion*> explosions_;

  std::vector<std::pair<std::string, int>> leaderboard_;

  int points_ = 0;

  sf::Clock gunTimer_;

  float timer_ = 0;

  bool bulletTimer_ = false;

  template <typename T>
  void AddPhysicalForReal(std::unique_ptr<T> physical) {
    if (physical->GetType() == Entity::EntityType::GROUND) {
      physics_->AddBoxBody(physical, false);
    } else {
      physics_->AddBoxBody(physical, true);
    }
    physicals_.push_back(std::move(physical));
  }
};

#endif