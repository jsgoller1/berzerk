#pragma once

#include "Vect2D.hh"

// Fwd decl
class WallCollisionProxy;
class WallCollection;
class GameObject;

class WallCollisionProxy {
 public:
  WallCollisionProxy(const WallCollection& walls);
  bool test(const GameObject& source, const Vect2D& sourceOffset = Vect2D::zero()) const;

 private:
  const WallCollection& _walls;
};
