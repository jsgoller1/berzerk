#include "Screen.hh"

#include <iostream>
#include <memory>

#include "SDL2/SDL_image.h"
#include "SDL2/SDL_mixer.h"
#include "Sprite.hh"
#include "Vect2D.hh"

Screen::Screen(const int width, const int height) : _width(width), _height(height) {
  this->_screenDrawingProxy = std::unique_ptr<ScreenDrawingProxy>(new ScreenDrawingProxy(*this));

  // TODO: Some of the SDL initialization we do here involves sound, so it doesn't really belong with Screen. Fine for
  // now.

  // Initialize SDL and window
  if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0) {
    throw;
  }
  this->_window = SDL_CreateWindow("Berzerk", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, this->_width,
                                   this->_height, SDL_WINDOW_SHOWN);
  if (this->_window == nullptr) {
    throw;
  }

  // Initialize renderer
  Uint32 flags = SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC;
  int windowDriverIndex = -1;
  this->_renderer = (SDL_CreateRenderer(this->_window, windowDriverIndex, flags));
  if (this->_renderer == nullptr) {
    throw;
  }

  // Initialize PNG loading
  if (!(IMG_Init(IMG_INIT_PNG))) {
    printf("SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError());
    throw;
  }

  // Initialize SDL_mixer
  int frequency = 44100;
  int stereoChannelsCount = 2;
  int sampleSize = 2048;
  if (Mix_OpenAudio(frequency, MIX_DEFAULT_FORMAT, stereoChannelsCount, sampleSize) < 0) {
    printf("SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError());
    throw;
  }
}

Screen::~Screen() {
  SDL_DestroyWindow(this->_window);
  Mix_Quit();
  IMG_Quit();
  SDL_Quit();
}

Screen::ScreenDrawingProxy::ScreenDrawingProxy(Screen& screen) : _screen(screen) {}

void Screen::ScreenDrawingProxy::draw(const Vect2D& center, const int width, const int height,
                                      std::shared_ptr<Sprite> pixelData) {
  // Proxy users don't need to know this, but technically ScreenDrawingProxy::draw just sends pixel data to
  // SDL for drawing; SDL draws everything at once when the screen is updated.
  this->_screen.prepare(center, height, width, pixelData);
}

void Screen::prepare(const Vect2D& center, const int height, const int width, std::shared_ptr<Sprite> sprite) {
  Vect2D drawPoint = this->toScreenCoordinates(this->getDrawPoint(center, height, width));

  SDL_Rect renderQuad = {drawPoint.x, drawPoint.y, width, height};
  SDL_Rect* clip = sprite->getClipRectangle();
  double angle = 0.0;
  SDL_RendererFlip flip = SDL_FLIP_NONE;
  SDL_Point sdlCenter = SDL_Point{.x = drawPoint.x, .y = drawPoint.y};
  SDL_Texture* texture = SDL_CreateTextureFromSurface(this->_renderer, sprite->getSpriteSheet());
  SDL_SetTextureColorMod(texture, sprite->getColorMask().getRed(), sprite->getColorMask().getGreen(),
                         sprite->getColorMask().getBlue());
  if (SDL_RenderCopyEx(this->_renderer, texture, clip, &renderQuad, angle, &sdlCenter, flip)) {
    std::cout << "Couldn't draw texture" << std::endl;
    this->printSDLError();
  }
  SDL_DestroyTexture(texture);
}

void Screen::render() { SDL_RenderPresent(this->_renderer); }
void Screen::clear() { SDL_RenderClear(this->_renderer); }

int Screen::getHeight() const { return this->_height; }
int Screen::getWidth() const { return this->_width; }

Vect2D Screen::getTopLeft() const { return Vect2D{0, 0}; }
Screen::ScreenDrawingProxy& Screen::getScreenDrawingProxy() const { return *this->_screenDrawingProxy; }

Vect2D Screen::getDrawPoint(const Vect2D& center, const int height, const int width) const {
  // Get the specific point SDL should use for drawing; SDL treats
  // this as the top left of the image and draws from there. We do not
  // need to account for other SDL specifics here (i.e. y-axis flip or top left
  // corner.)

  return Vect2D(center.x - width / 2, center.y + height / 2);
}

Vect2D Screen::toScreenCoordinates(const Vect2D& vect) const {
  /*
   * SDL: (0,0) is the upper left of the display, (ScreenWidth, ScreenHeight) is
   * the bottom right. (100,100) is beneath (100,0)
   * Game world: (0,0) is the center of the screen. (100,100) is above (100,0).
   * To translate from game world to SDL, invert the Y coordinates, and move
   * everything by (ScreenWidth/2, ScreenHeight/2).
   */

  Vect2D screenCoords = Vect2D(vect);
  screenCoords.y = screenCoords.y - (this->_height / 2);
  screenCoords.x = screenCoords.x + (this->_width / 2);
  screenCoords.y = screenCoords.y * -1;
  return screenCoords;
}

Vect2D Screen::toWorldCoordinates(const Vect2D& vect) const {
  Vect2D worldCoords = Vect2D(vect);
  worldCoords.y = worldCoords.y * -1;
  worldCoords.x = worldCoords.x - (this->_width / 2);
  worldCoords.y = worldCoords.y + (this->_height / 2);
  return worldCoords;
}

void Screen::printSDLError() {
  std::string error = std::string(SDL_GetError());
  std::cout << "SDL Error message: " << error << std::endl;
  SDL_ClearError();
}
