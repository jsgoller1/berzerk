#pragma once
#include <memory>

#include "SDL2/SDL.h"

// Forward decls
class Direction;
class Vect2D;
class Sprite;

class DrawingProxy {
 public:
  virtual ~DrawingProxy();
  virtual void draw(const Vect2D& center, const int width, const int height,
                    std::shared_ptr<Sprite> surface) = 0;
};
