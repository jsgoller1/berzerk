#pragma once

#include "SpriteManager.hh"

class RobotSpriteManager : public SpriteManager {
 public:
  RobotSpriteManager(const std::string& assetsDirPath);

  std::shared_ptr<Sprite> idle(const int frameNo) const;
  std::shared_ptr<Sprite> movingN(const int frameNo) const;
  std::shared_ptr<Sprite> movingS(const int frameNo) const;
  std::shared_ptr<Sprite> movingE(const int frameNo) const;
  std::shared_ptr<Sprite> movingW(const int frameNo) const;
  std::shared_ptr<Sprite> dying(const int frameNo) const;
  std::shared_ptr<Sprite> dead() const;

  std::shared_ptr<Sprite> shootingN() const;
  std::shared_ptr<Sprite> shootingE() const;
  std::shared_ptr<Sprite> shootingS() const;
  std::shared_ptr<Sprite> shootingW() const;
  std::shared_ptr<Sprite> shootingNE() const;  // calls shootingE()
  std::shared_ptr<Sprite> shootingSE() const;  // calls shootingE()
  std::shared_ptr<Sprite> shootingNW() const;  // calls shootingW()
  std::shared_ptr<Sprite> shootingSW() const;  // calls shootingW()
};
