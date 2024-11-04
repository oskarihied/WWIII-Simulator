#include <box2d/box2d.h>

#include <SFML/Graphics.hpp>
#include <iostream>

int main() {
  // Create the main window
  sf::RenderWindow window(sf::VideoMode(800, 600), "SFML window");
  b2Vec2 v = b2Vec2(4.5, 6.8);

  // Start the game loop
  while (window.isOpen()) {
    // Process events
    sf::Event event;
    while (window.pollEvent(event)) {
      // Close window: exit
      if (event.type == sf::Event::Closed) window.close();
    }

    // Clear screen
    window.clear();

    // Update the window
    window.display();
  }

  return EXIT_SUCCESS;
}