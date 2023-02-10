#include "Vect2D.hh"

#include <cmath>

#include "Direction.hh"

Vect2D::Vect2D(const int x, const int y) : x(x), y(y) {}

Vect2D::Vect2D(const Direction& direction) : x(direction.getX()), y(direction.getY()) {}

bool Vect2D::above(const Vect2D& other) { return this->y > other.y; }
bool Vect2D::below(const Vect2D& other) { return this->y < other.y; }
bool Vect2D::left(const Vect2D& other) { return this->x < other.x; }
bool Vect2D::right(const Vect2D& other) { return this->x > other.x; }

Vect2D Vect2D::operator+(const Vect2D& vect) const { return Vect2D(this->x + vect.x, this->y + vect.y); }

void Vect2D::operator+=(const Vect2D& vect) {
  this->x += vect.x;
  this->y += vect.y;
}

Vect2D Vect2D::operator-(const Vect2D& vect) const {
  // Implements vector subtraction
  // -: R^2 X R^2 -> R^2
  return Vect2D(this->x - vect.x, this->y - vect.y);
}

void Vect2D::operator-=(const Vect2D& vect) {
  // Implements vector subtraction and assignment
  this->x -= vect.x;
  this->y -= vect.y;
}

bool Vect2D::operator==(const Vect2D& vect) const { return this->x == vect.x && this->y == vect.y; }

Vect2D Vect2D::operator*(const int scalar) const { return Vect2D(this->x * scalar, this->y * scalar); }

bool Vect2D::operator<(const Vect2D& vect) const { return this->x < vect.x || this->y < vect.y; }

int Vect2D::distance(const Vect2D& other) {
  int xDist = this->x - other.x;
  int yDist = this->y - other.y;
  return int(sqrt(double(xDist * xDist) + (yDist * yDist)));
}
