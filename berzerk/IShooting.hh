#pragma once

#include "BulletSpriteManager.hh"
#include "LevelShootingProxy.hh"

// Fwd decl
class Color;
class Direction;
class Vect2D;

class IShooting {
 public:
  IShooting(LevelShootingProxy& shootingProxy);
  void shoot(const Direction& direction, const Vect2D& origin);

 private:
  // IShooting
  LevelShootingProxy& _shootingProxy;
};
