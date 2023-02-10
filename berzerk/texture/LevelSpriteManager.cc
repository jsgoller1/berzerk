#include "LevelSpriteManager.hh"

#include "Configs.hh"
#include "Sprite.hh"

// TODO: Since the level sprite sheet is not a grid like the others, we implement this differently and
// directly give the coordinates on the spritesheet for the sections we want to pull (rather than using getSprite)
// TODO: Let's just modify the sprite sheets so we can use a consistent interface
LevelSpriteManager::LevelSpriteManager(const std::string& assetsDirPath)
    : SpriteManager(assetsDirPath + LEVEL_SPRITE_SHEET_PATH, Vect2D::zero(), 0, 0, 0) {}
std::shared_ptr<Sprite> LevelSpriteManager::horizontalBorderWall() const {
  // 19,8 is the top left corner
  int topLeftX = 19;
  int topLeftY = 8;
  int wallWidth = 54;
  int wallHeight = 4;
  return std::make_shared<Sprite>(this->getSpriteSheet(), topLeftX, topLeftY, wallWidth, wallHeight);
}
std::shared_ptr<Sprite> LevelSpriteManager::verticalBorderWall() const {
  // 19,8 is the top left corner
  int topLeftX = 19;
  int topLeftY = 8;
  int wallWidth = 4;
  int wallHeight = 54;
  return std::make_shared<Sprite>(this->getSpriteSheet(), topLeftX, topLeftY, wallWidth, wallHeight);
}
std::shared_ptr<Sprite> LevelSpriteManager::horizontalInternalWall() const {
  // 19,8 is the top left corner
  int topLeftX = 24;
  int topLeftY = 75;
  int wallWidth = 44;  // -10 px; This prevents grabbing the little dark blue box in the middle
  int wallHeight = 4;
  return std::make_shared<Sprite>(this->getSpriteSheet(), topLeftX, topLeftY, wallWidth, wallHeight);
}
std::shared_ptr<Sprite> LevelSpriteManager::verticalInternalWall() const {
  // 19,8 is the top left corner
  int topLeftX = 72;
  int topLeftY = 12;
  int wallWidth = 4;
  int wallHeight = 54;
  return std::make_shared<Sprite>(this->getSpriteSheet(), topLeftX, topLeftY, wallWidth, wallHeight);
}

// TODO: In the original game, the exit was the same color as the robots. This would create more work and virtually
// no benefit, so I don't care that it's the same as all other walls for now.
std::shared_ptr<Sprite> LevelSpriteManager::horizontalExitWall() const { return this->horizontalBorderWall(); }
std::shared_ptr<Sprite> LevelSpriteManager::verticalExitWall() const { return this->verticalBorderWall(); }
