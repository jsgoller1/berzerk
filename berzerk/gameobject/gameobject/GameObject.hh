#pragma once

#include <memory>

#include "PositionComponent.hh"
#include "SDL2/SDL.h"
#include "Vect2D.hh"

// Forward decls
class Direction;
class DrawingComponent;
class DrawingProxy;
class SpriteManager;
class Sprite;

/*
 * TODO: for now, we're just going to bloat GameObject with animation, collision, drawing, and movement behavior. Once
 * we figure out exactly "what needs to know what" (each of those need to know about the object's position, for
 * instance), we'll split them off into separate interface objects. Anything of these sub-behaviors that require
 * specific attributes to be initialized should have their own init method, which we will later use for the interface
 * object constructor.
 */

class GameObject {
 public:
  GameObject(const Vect2D& position, const Vect2D& velocity);
  virtual ~GameObject();
  Vect2D getPosition() const;
  void setPosition(const Vect2D& position);
  PositionComponent& getPositionComponent() const;
  virtual DrawingComponent& getDrawingComponent() const = 0;

  // IMovement
  void IMovementCtor(const Vect2D& velocity);
  virtual Vect2D getVelocity() const;
  virtual void setVelocity(const Vect2D& velocity);
  void move();

  // ICollision
  // virtual ~ICollision();

  bool collisionTest(const GameObject& target, const Vect2D usOffset = Vect2D::zero(),
                     const Vect2D themOffset = Vect2D::zero()) const;
  virtual void resolveCollision(GameObject& target) = 0;

  // Other
  bool getShouldRemove() const;
  void setShouldRemove(const bool setting);

 private:
  bool _shouldRemove = false;
  std::unique_ptr<PositionComponent> _positionComponent;
  Vect2D _velocity = Vect2D::zero();
};
