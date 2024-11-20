#ifndef LEVEL_HPP
#define LEVEL_HPP

#include <vector>

#include "bullets.hpp"
#include "camera.hpp"
#include "enemy.hpp"
#include "entity.hpp"
#include "physics.hpp"
#include "button.hpp"
#include "enemy.hpp"

class Level {
 public:
  Level(sf::Texture& background);

  Camera* GetCam();
  
  void AddEntity(Entity* entity);
  void AddNonPhysicalEntity(Entity* entity);
  void AddBox(Box* box);
  void AddGround(Ground* ground);

  void AddButton(Button* button);

  void AddEnemy(Enemy* enemy);
  void AddScore(std::string name, int score);
  void AddBoxes(std::vector<Box*> boxes);
  void AddScores(std::vector<std::pair<std::string,int>> scores);
  Physics* GetPhysics();
  void Fire(float speed);

  sf::Sprite& GetBackground();


  std::vector<Entity*> GetEntities();
  std::vector<Entity*> GetNonPhysicalEntities();
  std::vector<Button*> GetButtons();


  std::vector<Entity*> GetEntities();
  std::vector<Entity*> GetNonPhysicalEntities();

  std::vector<std::pair<std::string, int>> GetLeaderboard();
  Entity* CurrentGun();
  // std::vector<Entity*> GetGuns();
  void AddGun(Entity* gun);

 protected:
  Camera* camera_;
  Physics* physics_;
  std::vector<Bullet*> bullets_;
  const std::vector<Entity*>& entities_;
  std::vector<std::pair<std::string,int>> leaderboard_;
  std::vector<Entity*> nonPhysicals_;
  std::vector<int> guns_;

  sf::Sprite background_;

      std::vector<Button*> buttons_;
      
};

#endif
