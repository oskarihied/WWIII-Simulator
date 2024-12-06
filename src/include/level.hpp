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

  void AddBox(Box* box);
  void AddBoxes(std::vector<Box*> boxes);
  void AddGround(Ground* ground);
  void AddEnemy(Enemy* enemy);
  void AddGun(Gun* gun);
  void AddExplosion(Explosion* explosion, float force);

  void AddScore(std::string name, int score);
  void AddScores(std::vector<std::pair<std::string, int>> scores);

  void Fire(float speed);

  void RemoveNonPhysicalEntity(Entity* entity);
  std::vector<Entity*>::const_iterator RemovePhysicalEntity(Entity* entity);
  void RemoveExplosion(Explosion* entity);

  std::vector<Explosion*> GetExplosions();

  std::vector<std::pair<std::string, int>> GetLeaderboard();
  // std::vector<Entity*> GetGuns();

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

  std::vector<std::unique_ptr<Gun>> guns_;
  std::vector<Explosion*> explosions_;

  std::vector<std::pair<std::string, int>> leaderboard_;

  int points_ = 0;

  sf::Clock gunTimer_;

  float timer_ = 0;

  bool bulletTimer_ = false;
};

#endif