#include "WallCollection.hh"

#include "Wall.hh"
#include "WallCollisionProxy.hh"

WallCollection::WallCollection(const std::vector<int> wallIndices, const LevelSpriteManager& levelSpriteManager,
                               DrawingProxy& drawingProxy)
    : _walls(std::vector<std::unique_ptr<Wall>>()), _wallCollisionProxy(WallCollisionProxy(*this)) {
  for (int i : wallIndices) {
    this->_walls.push_back(std::unique_ptr<Wall>(new Wall(i, levelSpriteManager, drawingProxy)));
  }
}
Wall* WallCollection::get(const size_t index) const { return this->_walls.at(index).get(); }
size_t WallCollection::size() const { return this->_walls.size(); }

const WallCollisionProxy& WallCollection::getWallCollisionProxy() const { return this->_wallCollisionProxy; }
