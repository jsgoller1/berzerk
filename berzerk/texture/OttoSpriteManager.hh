#pragma once

#include "SpriteManager.hh"

class OttoSpriteManager : public SpriteManager {
 public:
  OttoSpriteManager(const std::string& assetsDirPath);

  std::shared_ptr<Sprite> spawning(const int frameNo) const;
  std::shared_ptr<Sprite> chasing() const;
};
