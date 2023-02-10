#include "UI.hh"

#include "DrawingProxy.hh"
#include "LevelDataProxy.hh"
#include "TextSpriteManager.hh"

UI::UI(const TextSpriteManager& textSpriteManager, DrawingProxy& drawingProxy, LevelDataProxy& levelDataProxy)
    : _textSpriteManager(textSpriteManager), _drawingProxy(drawingProxy), _levelDataProxy(levelDataProxy) {
  for (size_t i = 0; i < UI_SCOREBOARD_DIGIT_PLACES; i++) {
    this->_scoreboard[i] = this->_textSpriteManager.digit(0);
  }
}

void UI::update() {
  int score = this->_levelDataProxy.getScore();
  for (size_t i = 0; i < UI_SCOREBOARD_DIGIT_PLACES; i++) {
    this->_scoreboard[i] = this->_textSpriteManager.digit(score % 10);
    score /= 10;
  }
}
void UI::draw() {
  Vect2D topLeft = UI_TOP_LEFT;
  for (int i = UI_SCOREBOARD_DIGIT_PLACES - 1; i >= 0; i--) {
    this->_drawingProxy.draw(topLeft, TEXT_WIDTH_PX, TEXT_HEIGHT_PX, this->_scoreboard[i]);
    topLeft.x += TEXT_WIDTH_PX + TEXT_BOUNDARY_WIDTH_PX;
  }

  // Add a gap between score and lives count
  topLeft.x += (TEXT_WIDTH_PX + TEXT_BOUNDARY_WIDTH_PX) * 2;

  for (int i = 0; i < this->_levelDataProxy.getLivesCount() - 1; i++) {
    this->_drawingProxy.draw(topLeft, TEXT_WIDTH_PX, TEXT_HEIGHT_PX, this->_textSpriteManager.man());
    topLeft.x += TEXT_WIDTH_PX + TEXT_BOUNDARY_WIDTH_PX;
  }
}
