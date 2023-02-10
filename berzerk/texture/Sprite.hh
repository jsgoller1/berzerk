#pragma once

#include <SDL2/SDL.h>

#include <memory>

#include "Color.hh"

class Sprite {
 public:
  // This is a wrapper around the SDL_Surface type that can be used with smart pointers. Do not try to manually
  // delete it with SDL_FreeSurface(); call its destructor instead.

  Sprite(SDL_Surface* spriteSheet, const int clipX, const int clipY, const int clipWidth, const int clipHeight,
         const Color colorMask = Color::White());
  SDL_Surface* getSpriteSheet() const;
  SDL_Rect* getClipRectangle() const;

  Color getColorMask() const;
  void setColorMask(const Color& colorMask);

 private:
  SDL_Surface* _spriteSheet;
  std::unique_ptr<SDL_Rect> _clipRectangle;
  Color _colorMask = Color::White();
};
