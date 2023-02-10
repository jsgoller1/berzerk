#pragma once

#include <string>

// fwd decl
class Vect2D;

constexpr int Y_NORTH = 1;
constexpr int Y_NONE = 0;
constexpr int Y_SOUTH = -1;
constexpr int X_WEST = -1;
constexpr int X_NONE = 0;
constexpr int X_EAST = 1;

class Direction {
 public:
  static Direction None() { return Direction(X_NONE, Y_NONE); }
  static Direction North() { return Direction(X_NONE, Y_NORTH); }
  static Direction South() { return Direction(X_NONE, Y_SOUTH); }
  static Direction East() { return Direction(X_EAST, Y_NONE); }
  static Direction West() { return Direction(X_WEST, Y_NONE); }
  static Direction NorthEast() { return Direction(X_EAST, Y_NORTH); }
  static Direction NorthWest() { return Direction(X_WEST, Y_NORTH); }
  static Direction SouthEast() { return Direction(X_EAST, Y_SOUTH); }
  static Direction SouthWest() { return Direction(X_WEST, Y_SOUTH); }
  Direction(const Vect2D& vect);
  int getX() const;
  int getY() const;
  std::string toString() const;

  Direction operator+(const Direction& other) const;
  bool operator==(const Direction& other) const;
  bool operator!=(const Direction& other) const;

 private:
  Direction(int x, int y) : _x(x), _y(y) {}
  int _x;
  int _y;
};
