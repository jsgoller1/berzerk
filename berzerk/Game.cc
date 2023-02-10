#include "Game.hh"

#include <iostream>

#include "BulletSpriteManager.hh"
#include "CLI.hh"
#include "DrawingProxy.hh"
#include "InputHandler.hh"
#include "LevelAudioComponent.hh"
#include "LevelSpriteManager.hh"
#include "OttoAudioComponent.hh"
#include "OttoSpriteManager.hh"
#include "PlayerAudioComponent.hh"
#include "PlayerSpriteManager.hh"
#include "RobotAudioComponent.hh"
#include "RobotSpriteManager.hh"
#include "Screen.hh"
#include "TextSpriteManager.hh"
#include "UI.hh"

// Public
Game::Game(const CLI& args, Screen& screen, InputHandler& inputHandler, Timer& timer)
    : _levelSpriteManager(std::make_unique<LevelSpriteManager>(args.getAssetsDirPath())),
      _levelAudioComponent(std::make_unique<LevelAudioComponent>(args.getAssetsDirPath())),
      _playerSpriteManager(std::make_unique<PlayerSpriteManager>(args.getAssetsDirPath())),
      _playerAudioComponent(std::make_unique<PlayerAudioComponent>(args.getAssetsDirPath())),
      _robotSpriteManager(std::make_unique<RobotSpriteManager>(args.getAssetsDirPath())),
      _robotAudioComponent(std::make_unique<RobotAudioComponent>(args.getAssetsDirPath())),
      _ottoSpriteManager(std::make_unique<OttoSpriteManager>(args.getAssetsDirPath())),
      _ottoAudioComponent(std::make_unique<OttoAudioComponent>(args.getAssetsDirPath())),
      _bulletSpriteManager(std::make_unique<BulletSpriteManager>(args.getAssetsDirPath())),
      _textSpriteManager(std::make_unique<TextSpriteManager>(args.getAssetsDirPath())),
      _inputHandler(inputHandler),
      _screen(screen),
      _timer(timer) {
  this->_ui =
      std::make_unique<UI>(*this->_textSpriteManager, this->_screen.getScreenDrawingProxy(), this->_LevelDataProxy);
  this->_currentLevel =
      std::make_unique<Level>(this->_levelNo, this->_LevelDataProxy, this->_screen.getScreenDrawingProxy(),
                              *this->_levelSpriteManager, *this->_levelAudioComponent, *this->_playerSpriteManager,
                              *this->_playerAudioComponent, *this->_robotSpriteManager, *this->_robotAudioComponent,
                              *this->_ottoSpriteManager, *this->_ottoAudioComponent, *this->_bulletSpriteManager);
}

void Game::run() {
  /*
  Core game loop
  */
  while (!(this->isLost() || this->_inputHandler.shouldQuit())) {
    this->_timer.tick();
    this->_inputHandler.getKeyboardInput();
    this->update(this->_inputHandler, this->_timer.getProxy());
    this->draw(this->_screen);
  }
}

void Game::update(const InputHandler& inputHandler, const TimerProxy& timerProxy) {
  if (inputHandler.pausePressed()) {
    this->_isPaused = !this->_isPaused;
  }
  if (this->_isPaused) {
    return;
  }
  if (this->_currentLevel->isFinished()) {
    if (!this->_currentLevel->playerAtExit()) {
      // If player is dead, decrement life counter and create new level
      this->_playerLives--;
    } else {
      (this->_currentLevel->isCleared()) ? this->_levelAudioComponent->playEscapeBrave()
                                         : this->_levelAudioComponent->playEscapeCowardly();
    }
    this->_levelNo = this->_playerScore / SCORE_LEVEL_THRESHOLD;
    this->_currentLevel =
        std::make_unique<Level>(this->_levelNo, this->_LevelDataProxy, this->_screen.getScreenDrawingProxy(),
                                *this->_levelSpriteManager, *this->_levelAudioComponent, *this->_playerSpriteManager,
                                *this->_playerAudioComponent, *this->_robotSpriteManager, *this->_robotAudioComponent,
                                *this->_ottoSpriteManager, *this->_ottoAudioComponent, *this->_bulletSpriteManager);
    this->_timer.reset();
  }
  this->_ui->update();
  this->_currentLevel->update(inputHandler, timerProxy);
}

void Game::draw(Screen& screen) {
  screen.clear();
  this->_ui->draw();
  this->_currentLevel->draw();
  screen.render();
}

// Private
void Game::initUI(const TextSpriteManager& textSpriteManager, DrawingProxy& drawingProxy) {
  // The UI (lives remaining and score) should take up
  // the bottom 10% of the screen or less

  (void)textSpriteManager;
  (void)drawingProxy;
}

bool Game::isLost() { return this->_playerLives <= 0; }
