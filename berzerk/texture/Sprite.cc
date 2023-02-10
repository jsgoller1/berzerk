#include "Sprite.hh"

Sprite::Sprite(SDL_Surface* spriteSheet, const int clipX, const int clipY, const int clipWidth, const int clipHeight,
               const Color colorMask)
    : _spriteSheet(spriteSheet),
      _clipRectangle(std::unique_ptr<SDL_Rect>(new SDL_Rect{clipX, clipY, clipWidth, clipHeight})),
      _colorMask(colorMask) {}

SDL_Surface* Sprite::getSpriteSheet() const { return this->_spriteSheet; }

SDL_Rect* Sprite::getClipRectangle() const { return this->_clipRectangle.get(); }

Color Sprite::getColorMask() const { return this->_colorMask; }
void Sprite::setColorMask(const Color& colorMask) { this->_colorMask = colorMask; }
