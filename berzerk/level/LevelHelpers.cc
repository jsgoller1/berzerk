#include "LevelHelpers.hh"

#include "Color.hh"
#include "Configs.hh"
#include "Vect2D.hh"

Color getLevelColor(const int levelNo) {
  switch (levelNo) {
    case 0:
      return Color::Mustard();
    case 1:
      return Color::Red();
    case 2:
      return Color::Cobalt();
    case 3:
      return Color::Green();
    case 4:
      return Color::Magenta();
    case 5:
      return Color::Yellow();
    case 6:
      return Color::White();
    case 7:
      return Color::Pink();
    case 8:
      return Color::Gray();
    case 9:
      return Color::Teal();
  }
  return Color::Orange();
}

Vect2D getCellCenter(const int cellId) {
  if (cellId < 0 || cellId > 14) {
    return Vect2D::zero();
  }

  Vect2D center = CELL_0_CENTER;
  center.x += (cellId % 5) * HORIZONTAL_WALL_WIDTH;
  center.y -= (cellId / 5) * VERTICAL_WALL_HEIGHT;
  return center;
}
