#include "TextSpriteManager.hh"

#include "Configs.hh"

TextSpriteManager::TextSpriteManager(const std::string& assetsDirPath)
    : SpriteManager(assetsDirPath + TEXT_SPRITE_SHEET_PATH, TOP_LEFT, TEXT_SPRITE_WIDTH_PX, TEXT_SPRITE_HEIGHT_PX,
                    TEXT_SPRITE_BOUNDARY_WIDTH_PX, Color::Green()) {}

std::shared_ptr<Sprite> TextSpriteManager::digit(const int digit) const {
  if (digit < 0 || 9 < digit) {
    return this->getSprite(0, 0);
  }
  return this->getSprite(0, digit);
}

std::shared_ptr<Sprite> TextSpriteManager::man() const { return this->getSprite(0, 10); }
