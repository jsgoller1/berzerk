#pragma once

#include <vector>

#include "DrawingProxy.hh"
#include "PositionComponent.hh"
#include "Vect2D.hh"

// fwd decls
class Sprite;
class SpriteManager;

class DrawingComponent {
 public:
  DrawingComponent(PositionComponent& _positionComponent, const int height, const int width,
                   DrawingProxy& drawingProxy);
  virtual ~DrawingComponent();
  int getHeight() const;
  void setHeight(const int height);
  int getWidth() const;
  void setWidth(const int width);
  Vect2D getTopLeft() const;
  DrawingProxy& getDrawingProxy() const;
  virtual void draw();
  virtual std::shared_ptr<Sprite> getCurrentSprite() const = 0;

 private:
  PositionComponent& _positionComponent;
  int _height;
  int _width;
  DrawingProxy& _drawingProxy;
};
