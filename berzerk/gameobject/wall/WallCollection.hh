#pragma once

#include <memory>
#include <vector>

#include "GameObjectCollection.hh"
#include "Wall.hh"
#include "WallCollisionProxy.hh"

// Fwd decl
class DrawingProxy;
class LevelSpriteManager;

class WallCollection : public GameObjectCollection {
 public:
  WallCollection(const std::vector<int> internalWallIndices, const LevelSpriteManager& levelSpriteManager,
                 DrawingProxy& drawingProxy);
  Wall* get(const size_t index) const override;
  size_t size() const override;

  const WallCollisionProxy& getWallCollisionProxy() const;

 private:
  std::vector<std::unique_ptr<Wall>> _walls;
  WallCollisionProxy _wallCollisionProxy;
};
