#pragma once

#include "Configs.hh"
#include "Sprite.hh"

class DrawingProxy;
class LevelDataProxy;
class TextSpriteManager;

class UI {
 public:
  UI(const TextSpriteManager& textSpriteManager, DrawingProxy& drawingProxy, LevelDataProxy& LevelDataProxy);
  void update();
  void draw();

 private:
  const TextSpriteManager& _textSpriteManager;
  DrawingProxy& _drawingProxy;
  LevelDataProxy& _levelDataProxy;

  std::shared_ptr<Sprite> _scoreboard[UI_SCOREBOARD_DIGIT_PLACES];
};
