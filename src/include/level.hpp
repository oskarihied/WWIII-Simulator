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

//Level where the actual gameplay happens
//Has methods for playing the game
class Level : public GameView {
 public:
  //params: current game
  Level(Game& game);

  //Adds a new explosion to the scene
  //params: explosion pointer, force of the explosion
  void AddExplosion(std::unique_ptr<Explosion> explosion, float force);

  //Adds a single score
  //params: nickname, score
  void AddScore(std::string name, int score);
  //Adds a multiple scores
  //params: list of nicknames and scores
  void AddScores(std::vector<std::pair<std::string, int>> scores);

  //Fires a bullet for the current gun
  //params: shooting speed
  void Fire(float speed);

  //returns: leaderboard
  std::vector<std::pair<std::string, int>> GetLeaderboard();

  //adds time to bullettimer. For bullet follow animations.
  //params: time added
  void IncrementBulletTimer(float time);
  //returns: bullet timers value
  float GetTimer();
  //params: time to set the bullet timer to
  void SetTimer(bool timer);

  //adds an amount to the points
  //params: points added
  void AddPoints(int points);
  //adds an amount to levels max points
  //params: amount of points
  void AddMaxPoints(int points);
  //returns: points
  int GetPoints();

  //returns: list of physical entities in the scene
  std::vector<std::unique_ptr<Physical>>& GetPhysicals();

  //returns: list of guns left
  std::vector<std::unique_ptr<Gun>>& GetGuns();

  //returns: if multiplayer is on or off
  const bool& IsMultiplayer();

  //Moves a single step in time. Called every loop
  //Calls for physics step in time and adds timer value
  //params: current window
  void StepInTime(sf::RenderWindow& window);

  //Draws entity sprites to the screen
  //Called every loop
  //params: current window
  void Render(sf::RenderWindow& window);

  //Adds a physical entity to the scene
  //params: a physical entity
  template <typename T>
  void AddPhysical(std::unique_ptr<T> physical) {
    //Creates a mirrored copy for the multiplayer
    if (IsMultiplayer() && physical->GetType() != Entity::EntityType::GROUND) {
      float x = physical->GetPos().GetX();
      float y = physical->GetPos().GetY();
      //create a copy
      std::unique_ptr<T> mirrored = std::make_unique<T>(40.0f - x, y);
      //set side to plr2
      mirrored->SetSide(true);
      //add to lists
      physics_->AddBoxBody(mirrored);
      physicals_.push_back(std::move(mirrored));
    }
    //adds the entity to physics and to physicals list
    physics_->AddBoxBody(physical);
    physicals_.push_back(std::move(physical));
  }

  //adds a gun to the scene
  //params: the gun
  template <typename T>
  void AddGun(std::unique_ptr<T> gun) {
    //copies the gun for multiplayer
    if (IsMultiplayer()) {
      float x = gun->GetPos().GetX();
      float y = gun->GetPos().GetY();
      //mirroring the gun
      std::unique_ptr<T> mirrored = std::make_unique<T>(40.0f - x, y);
      //mirroring the sprite
      mirrored->GetSprite().setScale(1, -1);
      //adding two guns
      guns_.push_back(std::move(gun));
      guns_.push_back(std::move(mirrored));
    } else {
      //adding gun
      guns_.push_back(std::move(gun));
    }
  }

 private:
  //Levels physic counterpart
  std::unique_ptr<Physics> physics_;

  //bullet currently in use
  Bullet* currentBullet_ = nullptr;

  //a font used
  sf::Font font_;

  //UI texts in the level. For points and bullet power
  sf::Text pointsText_;
  sf::Text powerText_;
  //whether to show power. Only when shooting
  bool showPower_ = false;

  //UI entities in the level
  Entity complete_ = Entity(0, 0);
  Entity star1_ = Entity(0, 0);
  Entity star2_ = Entity(0, 0);
  Entity star3_ = Entity(0, 0);
  Entity winner_ = Entity(0, 0);

  //lists of different entities of the level
  std::vector<std::unique_ptr<Physical>> physicals_;
  std::vector<std::unique_ptr<Gun>> guns_;
  std::vector<std::unique_ptr<Explosion>> explosions_;

  //leaderboard of nicknames and points
  std::vector<std::pair<std::string, int>> leaderboard_;

  //current points
  int points_ = 0;
  //maximum points of the level
  int maxPoints_ = 0;

  //highscore
  int highscore_ = 0;

  //timer for shooting
  sf::Clock gunTimer_;
  //timer for bullet following animation
  float timer_ = 0;
  //whether bullettimer is on or off
  bool bulletTimer_ = false;

  //whether the level is over (plr1 won)
  bool over_ = false;
  //same but if plr2 won
  bool over2_ = false;
  //true if the level was won
  bool win_ = false;

  //Renders the guns left
  //params: current window, gun, guns index
  void RenderAmmo(sf::RenderWindow& window, std::unique_ptr<Gun>& gun,
                  const int& index);
};

#endif