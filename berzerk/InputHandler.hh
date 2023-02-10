#pragma once

#include <SDL2/SDL.h>

#include "Vect2D.hh"

// Fwd decl
class Direction;

class InputHandler {
 public:
  bool pausePressed() const;
  bool gotSDLQuit() const;
  bool escapePressed() const;
  bool upArrowPressed() const;
  bool downArrowPressed() const;
  bool leftArrowPressed() const;
  bool rightArrowPressed() const;
  bool spacePressed() const;

  bool movementKeysPressed() const;
  bool noHorizontalKeysPressed() const;
  bool bothHorizontalKeysPressed() const;
  bool noVerticalKeysPressed() const;
  bool bothVerticalKeysPressed() const;
  bool shouldQuit() const;
  Direction getArrowKeyVerticalDirection() const;
  Direction getArrowKeyHorizontalDirection() const;
  Direction getArrowKeyDirection() const;

  void getKeyboardInput();

 private:
  bool _pausePressed = false;
  bool _gotSDLQuit = false;
  bool _escapePressed = false;
  bool _upArrowPressed = false;
  bool _downArrowPressed = false;
  bool _leftArrowPressed = false;
  bool _rightArrowPressed = false;
  bool _spacePressed = false;

  void keyboardEventHandler(const Uint32 eventType, const SDL_Keycode keycode);
};
