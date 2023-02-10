#include "Wall.hh"

#include "SpriteManager.hh"
#include "Vect2D.hh"

Wall::Wall(const int wallIndex, const LevelSpriteManager& levelSpriteManager, DrawingProxy& drawingProxy)
    : GameObject(getWallPosition((unsigned)wallIndex), Vect2D::zero()), _wallIndex(wallIndex) {
  int height, width;
  std::shared_ptr<Sprite> sprite;

  if (HORIZONTAL_BORDER_WALLS.find(wallIndex) != HORIZONTAL_BORDER_WALLS.end()) {
    height = HORIZONTAL_WALL_HEIGHT;
    width = HORIZONTAL_WALL_WIDTH;
    sprite = levelSpriteManager.horizontalBorderWall();
  } else if (VERTICAL_BORDER_WALLS.find(wallIndex) != VERTICAL_BORDER_WALLS.end()) {
    height = VERTICAL_WALL_HEIGHT;
    width = VERTICAL_WALL_WIDTH;
    sprite = levelSpriteManager.verticalBorderWall();
  } else if (HORIZONTAL_INTERNAL_WALLS.find(wallIndex) != HORIZONTAL_INTERNAL_WALLS.end()) {
    height = HORIZONTAL_WALL_HEIGHT;
    width = HORIZONTAL_WALL_WIDTH;
    sprite = levelSpriteManager.horizontalInternalWall();
  } else if (VERTICAL_INTERNAL_WALLS.find(wallIndex) != VERTICAL_INTERNAL_WALLS.end()) {
    height = VERTICAL_WALL_HEIGHT;
    width = VERTICAL_WALL_WIDTH;
    sprite = levelSpriteManager.verticalInternalWall();
  } else if (HORIZONTAL_EXIT_WALLS.find(wallIndex) != HORIZONTAL_EXIT_WALLS.end()) {
    height = HORIZONTAL_WALL_HEIGHT;
    width = HORIZONTAL_WALL_WIDTH;
    sprite = levelSpriteManager.horizontalExitWall();
  } else {  // VERTICAL_EXIT_WALLS.find(wallIndex) != VERTICAL_EXIT_WALLS.end())
    height = VERTICAL_WALL_HEIGHT;
    width = VERTICAL_WALL_WIDTH;
    sprite = levelSpriteManager.verticalExitWall();
  }

  this->_drawingComponent = std::unique_ptr<StaticDrawingComponent>(
      new StaticDrawingComponent(this->getPositionComponent(), height, width, drawingProxy, sprite));
}

void Wall::resolveCollision(GameObject& target) {
  // We actually don't need to do anything when something collides with us; anything colliding with a wall dies
  // painfully (except EvilOtto)
  // TODO: This means then that not every GameObject needs to have collision resolution behavior.
  (void)target;
};

StaticDrawingComponent& Wall::getDrawingComponent() const { return *this->_drawingComponent; }

int Wall::getWallIndex() const { return this->_wallIndex; }

Vect2D getWallPosition(const unsigned wallIndex) {
  return (wallIndex < 20) ? getHorizontalWallPosition(wallIndex) : getVerticalWallPosition(wallIndex);
}

Vect2D getHorizontalWallPosition(const unsigned wallIndex) {
  // The top left corner of the topmost leftmost wall is at (-SCREEN_WIDTH/2, SCREEN_HEIGHT/2), so
  // it's center is offset from that by (wall width / 2, wall height / 2).
  int x = (-INTERNAL_PLAY_AREA_WIDTH / 2) + (HORIZONTAL_WALL_WIDTH / 2);
  // Then for each wall in the sequence, the horizontal offset is multiplied by (wallIndex % 5)
  x += HORIZONTAL_WALL_WIDTH * (wallIndex % 5);

  // For the vertical offset, horizontal walls of each row need to have vertical wall height distance between them
  int y = (INTERNAL_PLAY_AREA_HEIGHT / 2) - (HORIZONTAL_WALL_HEIGHT / 2);
  y -= (VERTICAL_WALL_HEIGHT) * (wallIndex / 5);
  // Correct positioning for wall 0 should be (-550, 395)
  return Vect2D(x, y);
}

Vect2D getVerticalWallPosition(const unsigned wallIndex) {
  // The top left corner of the topmost leftmost wall is at (-SCREEN_WIDTH/2, SCREEN_HEIGHT/2), so
  // it's center is offset from that by (wall width / 2, wall height / 2).
  int x = (-INTERNAL_PLAY_AREA_WIDTH / 2) + (VERTICAL_WALL_WIDTH / 2);
  // Then for each wall in the sequence, the horizontal offset is multiplied by (wallIndex % 6)
  x += HORIZONTAL_WALL_WIDTH * ((wallIndex % 20) % 6);

  // For the vertical offset, vertical walls of each row need to have vertical wall height distance between them
  int y = (INTERNAL_PLAY_AREA_HEIGHT / 2) - (VERTICAL_WALL_HEIGHT / 2);
  y -= VERTICAL_WALL_HEIGHT * ((wallIndex % 20) / 6);
  return Vect2D(x, y);
}
