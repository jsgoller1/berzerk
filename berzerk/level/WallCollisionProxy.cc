#include "WallCollisionProxy.hh"

#include "WallCollection.hh"

WallCollisionProxy::WallCollisionProxy(const WallCollection& walls) : _walls(walls) {}

bool WallCollisionProxy::test(const GameObject& source, const Vect2D& sourceOffset) const {
  for (size_t i = 0; i < this->_walls.size(); i++) {
    Wall* wall = this->_walls.get(i);
    if (source.collisionTest(*wall, sourceOffset)) {
      return true;
    }
  }
  return false;
}
