#pragma once
#include <memory>

#include "BulletSpriteManager.hh"
#include "Configs.hh"
#include "GameObject.hh"
#include "StaticDrawingComponent.hh"

// fwd decl
class Color;
class Direction;
class DrawingProxy;
class Vect2D;

class Bullet : public GameObject {
 public:
  Bullet(const Vect2D& position, const Direction& direction, DrawingProxy& drawingProxy,
         const BulletSpriteManager& bulletSpriteManager);
  void resolveCollision(GameObject& target) override;
  StaticDrawingComponent& getDrawingComponent() const override;
  void update();

 private:
  std::unique_ptr<StaticDrawingComponent> _drawingComponent;
};
