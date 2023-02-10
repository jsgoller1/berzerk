#include "Robot.hh"

#include <iostream>

#include "Direction.hh"
#include "Math.hh"
#include "RobotAudioComponent.hh"
#include "WallCollisionProxy.hh"

Robot::Robot(const Vect2D& position, const Vect2D& velocity, LevelShootingProxy& shootingProxy,
             DrawingProxy& drawingProxy, const PlayerPositionProxy& playerPositionProxy,
             const RobotSpriteManager& robotSpriteManager, const RobotAudioComponent& robotAudioComponent,
             const WallCollisionProxy& wallCollisionProxy, const RobotWallAvoidancePolicy avoidancePolicy)
    : GameObject(position, velocity),
      IShooting(shootingProxy),
      _playerPositionProxy(playerPositionProxy),
      _robotAudioComponent(robotAudioComponent),
      _wallCollisionProxy(wallCollisionProxy),
      _avoidancePolicy(avoidancePolicy),
      _isAvoiding(this->shouldAvoidWalls()) {
  this->_robotAnimationSet = std::unique_ptr<RobotAnimationSet>(new RobotAnimationSet(robotSpriteManager));
  this->_drawingComponent = std::unique_ptr<AnimatedDrawingComponent>(
      new AnimatedDrawingComponent(this->getPositionComponent(), ROBOT_DEFAULT_HEIGHT, ROBOT_DEFAULT_WIDTH,
                                   drawingProxy, this->_robotAnimationSet->idle()));
}

AnimatedDrawingComponent& Robot::getDrawingComponent() const { return *this->_drawingComponent; }

void Robot::resolveCollision(GameObject& target) {
  (void)target;
  // TODO: I'd prefer we didn't do either state or animation setting here; both already have
  // respective update functions, and should be done there.
  // TODO: Maybe we should have an event queue of some kind and state updates process events on that queue?
  if (this->_state != CharacterState::DYING) {
    this->_state = CharacterState::DYING;
    this->_robotAudioComponent.playDeath();
    this->_drawingComponent->setAnimationSequence(this->_robotAnimationSet->dying());
  }
}

void Robot::update(const TimerProxy& timerProxy) {
  this->_sinceLastShot += timerProxy.getTimeDelta();
  this->_state = this->getNewState(this->_state, timerProxy);
  switch (this->_state) {
    case CharacterState::DEAD:
      this->stateBehaviorDead();
      break;
    case CharacterState::DYING:
      this->stateBehaviorDying();
      break;
    case CharacterState::IDLE:
      this->stateBehaviorIdle();
      break;
    case CharacterState::MOVING:
      this->stateBehaviorMoving();
      break;
    case CharacterState::SHOOTING:
      this->stateBehaviorShooting();
      break;
  }
  this->_drawingComponent->updateAnimationSequence(timerProxy);
}

CharacterState Robot::getNewState(const CharacterState currentState, const TimerProxy& timerProxy) const {
  /*
   * As soon as the player is within range, robots either start shooting or moving to a firing axis.
   * Robots may be forced to be idle (i.e. not shooting or moving), but they can still be killed
   */
  bool playerInRange = this->withinRangeOfPlayer();
  bool playerShootable = this->getShootingDirection() != Direction::None();

  if (currentState == CharacterState::DEAD) {
    return currentState;
  }
  if (currentState == CharacterState::DYING) {
    return (this->getDrawingComponent().getAnimationSequence().isComplete()) ? CharacterState::DEAD
                                                                             : CharacterState::DYING;
  }
  bool forceIdle = timerProxy.getCurrentTime() < LEVEL_START_DELAY_MS;
  if (!forceIdle && playerInRange && playerShootable) {
    return CharacterState::SHOOTING;
  }

  bool nextMoveKillsRobot = this->_wallCollisionProxy.test(
      *this, Vect2D(this->getMovingDirection()) * ROBOT_MOVE_SPEED * ROBOT_COLLISION_TEST_MOVES_COUNT);
  if (!forceIdle && playerInRange && !(this->_isAvoiding && nextMoveKillsRobot)) {
    return CharacterState::MOVING;
  }

  return CharacterState::IDLE;
}

void Robot::stateBehaviorDead() {
  this->_drawingComponent->setAnimationSequence(this->_robotAnimationSet->dead());
  this->setPosition(Vect2D(-2000, -2000));
  this->setShouldRemove(true);
}

void Robot::stateBehaviorDying() {
  this->getDrawingComponent().setHeight(ROBOT_DYING_HEIGHT);
  this->getDrawingComponent().setWidth(ROBOT_DYING_WIDTH);
  this->_drawingComponent->setAnimationSequence(this->_robotAnimationSet->dying());
}

void Robot::stateBehaviorIdle() { this->_drawingComponent->setAnimationSequence(this->_robotAnimationSet->idle()); }

void Robot::stateBehaviorMoving() {
  // TODO: Moving behavior occurs every frame, so updating isAvoiding here or at the time of state update will
  // occur repeatedly until at close enough range to the wall we get a "should", after which the robot transitions to
  // Idle. In essence, the robot will always eventually choose not to walk into a wall for the SOMETIMES policy. We need
  // to update the isAvoiding only when the robot first changes into the Moving state.
  this->_isAvoiding = this->shouldAvoidWalls();
  Direction facingDirection = this->getMovingDirection();
  this->_drawingComponent->setAnimationSequence(this->_robotAnimationSet->moving(facingDirection));
  this->setVelocity(Vect2D(facingDirection) * ROBOT_MOVE_SPEED);
  this->move();
}

void Robot::stateBehaviorShooting() {
  this->_drawingComponent->setAnimationSequence(this->_robotAnimationSet->shooting(this->getShootingDirection()));
  if (this->_sinceLastShot > ROBOT_SHOOT_DELAY_MS) {
    this->_robotAudioComponent.playShooting();
    this->_sinceLastShot = 0;
    this->shoot(this->getShootingDirection(), this->getPosition());
  }
}

bool Robot::withinRangeOfPlayer() const {
  return this->getPosition().distance(this->_playerPositionProxy.getPlayerPosition()) <= ROBOT_PURSUIT_DISTANCE_PX;
}

Direction Robot::getShootingDirection() const {
  return this->_playerPositionProxy.lineScan(this->getPosition(), ROBOT_SHOOTING_ERROR_MARGIN_PX);
}

Direction Robot::getMovingDirection() const {
  // If the player cannot be shot, pick a direction to move in for closing the distance to the player.
  // The direction picked should be the longer of the two (horizontal or vertical), so that the overall distance to
  // the player decreases the most. Diagonal is chosen if they're equal.

  Vect2D us = this->getPosition();
  Vect2D them = this->_playerPositionProxy.getPlayerPosition();

  int xDistance = absval(us.x - them.x);
  Direction horizontal = (us.x < them.x) ? Direction::East() : Direction::West();

  int yDistance = absval(us.y - them.y);
  Direction vertical = (us.y < them.y) ? Direction::North() : Direction::South();

  if (xDistance == yDistance) {
    return horizontal + vertical;
  } else if (xDistance > yDistance) {
    return horizontal;
  } else {  // xDistance < yDistance
    return vertical;
  }
}

bool Robot::shouldAvoidWalls() const {
  switch (this->_avoidancePolicy) {
    case RobotWallAvoidancePolicy::ALWAYS:
      return true;
    case RobotWallAvoidancePolicy::SOMETIMES:
      return randInt(0, 1) == 1;
    case RobotWallAvoidancePolicy::NEVER:
      return false;
  }
}
