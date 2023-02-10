#include "Direction.hh"

#include "Vect2D.hh"

Direction::Direction(const Vect2D& vect) {
  this->_x = 0;
  this->_y = 0;

  if (vect.x > 0) {
    this->_x = 1;
  } else if (vect.x < 0) {
    this->_x = -1;
  }

  if (vect.y > 0) {
    this->_y = -1;
  } else if (vect.y < 0) {
    this->_y = -1;
  }
}
int Direction::getX() const { return this->_x; }
int Direction::getY() const { return this->_y; }
std::string Direction::toString() const {
  return std::string("Direction{x=") + std::to_string(this->_x) + std::string(",y=") + std::to_string(this->_y) +
         std::string(")");
}

Direction Direction::operator+(const Direction& dir) const { return Direction(this->_x + dir._x, this->_y + dir._y); }
bool Direction::operator==(const Direction& dir) const { return (this->_x == dir._x) && (this->_y == dir._y); }
bool Direction::operator!=(const Direction& dir) const { return !(*this == dir); }
