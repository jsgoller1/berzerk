#include "InputHandler.hh"

#include "Direction.hh"

bool InputHandler::pausePressed() const { return this->_pausePressed; }
bool InputHandler::gotSDLQuit() const { return this->_gotSDLQuit; }
bool InputHandler::escapePressed() const { return this->_escapePressed; }
bool InputHandler::upArrowPressed() const { return this->_upArrowPressed; }
bool InputHandler::downArrowPressed() const { return this->_downArrowPressed; }
bool InputHandler::leftArrowPressed() const { return this->_leftArrowPressed; }
bool InputHandler::rightArrowPressed() const { return this->_rightArrowPressed; }
bool InputHandler::spacePressed() const { return this->_spacePressed; }
bool InputHandler::noHorizontalKeysPressed() const { return !this->_leftArrowPressed && !this->_rightArrowPressed; }
bool InputHandler::bothHorizontalKeysPressed() const { return this->_leftArrowPressed && this->_rightArrowPressed; }
bool InputHandler::noVerticalKeysPressed() const { return !this->_upArrowPressed && !this->_downArrowPressed; }
bool InputHandler::bothVerticalKeysPressed() const { return this->_upArrowPressed && this->_downArrowPressed; }
bool InputHandler::shouldQuit() const { return this->_escapePressed || this->_gotSDLQuit; }

Direction InputHandler::getArrowKeyVerticalDirection() const {
  if (this->bothVerticalKeysPressed() || this->noVerticalKeysPressed()) {
    return Direction::None();
  } else if (this->upArrowPressed()) {
    return Direction::North();
  } else {
    return Direction::South();
  }
}

Direction InputHandler::getArrowKeyHorizontalDirection() const {
  if (this->bothHorizontalKeysPressed() || this->noHorizontalKeysPressed()) {
    return Direction::None();
  } else if (this->leftArrowPressed()) {
    return Direction::West();
  } else {
    return Direction::East();
  }
}

Direction InputHandler::getArrowKeyDirection() const {
  return this->getArrowKeyVerticalDirection() + this->getArrowKeyHorizontalDirection();
}

bool InputHandler::movementKeysPressed() const {
  return this->_upArrowPressed || this->_downArrowPressed || this->_leftArrowPressed || this->_rightArrowPressed;
}

void InputHandler::getKeyboardInput() {
  SDL_Event event;
  while (SDL_PollEvent(&event) != 0) {
    if (event.type == SDL_QUIT) {
      this->_gotSDLQuit = true;
    } else if (event.type == SDL_KEYDOWN || event.type == SDL_KEYUP) {
      keyboardEventHandler(event.type, event.key.keysym.sym);
    }
  }

  // DEBUG: This is just a hack for generating input while debugging.
  // this->_rightArrowPressed = true;
}

void InputHandler::keyboardEventHandler(const Uint32 eventType, const SDL_Keycode keycode) {
  bool setting = (eventType == SDL_KEYDOWN) ? true : false;
  switch (keycode) {
    case SDLK_ESCAPE:
      this->_escapePressed = setting;
      break;
    case SDLK_UP:
      this->_upArrowPressed = setting;
      break;
    case SDLK_DOWN:
      this->_downArrowPressed = setting;
      break;
    case SDLK_LEFT:
      this->_leftArrowPressed = setting;
      break;
    case SDLK_RIGHT:
      this->_rightArrowPressed = setting;
      break;
    case SDLK_SPACE:
      this->_spacePressed = setting;
      break;
    case SDLK_p:
      this->_pausePressed = setting;
    default:
      break;
  }
}
