#include "Otto.hh"

#include <algorithm>
#include <iostream>

#include "Configs.hh"
#include "Direction.hh"
#include "LevelHelpers.hh"
#include "OttoAudioComponent.hh"

Otto::Otto(const int levelNo, const Vect2D& position, DrawingProxy& drawingProxy,
           PlayerPositionProxy& playerPositionProxy, OttoSpriteManager& ottoSpriteManager,
           const OttoAudioComponent& ottoAudioComponent)
    : GameObject(position, Vect2D::zero()),
      _playerPositionProxy(playerPositionProxy),
      _ottoSpriteManager(ottoSpriteManager),
      _ottoAudioComponent(ottoAudioComponent) {
  this->_ottoSpriteManager.setColorMask(getLevelColor(levelNo));
  this->_ottoAnimationSet = std::unique_ptr<OttoAnimationSet>(new OttoAnimationSet(this->_ottoSpriteManager));
  this->_drawingComponent = std::unique_ptr<AnimatedDrawingComponent>(
      new AnimatedDrawingComponent(this->getPositionComponent(), OTTO_CHARACTER_HEIGHT_PX, OTTO_CHARACTER_WIDTH_PX,
                                   drawingProxy, this->_ottoAnimationSet->outOfPlay()));
}

void Otto::update(const TimerProxy& timerProxy) {
  this->_state = this->getNewState(this->_state, timerProxy);
  switch (this->_state) {
    case OttoState::OUT_OF_PLAY:
      // Explicitly nothing to do here.
      break;
    case OttoState::SPAWNING:
      this->stateBehaviorSpawning();
      break;
    case OttoState::CHASING:
      this->stateBehaviorChasing(timerProxy);
      break;
  }
  this->_drawingComponent->updateAnimationSequence(timerProxy);
}

void Otto::draw() { this->_drawingComponent->draw(); }

AnimatedDrawingComponent& Otto::getDrawingComponent() const { return *this->_drawingComponent; }

void Otto::resolveCollision(GameObject& target) {
  // Otto is invulnerable, nothing to do here.
  (void)target;
}

OttoState Otto::getNewState(const OttoState currentState, const TimerProxy& timerProxy) {
  time_ms currentTime = timerProxy.getCurrentTime();
  bool shouldSpawn = currentTime >= OTTO_ENTRANCE_TIME_THRESHOLD_MS;
  bool shouldChase = this->_drawingComponent->getAnimationSequence().isComplete();

  switch (currentState) {
    case OttoState::OUT_OF_PLAY:
      return (shouldSpawn) ? OttoState::SPAWNING : OttoState::OUT_OF_PLAY;
    case OttoState::SPAWNING:
      return (shouldChase) ? OttoState::CHASING : OttoState::SPAWNING;
    case OttoState::CHASING:
      return OttoState::CHASING;
  }
}
void Otto::stateBehaviorSpawning() {
  if (!this->_playedEntrySound) {
    this->_playedEntrySound = true;
    this->_ottoAudioComponent.playIntruderAlert();
  }
  this->_drawingComponent->setAnimationSequence(this->_ottoAnimationSet->spawning());
  this->setPosition(Vect2D::zero());
}
void Otto::stateBehaviorChasing(const TimerProxy& timerProxy) {
  this->updateJumpDisplacement(timerProxy);
  this->moveChasingPlayer();
  this->_drawingComponent->setAnimationSequence(this->_ottoAnimationSet->chasing());
}

void Otto::moveChasingPlayer() {
  // Get the distance to the player
  Vect2D player = this->_playerPositionProxy.getPlayerPosition();
  Vect2D us = this->getPosition();
  int xDistance = abs(player.x - us.x);
  xDistance *= (us.x < player.x) ? 1 : -1;
  int yDistance = abs(player.y - us.y);
  yDistance *= (us.y < player.y) ? 1 : -1;
  Vect2D distance = Vect2D(xDistance, yDistance);
  // If 1/100th of the distance to the player rounds down to zero (resulting in no movement), instead approximate which
  // compass direction they're in, then move in that direction. If we're this close, this will likely lead to a
  // collision anyways due to the width of the Otto sprite.
  // TODO: This technique causes Otto to move faster when he's further away.
  if (Vect2D(distance.x / 100, distance.y / 100) == Vect2D::zero()) {
    distance = Vect2D(Direction(Vect2D(distance.x, 0))) + Vect2D(Direction(Vect2D(distance.y, 0)));
  } else {
    distance.x /= 100;
    distance.y /= 100;
  }
  this->setPosition(this->getPosition() + distance);
}

void Otto::updateJumpDisplacement(const TimerProxy& timerProxy) {
  // TODO: So that bouncing doesn't interfere with navigation, we should apply vertical displacement before drawing,
  // draw, then unapply it for navigation. Need second variable to keep track of running total vertical displacement.
  if (this->_timeSinceLastVerticalMovement < OTTO_JUMP_VERTICAL_MOVEMENT_DELAY_MS) {
    this->_timeSinceLastVerticalMovement += timerProxy.getTimeDelta();
    return;
  }
  this->_timeSinceLastVerticalMovement = 0;

  Vect2D verticalDisplacement = Vect2D::zero();
  switch (this->_currentJumpVerticalOffsetCount) {
    case 0:
      verticalDisplacement = Vect2D(0, 50);
      break;
    case 1:
      verticalDisplacement = Vect2D(0, 20);
      break;
    case 2:
      verticalDisplacement = Vect2D(0, 15);
      break;
    case 3:
      verticalDisplacement = Vect2D(0, 10);
      break;
    case 4:
      verticalDisplacement = Vect2D(0, 5);
      break;
    case 5:
      verticalDisplacement = Vect2D(0, -5);
      break;
    case 6:
      verticalDisplacement = Vect2D(0, -10);
      break;
    case 7:
      verticalDisplacement = Vect2D(0, -15);
      break;
    case 8:
      verticalDisplacement = Vect2D(0, -20);
      break;
    case 9:
      verticalDisplacement = Vect2D(0, -50);
      break;
    default:
      break;
  }
  this->setPosition(this->getPosition() + verticalDisplacement);
  this->_currentJumpVerticalOffsetCount = (this->_currentJumpVerticalOffsetCount + 1) % 10;
}
