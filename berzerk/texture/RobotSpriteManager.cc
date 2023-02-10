#include "RobotSpriteManager.hh"

#include "Configs.hh"

RobotSpriteManager::RobotSpriteManager(const std::string& assetsDirPath)
    : SpriteManager(assetsDirPath + ROBOT_SPRITE_SHEET_PATH, TOP_LEFT, ROBOT_SPRITE_WIDTH_PX, ROBOT_SPRITE_HEIGHT_PX,
                    ROBOT_SPRITE_BOUNDARY_WIDTH_PX) {}

std::shared_ptr<Sprite> RobotSpriteManager::idle(const int frameNo) const { return this->getSprite(0, frameNo); }

std::shared_ptr<Sprite> RobotSpriteManager::movingN(const int frameNo) const { return this->getSprite(2, 3 + frameNo); }
std::shared_ptr<Sprite> RobotSpriteManager::movingS(const int frameNo) const { return this->getSprite(2, frameNo); }
std::shared_ptr<Sprite> RobotSpriteManager::movingE(const int frameNo) const { return this->getSprite(1, frameNo); }
std::shared_ptr<Sprite> RobotSpriteManager::movingW(const int frameNo) const { return this->getSprite(1, 2 + frameNo); }
std::shared_ptr<Sprite> RobotSpriteManager::dying(const int frameNo) const {
  // The robot exploding sprites are slightly larger than the normal sprites, so
  // we need to grab them explicitly with coords on the sprite sheet
  Vect2D topLeft = Vect2D::zero();
  if (frameNo == 0) {
    topLeft = Vect2D(0, 40);
  } else if (frameNo == 1) {
    topLeft = Vect2D(16, 40);
  } else if (frameNo == 2) {
    topLeft = Vect2D(0, 56);
  } else if (frameNo == 3) {
    topLeft = Vect2D(16, 56);
  }
  return this->getSprite(topLeft, ROBOT_DYING_SPRITE_WIDTH_PX, ROBOT_DYING_SPRITE_HEIGHT_PX);
}
std::shared_ptr<Sprite> RobotSpriteManager::dead() const { return this->getSprite(4, 1); }

std::shared_ptr<Sprite> RobotSpriteManager::shootingN() const { return this->getSprite(0, 0); }
std::shared_ptr<Sprite> RobotSpriteManager::shootingE() const { return this->getSprite(1, 0); }
std::shared_ptr<Sprite> RobotSpriteManager::shootingS() const { return this->getSprite(0, 3); }
std::shared_ptr<Sprite> RobotSpriteManager::shootingW() const { return this->getSprite(1, 3); }
std::shared_ptr<Sprite> RobotSpriteManager::shootingNE() const { return this->shootingE(); }
std::shared_ptr<Sprite> RobotSpriteManager::shootingSE() const { return this->shootingE(); }
std::shared_ptr<Sprite> RobotSpriteManager::shootingNW() const { return this->shootingW(); }
std::shared_ptr<Sprite> RobotSpriteManager::shootingSW() const { return this->shootingW(); }
