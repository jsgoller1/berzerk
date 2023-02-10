#pragma once

#include "SpriteManager.hh"

class TextSpriteManager : public SpriteManager {
 public:
  TextSpriteManager(const std::string& assetsDirPath);

  std::shared_ptr<Sprite> digit(const int digit) const;
  std::shared_ptr<Sprite> man() const;
};
