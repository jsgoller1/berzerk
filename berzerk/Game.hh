#pragma once
#include <memory>

#include "BulletSpriteManager.hh"
#include "Level.hh"
#include "LevelAudioComponent.hh"
#include "LevelDataProxy.hh"
#include "LevelSpriteManager.hh"
#include "OttoAudioComponent.hh"
#include "OttoSpriteManager.hh"
#include "PlayerAudioComponent.hh"
#include "PlayerSpriteManager.hh"
#include "RobotAudioComponent.hh"
#include "RobotSpriteManager.hh"
#include "TextSpriteManager.hh"
#include "Time.hh"
#include "UI.hh"

#define SCREEN_WIDTH 1200
#define SCREEN_HEIGHT 800

// fwd decls
class CLI;
class DrawingProxy;
class InputHandler;
class Screen;

class Game {
 public:
  Game(const CLI& args, Screen& screen, InputHandler& inputHandler, Timer& timer);
  void run();

  void update(const InputHandler& inputHandler, const TimerProxy& timerProxy);
  void draw(Screen& screen);

 private:
  std::unique_ptr<UI> _ui;
  std::unique_ptr<Level> _currentLevel;
  std::unique_ptr<LevelSpriteManager> _levelSpriteManager;
  std::unique_ptr<LevelAudioComponent> _levelAudioComponent;

  std::unique_ptr<PlayerSpriteManager> _playerSpriteManager;
  std::unique_ptr<PlayerAudioComponent> _playerAudioComponent;

  std::unique_ptr<RobotSpriteManager> _robotSpriteManager;
  std::unique_ptr<RobotAudioComponent> _robotAudioComponent;

  std::unique_ptr<OttoSpriteManager> _ottoSpriteManager;
  std::unique_ptr<OttoAudioComponent> _ottoAudioComponent;

  std::unique_ptr<BulletSpriteManager> _bulletSpriteManager;
  std::unique_ptr<TextSpriteManager> _textSpriteManager;
  InputHandler& _inputHandler;
  Screen& _screen;
  Timer& _timer;

  bool _isPaused = false;
  int _playerLives = 3;
  int _playerScore = 0;
  int _levelNo = 0;
  LevelDataProxy _LevelDataProxy = LevelDataProxy(&this->_playerScore, &this->_playerLives);

  void initUI(const TextSpriteManager& textSpriteManager, DrawingProxy& drawingProxy);
  bool isLost();
};
