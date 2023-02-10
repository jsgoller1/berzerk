#pragma once

#include "Vect2D.hh"

class PositionComponent {
 public:
  PositionComponent(const Vect2D& position);
  Vect2D getPosition() const;
  void setPosition(const Vect2D& position);
  void updatePosition(const Vect2D& delta);

 private:
  Vect2D _position;
};
