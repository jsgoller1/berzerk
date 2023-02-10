#include "PlayerAnimationSet.hh"

#include <iostream>
#include <vector>

#include "AnimationSequence.hh"
#include "Configs.hh"
#include "Direction.hh"
#include "PlayerSpriteManager.hh"
#include "Sprite.hh"

PlayerAnimationSet::PlayerAnimationSet(const PlayerSpriteManager& playerSpriteManager) {
  this->initIdle(playerSpriteManager);
  this->initMoving(playerSpriteManager);
  this->initShooting(playerSpriteManager);
  this->initDeath(playerSpriteManager);
}

std::shared_ptr<AnimationSequence> PlayerAnimationSet::idle() const { return this->_idle; }
std::shared_ptr<AnimationSequence> PlayerAnimationSet::movingE() const { return this->_movingE; }
std::shared_ptr<AnimationSequence> PlayerAnimationSet::movingW() const { return this->_movingW; }
std::shared_ptr<AnimationSequence> PlayerAnimationSet::shootingN() const { return this->_shootingN; }
std::shared_ptr<AnimationSequence> PlayerAnimationSet::shootingE() const { return this->_shootingE; }
std::shared_ptr<AnimationSequence> PlayerAnimationSet::shootingS() const { return this->_shootingS; }
std::shared_ptr<AnimationSequence> PlayerAnimationSet::shootingW() const { return this->_shootingW; }
std::shared_ptr<AnimationSequence> PlayerAnimationSet::shootingNE() const { return this->_shootingNE; }
std::shared_ptr<AnimationSequence> PlayerAnimationSet::shootingSE() const { return this->_shootingSE; }
std::shared_ptr<AnimationSequence> PlayerAnimationSet::shootingNW() const { return this->_shootingNW; }
std::shared_ptr<AnimationSequence> PlayerAnimationSet::shootingSW() const { return this->_shootingSW; }
std::shared_ptr<AnimationSequence> PlayerAnimationSet::dying() const { return this->_dying; }
std::shared_ptr<AnimationSequence> PlayerAnimationSet::dead() const { return this->_dead; }

// NOTE: This code has similar versions in Robot and Player, but not completely duplicated
std::shared_ptr<AnimationSequence> PlayerAnimationSet::shooting(const Direction& direction) const {
  if (direction == Direction::North()) {
    return this->shootingN();
  } else if (direction == Direction::South()) {
    return this->shootingS();
  } else if (direction == Direction::East()) {
    return this->shootingE();
  } else if (direction == Direction::West()) {
    return this->shootingW();
  } else if (direction == Direction::NorthEast()) {
    return this->shootingNE();
  } else if (direction == Direction::SouthEast()) {
    return this->shootingSE();
  } else if (direction == Direction::SouthWest()) {
    return this->shootingSW();
  } else {  // NorthWest
    return this->shootingNW();
  }
}

void PlayerAnimationSet::initIdle(const PlayerSpriteManager& playerSpriteManager) {
  this->_idle = std::make_shared<AnimationSequence>("idle");
  this->_idle->addSprite(playerSpriteManager.idle());
}
void PlayerAnimationSet::initMoving(const PlayerSpriteManager& playerSpriteManager) {
  this->_movingE = std::make_shared<AnimationSequence>("movingE");
  this->_movingE->setFrameShowLength(PLAYER_ANIMATION_FRAME_SHOW_LENGTH_MS);
  this->_movingW = std::make_shared<AnimationSequence>("movingW");
  this->_movingW->setFrameShowLength(PLAYER_ANIMATION_FRAME_SHOW_LENGTH_MS);
  for (int i = 0; i < 3; i++) {
    this->_movingE->addSprite(playerSpriteManager.movingE(i));
    this->_movingW->addSprite(playerSpriteManager.movingW(i));
  }
}

void PlayerAnimationSet::initShooting(const PlayerSpriteManager& playerSpriteManager) {
  this->_shootingN = std::make_shared<AnimationSequence>("shootingN");
  this->_shootingN->addSprite(playerSpriteManager.shootingN());
  this->_shootingS = std::make_shared<AnimationSequence>("shootingS");
  this->_shootingS->addSprite(playerSpriteManager.shootingS());
  this->_shootingE = std::make_shared<AnimationSequence>("shootingE");
  this->_shootingE->addSprite(playerSpriteManager.shootingE());
  this->_shootingW = std::make_shared<AnimationSequence>("shootingW");
  this->_shootingW->addSprite(playerSpriteManager.shootingW());
  this->_shootingNE = std::make_shared<AnimationSequence>("shootingNE");
  this->_shootingNE->addSprite(playerSpriteManager.shootingNE());
  this->_shootingSE = std::make_shared<AnimationSequence>("shootingSE");
  this->_shootingSE->addSprite(playerSpriteManager.shootingSE());
  this->_shootingNW = std::make_shared<AnimationSequence>("shootingNW");
  this->_shootingNW->addSprite(playerSpriteManager.shootingNW());
  this->_shootingSW = std::make_shared<AnimationSequence>("shootingSW");
  this->_shootingSW->addSprite(playerSpriteManager.shootingSW());
}

void PlayerAnimationSet::initDeath(const PlayerSpriteManager& playerSpriteManager) {
  this->_dying = std::make_shared<AnimationSequence>("dying", PLAYER_DYING_ANIMATION_LOOP_COUNT);
  for (int i = 0; i < 8; i++) {
    this->_dying->addSprite(playerSpriteManager.dying(i));
  }

  this->_dead = std::make_shared<AnimationSequence>("dead");
  this->_dead->addSprite(playerSpriteManager.dead());
}
