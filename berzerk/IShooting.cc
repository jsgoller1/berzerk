#include "IShooting.hh"

#include "Configs.hh"
#include "Direction.hh"

IShooting::IShooting(LevelShootingProxy& shootingProxy) : _shootingProxy(shootingProxy) {}

void IShooting::shoot(const Direction& direction, const Vect2D& origin) {
  // NOTE: If bullet spaws directly on player or robot, it will kill them instantly; we must spawn it at an offset
  // TODO:
  int offsetDistance = (direction == Direction::North() || direction == Direction::South())
                           ? BULLET_SPAWN_VERTICAL_OFFSET_DISTANCE_PX
                           : BULLET_SPAWN_HORIZONTAL_OFFSET_DISTANCE_PX;

  Vect2D offsetOrigin = origin + (Vect2D(direction) * offsetDistance);
  this->_shootingProxy.shoot(direction, offsetOrigin);
}
