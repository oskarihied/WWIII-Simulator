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

  void AddExplosion(std::unique_ptr<Explosion> explosion, float force);

  void AddScore(std::string name, int score);
  void AddScores(std::vector<std::pair<std::string, int>> scores);

  void Fire(float speed);

  std::vector<std::pair<std::string, int>> GetLeaderboard();

  void IncrementBulletTimer(float time);
  float GetTimer();
  void SetTimer(bool timer);

  void AddPoints(int points);
  int GetPoints();

  std::vector<std::unique_ptr<Physical>>& GetPhysicals();

  std::vector<std::unique_ptr<Gun>>& GetGuns();

  const bool& IsMultiplayer();

  void StepInTime(sf::RenderWindow& window);

  void Render(sf::RenderWindow& window);

  void AddMaxPoints(int points);

  template <typename T>
  void AddPhysical(std::unique_ptr<T> physical) {
    if (IsMultiplayer() && physical->GetType() != Entity::EntityType::GROUND) {
      float x = physical->GetPos().GetX();
      float y = physical->GetPos().GetY();
      std::unique_ptr<T> mirrored = std::make_unique<T>(40.0f - x, y);
      mirrored->SetSide(true);
      physics_->AddBoxBody(mirrored);
      physicals_.push_back(std::move(mirrored));
    }
    physics_->AddBoxBody(physical);
    physicals_.push_back(std::move(physical));
  }

  template <typename T>
  void AddGun(std::unique_ptr<T> gun) {
    if (IsMultiplayer()) {
      float x = gun->GetPos().GetX();
      float y = gun->GetPos().GetY();
      std::unique_ptr<T> mirrored = std::make_unique<T>(40.0f - x, y);
      mirrored->GetSprite().setScale(1, -1);
      guns_.push_back(std::move(gun));
      guns_.push_back(std::move(mirrored));
    } else {
      guns_.push_back(std::move(gun));
    }
  }

 private:
  std::unique_ptr<Physics> physics_;
  Bullet* currentBullet_ = nullptr;

  sf::Font font_;
  sf::Text pointsText_;
  sf::Text powerText_;
  bool showPower_ = false;

  Entity complete_ = Entity(0, 0);
  Entity star1_ = Entity(0, 0);
  Entity star2_ = Entity(0, 0);
  Entity star3_ = Entity(0, 0);

  std::vector<std::unique_ptr<Physical>> physicals_;
  std::vector<std::unique_ptr<Gun>> guns_;
  std::vector<std::unique_ptr<Explosion>> explosions_;

  std::vector<std::pair<std::string, int>> leaderboard_;

  int points_ = 0;
  int maxPoints_ = 0;
  int highscore_ = 0;

  sf::Clock gunTimer_;

  bool over_ = false;
  bool over2_ = false;
  bool win_ = false;

  float timer_ = 0;
  bool bulletTimer_ = false;

  Entity winner_ = Entity(0, 0);

  void RenderAmmo(sf::RenderWindow& window, std::unique_ptr<Gun>& gun,
                  const int& index);
};

#endif