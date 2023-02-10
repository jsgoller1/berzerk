#pragma once

#include <memory>

#include "Configs.hh"
#include "DrawingProxy.hh"
#include "SDL2/SDL.h"

// Forward decl
class Vect2D;
class Sprite;

class Screen {
 public:
  Screen(const int width, const int height);
  ~Screen();

  int getHeight() const;
  int getWidth() const;
  Vect2D getTopLeft() const;

  Vect2D toScreenCoordinates(const Vect2D& center) const;
  Vect2D toWorldCoordinates(const Vect2D& vect) const;

  void render();
  void clear();

  class ScreenDrawingProxy : public DrawingProxy {
   public:
    ScreenDrawingProxy(Screen& screen);
    void draw(const Vect2D& center, const int width, const int height, std::shared_ptr<Sprite> pixelData) override;

   private:
    Screen& _screen;
  };
  ScreenDrawingProxy& getScreenDrawingProxy() const;

 private:
  int _width;
  int _height;
  SDL_Window* _window;
  SDL_Renderer* _renderer;
  std::unique_ptr<ScreenDrawingProxy> _screenDrawingProxy;

  void prepare(const Vect2D& center, const int height, const int width, std::shared_ptr<Sprite> texture);

  Vect2D getDrawPoint(const Vect2D& center, const int height, const int width) const;
  void printSDLError();
};
