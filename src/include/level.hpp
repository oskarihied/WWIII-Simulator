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

  ~Level();

  void AddBox(std::unique_ptr<Box> box);
  void AddGround(std::unique_ptr<Ground> ground);
  void AddEnemy(std::unique_ptr<Enemy> enemy);
  void AddGun(std::unique_ptr<Gun> gun);
  void AddExplosion(Explosion* explosion, float force);

  void AddScore(std::string name, int score);
  void AddScores(std::vector<std::pair<std::string, int>> scores);

  void Fire(float speed);

  void RemoveNonPhysicalEntity(Entity* entity);
  void RemoveExplosion(Explosion* entity);

  std::vector<Explosion*> GetExplosions();

  std::vector<std::pair<std::string, int>> GetLeaderboard();

  void AddBulletTimer(float time);
  float GetTimer();
  void SetTimer(bool timer);

  void AddPoints(int points);
  int GetPoints();

  std::vector<std::unique_ptr<Gun>>& GetGuns();

  void StepInTime(sf::RenderWindow& window);

  void Render(sf::RenderWindow& window);

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
};

#endif