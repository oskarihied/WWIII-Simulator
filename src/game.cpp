
#include "game.hpp"

Game::Game(int w, int h) : windowWidth_(w), windowHeight_(h) {}

Level Game::startLevel() {
    currentLevel_ = Level();
    return currentLevel_;
}

std::pair<int, int> Game::ToScreenPos(Pos pos, Camera cam) {
    float x = pos.GetX();
    float y = pos.GetY();

    x -= cam.GetPos().GetX();
    y -= cam.GetPos().GetY();

    x *= windowWidth_ / cam.GetZoom();
    y *= windowHeight_ / cam.GetZoom();

    return (std::pair((int)x, (int)y));
}

