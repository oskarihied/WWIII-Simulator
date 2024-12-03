#ifndef LEVEL_HPP
#define LEVEL_HPP

#include <vector>

#include "button.hpp"
#include "camera.hpp"
#include "enemy.hpp"
#include "entity.hpp"
#include "explosion.hpp"
#include "gun.hpp"
#include "physics.hpp"

class Level {
 public:
  Level(sf::Texture& background, bool isMenu = false);

  ~Level();

  Camera* GetCam();

  bool IsMenu();

  void AddEntity(Entity* entity);
  void AddNonPhysicalEntity(Entity* entity);
  void AddBox(Box* box);
  void AddGround(Ground* ground);

  void AddButton(Button* button);

  void AddEnemy(Enemy* enemy);
  void AddScore(std::string name, int score);
  void AddBoxes(std::vector<Box*> boxes);
  void AddExplosion(Explosion* explosion, float force);

  void AddScores(std::vector<std::pair<std::string, int>> scores);
  Physics* GetPhysics();
  void Fire(float speed);

  sf::Sprite& GetBackground();

  std::vector<Entity*> GetEntities();
  std::vector<Entity*> GetNonPhysicalEntities();

  void RemoveNonPhysicalEntity(Entity* entity);
  void RemovePhysicalEntity(Entity* entity);
  void RemoveExplosion(Explosion* entity);

  std::vector<Button*> GetButtons();

  std::vector<Explosion*> GetExplosions();

  std::vector<std::pair<std::string, int>> GetLeaderboard();
  Entity* CurrentGun();
  // std::vector<Entity*> GetGuns();
  void AddGun(Gun* gun);

 protected:
  bool isMenu_;
  Camera* camera_;
  Physics* physics_;
  const std::vector<Entity*>& entities_;
  std::vector<std::pair<std::string, int>> leaderboard_;
  std::vector<Entity*> nonPhysicals_;
  std::vector<Gun*> guns_;

  Gun* currentGun_ = nullptr;

  std::vector<Explosion*> explosions_;

  sf::Sprite background_;

  std::vector<Button*> buttons_;
};

#endif
