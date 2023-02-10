#include "PlayerPositionProxy.hh"

#include "Direction.hh"
#include "Math.hh"
#include "Player.hh"
#include "Vect2D.hh"

PlayerPositionProxy::PlayerPositionProxy(const Player& player) : _player(player) {}

Vect2D PlayerPositionProxy::getPlayerPosition() const { return this->_player.getPosition(); }

Direction PlayerPositionProxy::lineScan(const Vect2D& currentPosition, const int errorMargin) const {
  /*
  // If the slope is 1 or -1, then the absval of difference between our x and their x should be the same for our y and
  // their y. To allow for a margin of error (e.g. suppose we want to be OK with slopes ranging from 5/1 to 1/5), we can
  // then check that the difference between abs(us.x - them.x) and abs(us.y - them.y) is within the margin (e.g.
  // within 5).
  */

  Vect2D playerPosition = this->_player.getPosition();
  int xDifference = currentPosition.x - playerPosition.x;
  int yDifference = currentPosition.y - playerPosition.y;

  // N or S
  if (absval(xDifference) <= errorMargin) {
    return (currentPosition.y < playerPosition.y) ? Direction::North() : Direction::South();
  }

  // W or E
  else if (absval(yDifference) <= errorMargin) {
    return (currentPosition.x < playerPosition.x) ? Direction::East() : Direction::West();
  }

  /*
   * Diagonal shooting. Suppose we want strict diagonals only; then we'd mandate that the slope of the line drawn from
   * them to us is either 1 or -1. To allow for a margin of error, we might instead allow for slopes between 5/1 to 1/5.
   * This would include 2/3, 3/2, 4/1, 1/4, and 55/56, but not 6/1, 100/5, or 0/5. So if the absval of the difference of
   * the xDifference and yDifference is within our margin of error, then we can successfully shoot diagonally.
   */
  else if (abs(abs(xDifference) - abs(yDifference)) <= errorMargin) {
    Direction horizontal = (currentPosition.x < playerPosition.x) ? Direction::East() : Direction::West();
    Direction vertical = (currentPosition.y < playerPosition.y) ? Direction::North() : Direction::South();
    return horizontal + vertical;
  }

  // Otherwise, not on compass rose
  return Direction::None();
}
