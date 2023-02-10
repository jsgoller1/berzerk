#pragma once

#include "SpriteManager.hh"

class PlayerSpriteManager : public SpriteManager {
 public:
  PlayerSpriteManager(const std::string& assetsDirPath);

  std::shared_ptr<Sprite> idle() const;
  // NOTE: Player uses west-facing movement animation for all movemement except east-movement
  std::shared_ptr<Sprite> movingE(const int frameNo) const;
  std::shared_ptr<Sprite> movingW(const int frameNo) const;
  std::shared_ptr<Sprite> shootingN() const;
  std::shared_ptr<Sprite> shootingE() const;
  std::shared_ptr<Sprite> shootingS() const;
  std::shared_ptr<Sprite> shootingW() const;
  std::shared_ptr<Sprite> shootingNE() const;
  std::shared_ptr<Sprite> shootingSE() const;
  std::shared_ptr<Sprite> shootingNW() const;
  std::shared_ptr<Sprite> shootingSW() const;
  std::shared_ptr<Sprite> dying(const int frameNo) const;
  std::shared_ptr<Sprite> dead() const;
};
