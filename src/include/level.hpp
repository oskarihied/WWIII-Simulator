#ifndef LEVEL_HPP
#define LEVEL_HPP

#include <SFML/Audio.hpp>
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
  Level(sf::Texture& background, std::map<std::string, sf::SoundBuffer>& sfx,
        bool isMenu = false);

  ~Level();

  Camera* GetCam();

  bool IsMenu();

  void AddBox(Box* box);
  void AddBoxes(std::vector<Box*> boxes);
  void AddGround(Ground* ground);
  void AddEnemy(Enemy* enemy);
  void AddGun(Gun* gun);
  void AddExplosion(Explosion* explosion, float force);

  void AddNonPhysicalEntity(Entity* entity);

  void AddButton(Button* button);

  void AddScore(std::string name, int score);
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
  Gun* CurrentGun();
  // std::vector<Entity*> GetGuns();

  void AddBulletTimer(float time);
  float GetTimer();
  void SetTimer(bool timer);

  void AddPoints(int points);
  int GetPoints();

  void PlaySound(const std::string name);

  std::vector<sf::Sound*>& GetSounds();

 protected:
  sf::Sprite background_;

  Camera* camera_;
  Physics* physics_;
  Gun* currentGun_ = nullptr;

  const std::vector<Entity*>& entities_;
  std::map<std::string, sf::SoundBuffer>& sfx_;

  std::vector<Entity*> nonPhysicals_;
  std::vector<Gun*> guns_;
  std::vector<Explosion*> explosions_;
  std::vector<Button*> buttons_;
  std::vector<sf::Sound*> onGoingSounds_;

  std::vector<std::pair<std::string, int>> leaderboard_;

  int points_ = 0;
  float timer_ = 0;

  bool bulletTimer_ = false;
  bool isMenu_;
};

#endif
