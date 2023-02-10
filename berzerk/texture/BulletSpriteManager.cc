#include "BulletSpriteManager.hh"

#include "Configs.hh"
#include "Sprite.hh"

BulletSpriteManager::BulletSpriteManager(const std::string& assetsDirPath)
    : SpriteManager(assetsDirPath + BULLET_SPRITE_SHEET_PATH, TOP_LEFT, BULLET_SPRITE_WIDTH_PX, BULLET_SPRITE_HEIGHT_PX,
                    BULLET_SPRITE_BOUNDARY_WIDTH_PX) {}

std::shared_ptr<Sprite> BulletSpriteManager::bulletHorizontal() const { return this->getSprite(0, 0); }
std::shared_ptr<Sprite> BulletSpriteManager::bulletSE() const { return this->getSprite(0, 1); }

std::shared_ptr<Sprite> BulletSpriteManager::bulletVertical() const { return this->getSprite(0, 2); }
std::shared_ptr<Sprite> BulletSpriteManager::bulletNE() const { return this->getSprite(0, 3); }
