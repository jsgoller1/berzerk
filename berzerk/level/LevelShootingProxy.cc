#include "LevelShootingProxy.hh"

#include <iostream>

#include "Bullet.hh"
#include "Color.hh"
#include "Direction.hh"
#include "DrawingProxy.hh"
#include "Vect2D.hh"

LevelShootingProxy::LevelShootingProxy(BulletCollection& levelBullets) : _levelBullets(levelBullets) {}

void LevelShootingProxy::shoot(const Direction& direction, const Vect2D& origin) const {
  this->_levelBullets.createAt(direction, origin);
}
