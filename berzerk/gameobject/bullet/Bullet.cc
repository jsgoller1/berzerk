#include "Bullet.hh"

#include <iostream>

#include "Color.hh"
#include "Direction.hh"
#include "DrawingProxy.hh"
#include "PlayerSpriteManager.hh"
#include "Vect2D.hh"

Bullet::Bullet(const Vect2D& position, const Direction& direction, DrawingProxy& drawingProxy,
               const BulletSpriteManager& bulletSpriteManager)
    : GameObject(position, Vect2D(direction) * BULLET_DEFAULT_SPEED) {
  std::shared_ptr<Sprite> sprite;
  if (direction == Direction::SouthWest() || direction == Direction::NorthEast()) {
    sprite = bulletSpriteManager.bulletNE();
  } else if (direction == Direction::SouthEast() || direction == Direction::NorthWest()) {
    sprite = bulletSpriteManager.bulletSE();
  } else if (direction == Direction::North() || direction == Direction::South()) {
    sprite = bulletSpriteManager.bulletVertical();
  } else {  // direction == East or direction == West
    sprite = bulletSpriteManager.bulletHorizontal();
  }
  this->_drawingComponent = std::unique_ptr<StaticDrawingComponent>(new StaticDrawingComponent(
      this->getPositionComponent(), BULLET_DEFAULT_HEIGHT, BULLET_DEFAULT_WIDTH, drawingProxy, sprite));
}

void Bullet::resolveCollision(GameObject& target) {
  (void)target;
  this->setShouldRemove(true);
}
StaticDrawingComponent& Bullet::getDrawingComponent() const { return *this->_drawingComponent; }

void Bullet::update() { this->move(); }
