#pragma once

#include "Color.hh"
#include "SpriteManager.hh"

// Fwd decl
class Sprite;

class BulletSpriteManager : public SpriteManager {
 public:
  BulletSpriteManager(const std::string& assetsDirPath);

  std::shared_ptr<Sprite> bulletVertical() const;
  std::shared_ptr<Sprite> bulletHorizontal() const;
  std::shared_ptr<Sprite> bulletNE() const;
  std::shared_ptr<Sprite> bulletSE() const;
};
