#include "gameView.hpp"

#include <typeinfo>

#include "game.hpp"

GameView::GameView(Game& game) : game_(game) {
  camera_ = std::make_unique<Camera>(-1, 4);
}

GameView::~GameView() {
  for (auto& button : buttons_) {
    button = nullptr;
  }

  for (auto& nonPhysical : nonPhysicals_) {
    nonPhysical = nullptr;
  }

  camera_ = nullptr;
}

void GameView::AddButton(Button* button) {
  std::unique_ptr<Button> uptr(button);
  buttons_.push_back(std::move(uptr));
}

void GameView::AddNonPhysicalEntity(Entity* entity) {
  std::unique_ptr<Entity> uptr(entity);
  nonPhysicals_.push_back(std::move(uptr));
}

std::unique_ptr<Camera>& GameView::GetCam() { return camera_; }

std::vector<std::unique_ptr<Button>>& GameView::GetButtons() {
  return buttons_;
}

std::vector<std::unique_ptr<Entity>>& GameView::GetNonPhysicals() {
  return nonPhysicals_;
}

template <typename T>
void GameView::RenderEntity(std::unique_ptr<T>& entity,
                            sf::RenderWindow& window) {
  float scale = (1300.0f / 200.0f) / camera_->GetZoom();

  entity->GetSprite()->setScale(sf::Vector2(scale, scale));
  entity->GetSprite()->setRotation(entity->GetRotation());

  std::pair<int, int> pos = game_.ToScreenPos(entity->GetPos(), *camera_);
  entity->GetSprite()->setPosition(pos.first, -pos.second);

  window.draw(*(entity->GetSprite()));
}

template void GameView::RenderEntity<Entity>(std::unique_ptr<Entity>&,
                                             sf::RenderWindow&);
template void GameView::RenderEntity<Gun>(std::unique_ptr<Gun>&,
                                          sf::RenderWindow&);
template void GameView::RenderEntity<Button>(std::unique_ptr<Button>&,
                                             sf::RenderWindow&);