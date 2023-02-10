#pragma once

#include "SpriteManager.hh"

// Fwd decl
class Sprite;

class LevelSpriteManager : public SpriteManager {
 public:
  LevelSpriteManager(const std::string& assetsDirPath);
  std::shared_ptr<Sprite> horizontalBorderWall() const;
  std::shared_ptr<Sprite> verticalBorderWall() const;
  std::shared_ptr<Sprite> horizontalInternalWall() const;
  std::shared_ptr<Sprite> verticalInternalWall() const;
  std::shared_ptr<Sprite> horizontalExitWall() const;
  std::shared_ptr<Sprite> verticalExitWall() const;
};
