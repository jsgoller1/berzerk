#include "OttoAnimationSet.hh"

#include "OttoSpriteManager.hh"

OttoAnimationSet::OttoAnimationSet(const OttoSpriteManager& ottoSpriteManager) {
  this->_outOfPlay = std::make_shared<AnimationSequence>("outOfPlay", ottoSpriteManager.spawning(0));

  time_ms spawningFrameShowLength = 100;
  int loopLimit = 1;
  this->_spawning = std::make_shared<AnimationSequence>("spawning", loopLimit);
  this->_spawning->setFrameShowLength(spawningFrameShowLength);
  for (int i = 0; i < 7; i++) {
    this->_spawning->addSprite(ottoSpriteManager.spawning(i));
  }
  this->_chasing = std::make_shared<AnimationSequence>("chasing", ottoSpriteManager.chasing());
}

std::shared_ptr<AnimationSequence> OttoAnimationSet::outOfPlay() const { return this->_outOfPlay; }
std::shared_ptr<AnimationSequence> OttoAnimationSet::spawning() const { return this->_spawning; }
std::shared_ptr<AnimationSequence> OttoAnimationSet::chasing() const { return this->_chasing; }
