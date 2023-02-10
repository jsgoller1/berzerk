#include "OttoSpriteManager.hh"

#include "Configs.hh"

OttoSpriteManager::OttoSpriteManager(const std::string& assetsDirPath)
    : SpriteManager(assetsDirPath + OTTO_SPRITE_SHEET_PATH, TOP_LEFT, OTTO_SPRITE_WIDTH_PX, OTTO_SPRITE_HEIGHT_PX,
                    OTTO_SPRITE_BOUNDARY_WIDTH_PX) {}

std::shared_ptr<Sprite> OttoSpriteManager::spawning(const int frameNo) const { return this->getSprite(0, frameNo); }

std::shared_ptr<Sprite> OttoSpriteManager::chasing() const {
  // NOTE: The bouncing animation is implemented by just using the squash face (frame 6) for landing, then the normal
  // face (frame 7) for everything else. We implement the bouncing with a positional offset rather than sprites so we
  // can more precisely handle collisions.
  return this->getSprite(0, 7);
}
