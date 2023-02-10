#pragma once

// Fwd decls
class Direction;
class Player;
class Vect2D;

class PlayerPositionProxy {
 public:
  PlayerPositionProxy(const Player& player);
  Vect2D getPlayerPosition() const;
  Vect2D distanceToPlayer(const Vect2D& currentPosition) const;
  Direction lineScan(const Vect2D& currentPosition, const int errorMargin = 0) const;

 private:
  const Player& _player;
};
