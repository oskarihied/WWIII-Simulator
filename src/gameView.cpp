#include "gameView.hpp"

#include <typeinfo>

#include "game.hpp"

GameView::GameView(Game& game) : game_(game) {
  camera_ = std::make_unique<Camera>(-1, 4);
}

GameView::~GameView() {};

void GameView::AddButton(std::unique_ptr<Button> button) {
  buttons_.push_back(std::move(button));
}

void GameView::AddNonPhysicalEntity(std::unique_ptr<Entity> entity) {
  nonPhysicals_.push_back(std::move(entity));
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
  Vector pos = game_.ToScreenPos(entity->GetPos(), *camera_);

  float scale = (game_.GetDimensions().GetX() / 200.0f) / camera_->GetZoom();
  float rotation;
  if (entity->GetType() == Entity::EntityType::UNDEFINED) {
    rotation = entity->GetRotation();
  } else {
    rotation = -entity->GetRotation();
  }

  entity->GetSprite().setPosition(pos.GetX(), -pos.GetY());
  entity->GetSprite().setRotation(rotation);

  if (entity->GetSprite().getScale().x < 0) {
    entity->GetSprite().setScale(sf::Vector2(-scale, scale));
  } else if (entity->GetSprite().getScale().y < 0) {
    entity->GetSprite().setScale(sf::Vector2(scale, -scale));
  } else {
    entity->GetSprite().setScale(sf::Vector2(scale, scale));
  }

  window.draw(entity->GetSprite());
}

template void GameView::RenderEntity<Entity>(std::unique_ptr<Entity>&,
                                             sf::RenderWindow&);

template void GameView::RenderEntity<Physical>(std::unique_ptr<Physical>&,
                                               sf::RenderWindow&);

template void GameView::RenderEntity<Gun>(std::unique_ptr<Gun>&,
                                          sf::RenderWindow&);

template void GameView::RenderEntity<Button>(std::unique_ptr<Button>&,
                                             sf::RenderWindow&);