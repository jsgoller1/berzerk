#pragma once

#include <memory>

#include "Configs.hh"
#include "GameObject.hh"
#include "LevelSpriteManager.hh"
#include "Screen.hh"
#include "StaticDrawingComponent.hh"

class Wall : public GameObject {
 public:
  Wall(const int wallIndex, const LevelSpriteManager& levelSpriteManager, DrawingProxy& drawingProxy);
  void resolveCollision(GameObject& target) override;
  StaticDrawingComponent& getDrawingComponent() const override;
  int getWallIndex() const;

 private:
  const int _wallIndex;
  std::unique_ptr<StaticDrawingComponent> _drawingComponent;
};

Vect2D getWallPosition(unsigned wallIndex);
Vect2D getHorizontalWallPosition(const unsigned wallIndex);
Vect2D getVerticalWallPosition(const unsigned wallIndex);
