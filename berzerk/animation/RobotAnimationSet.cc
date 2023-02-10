#include "RobotAnimationSet.hh"

#include <memory>

#include "AnimationSequence.hh"
#include "Direction.hh"
#include "RobotSpriteManager.hh"

RobotAnimationSet::RobotAnimationSet(const RobotSpriteManager& robotSpriteManager) {
  this->initIdle(robotSpriteManager);
  this->initMoving(robotSpriteManager);
  this->initShooting(robotSpriteManager);
  this->initDeath(robotSpriteManager);
}

std::shared_ptr<AnimationSequence> RobotAnimationSet::idle() const { return this->_idle; }

std::shared_ptr<AnimationSequence> RobotAnimationSet::moving(const Direction& direction) const {
  if (direction == Direction::North()) {
    return this->movingN();
  } else if (direction == Direction::South()) {
    return this->movingS();
  } else if (direction == Direction::East() || direction == Direction::SouthEast() ||
             direction == Direction::NorthEast()) {
    return this->movingE();
  } else {  // West, Southwest, Northwest
    return this->movingW();
  }
}

std::shared_ptr<AnimationSequence> RobotAnimationSet::movingN() const { return this->_movingN; }
std::shared_ptr<AnimationSequence> RobotAnimationSet::movingE() const { return this->_movingE; }
std::shared_ptr<AnimationSequence> RobotAnimationSet::movingS() const { return this->_movingS; }
std::shared_ptr<AnimationSequence> RobotAnimationSet::movingW() const { return this->_movingW; }

// NOTE: This code has similar versions in Robot and Player, but not completely duplicated
std::shared_ptr<AnimationSequence> RobotAnimationSet::shooting(const Direction& direction) const {
  if (direction == Direction::North()) {
    return this->shootingN();
  } else if (direction == Direction::South()) {
    return this->shootingS();
  } else if (direction == Direction::East() || direction == Direction::SouthEast() ||
             direction == Direction::NorthEast()) {
    return this->shootingE();
  } else {  // West, Southwest, Northwest
    return this->shootingW();
  }
}
std::shared_ptr<AnimationSequence> RobotAnimationSet::shootingN() const { return this->_shootingN; }
std::shared_ptr<AnimationSequence> RobotAnimationSet::shootingE() const { return this->_shootingE; }
std::shared_ptr<AnimationSequence> RobotAnimationSet::shootingS() const { return this->_shootingS; }
std::shared_ptr<AnimationSequence> RobotAnimationSet::shootingW() const { return this->_shootingW; }

std::shared_ptr<AnimationSequence> RobotAnimationSet::dying() const { return this->_dying; }
std::shared_ptr<AnimationSequence> RobotAnimationSet::dead() const { return this->_dead; }

void RobotAnimationSet::initIdle(const RobotSpriteManager& robotSpriteManager) {
  this->_idle = std::make_shared<AnimationSequence>("idle");
  for (int i = 0; i < 6; i++) {
    this->_idle->addSprite(robotSpriteManager.idle(i));
  }
}

void RobotAnimationSet::initMoving(const RobotSpriteManager& robotSpriteManager) {
  this->_movingE = std::make_shared<AnimationSequence>("movingE");
  this->_movingW = std::make_shared<AnimationSequence>("movingW");
  for (int i = 0; i < 2; i++) {
    this->_movingE->addSprite(robotSpriteManager.movingE(i));
    this->_movingW->addSprite(robotSpriteManager.movingW(i));
  }
  this->_movingN = std::make_shared<AnimationSequence>("movingN");
  this->_movingS = std::make_shared<AnimationSequence>("movingS");
  for (int i = 0; i < 3; i++) {
    this->_movingN->addSprite(robotSpriteManager.movingN(i));
    this->_movingS->addSprite(robotSpriteManager.movingS(i));
  }
}

void RobotAnimationSet::initShooting(const RobotSpriteManager& robotSpriteManager) {
  this->_shootingN = std::make_shared<AnimationSequence>("shootingN", robotSpriteManager.shootingN());
  this->_shootingE = std::make_shared<AnimationSequence>("shootingE", robotSpriteManager.shootingE());
  this->_shootingS = std::make_shared<AnimationSequence>("shootingS", robotSpriteManager.shootingS());
  this->_shootingW = std::make_shared<AnimationSequence>("shootingW", robotSpriteManager.shootingW());
}

void RobotAnimationSet::initDeath(const RobotSpriteManager& robotSpriteManager) {
  this->_dying = std::make_shared<AnimationSequence>("dying", 1);
  for (int i = 0; i < 4; i++) {
    this->_dying->addSprite(robotSpriteManager.dying(i));
  }
  this->_dead = std::make_shared<AnimationSequence>("dead");
  this->_dead->addSprite(robotSpriteManager.dead());
}
