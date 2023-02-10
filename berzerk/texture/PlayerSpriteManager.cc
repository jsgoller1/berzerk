#include "PlayerSpriteManager.hh"

#include <iostream>

#include "Configs.hh"
#include "Vect2D.hh"

PlayerSpriteManager::PlayerSpriteManager(const std::string& assetsDirPath)
    : SpriteManager(assetsDirPath + PLAYER_SPRITE_SHEET_PATH, TOP_LEFT, PLAYER_SPRITE_WIDTH_PX, PLAYER_SPRITE_HEIGHT_PX,
                    PLAYER_SPRITE_BOUNDARY_WIDTH_PX) {}

std::shared_ptr<Sprite> PlayerSpriteManager::idle() const { return this->getSprite(0, 0); }

std::shared_ptr<Sprite> PlayerSpriteManager::movingE(const int frameNo) const {
  return this->getSprite(0, 1 + frameNo);
}
std::shared_ptr<Sprite> PlayerSpriteManager::movingW(const int frameNo) const {
  return this->getSprite(1, 1 + frameNo);
}

// NOTE: These are intentionally ordered differently than in the header file to coincide
// with how they appear on the spritesheet
std::shared_ptr<Sprite> PlayerSpriteManager::shootingNE() const { return this->getSprite(2, 0); }
std::shared_ptr<Sprite> PlayerSpriteManager::shootingE() const { return this->getSprite(2, 1); }
std::shared_ptr<Sprite> PlayerSpriteManager::shootingSE() const { return this->getSprite(2, 2); }
std::shared_ptr<Sprite> PlayerSpriteManager::shootingS() const { return this->getSprite(2, 3); }
std::shared_ptr<Sprite> PlayerSpriteManager::shootingSW() const { return this->getSprite(3, 0); }
std::shared_ptr<Sprite> PlayerSpriteManager::shootingW() const { return this->getSprite(3, 1); }
std::shared_ptr<Sprite> PlayerSpriteManager::shootingNW() const { return this->getSprite(2, 3); }
std::shared_ptr<Sprite> PlayerSpriteManager::shootingN() const { return this->getSprite(3, 3); }

std::shared_ptr<Sprite> PlayerSpriteManager::dying(const int frameNo) const {
  // NOTE: Technically, the sprites for dying are 1px taller (height) than the character sprites. We ignore this though
  // and are fine with chopping off the bottom 1px (no one will notice/care since they transition so quickly).
  // NOTE: the first 4 frames are on line 4 of the sprite sheet, and the second 4 are on line 5
  return this->getSprite((frameNo < 3 ? 4 : 5), frameNo % 4);
}

std::shared_ptr<Sprite> PlayerSpriteManager::dead() const { return this->getSprite(1, 0); }
