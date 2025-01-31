#include <SFML/Graphics.hpp>
#include <filesystem>
#include <iostream>

#include "game.hpp"

int main() {

  std::cout << "Current working directory: " << std::filesystem::current_path()
            << std::endl;

  //Create window
  sf::RenderWindow window(sf::VideoMode(), "WWIII Simulator",
                          sf::Style::Fullscreen);

  int w = window.getSize().x;
  int h = window.getSize().y;

  Game game = Game(w, h);

  game.StartMenu();

  //Framerate to 60
  window.setFramerateLimit(60);
  // Start the game loop
  while (window.isOpen()) {
    // Process events
    game.GetCurrentView()->StepInTime(window);

    // Clear screen
    window.clear();

    game.GetCurrentView()->Render(window);

    //  Update the window
    window.display();
  }

  //Destroy loaded data when the game ends
  FileManager::DestroySFML();

  return EXIT_SUCCESS;
}