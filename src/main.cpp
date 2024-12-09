#include <SFML/Graphics.hpp>
#include <filesystem>
#include <iostream>

#include "game.hpp"

int main() {
  // Create the main window

  std::cout << "Current working directory: " << std::filesystem::current_path()
            << std::endl;

  int w = 1300;
  int h = 700;

  Game game = Game(w, h);

  game.StartMenu();

  sf::RenderWindow window(sf::VideoMode(), "WWIII Simulator",
                          sf::Style::Fullscreen);

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

  FileManager::DestroySFML();

  return EXIT_SUCCESS;
}