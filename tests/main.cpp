#include <filesystem>
#include <iostream>

#include "level.hpp"
#include "game.hpp"

int main() {

  Game game = Game(20, 20);
  Level level(game);

  auto box0 = std::make_unique<Concrete>(1, 1);

  level.AddPhysical(std::move(box0));
  
  if (level.GetPhysicals().size() != 1) throw std::runtime_error("Entities wrong size");

  if (level.GetPoints() != 0) throw std::runtime_error("Wrong amount of points");

  level.AddPoints(30);
  
  if (level.GetPoints() != 30) throw std::runtime_error("Wrong amount of points added");

  std::cout << "All tests ran successfully" << std::endl;
  return EXIT_SUCCESS;
}