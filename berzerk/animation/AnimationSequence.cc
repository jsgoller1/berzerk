#include "AnimationSequence.hh"

AnimationSequence::AnimationSequence(const std::string name, int loopLimit) : _name(name), _loopLimit(loopLimit) {
  this->_sprites = std::vector<std::shared_ptr<Sprite>>();
}

AnimationSequence::AnimationSequence(const std::string name, const std::shared_ptr<Sprite> sprite, int loopLimit)
    : _name(name), _loopLimit(loopLimit) {
  this->_sprites = std::vector<std::shared_ptr<Sprite>>{sprite};
}
AnimationSequence::AnimationSequence(const std::string name, const std::vector<std::shared_ptr<Sprite>> sprites,
                                     const time_ms frameShowLength, int loopLimit)
    : _name(name), _loopLimit(loopLimit), _frameShowLength(frameShowLength), _sprites(sprites) {}

void AnimationSequence::addSprite(const std::shared_ptr<Sprite> sprite) { this->_sprites.push_back(sprite); }

void AnimationSequence::setFrameShowLength(const time_ms frameShowLength) { this->_frameShowLength = frameShowLength; }
time_ms AnimationSequence::getFrameShowLength() const { return this->_frameShowLength; }

time_ms AnimationSequence::getSinceLastUpdate() const { return this->_sinceLastUpdate; }

std::shared_ptr<Sprite> AnimationSequence::getCurrentSprite() const {
  if (not(this->_spriteIdx <= this->_sprites.size() - 1)) {
    return nullptr;
  }
  return this->_sprites[this->_spriteIdx];
}

bool AnimationSequence::loopsIndefinitely() { return this->_loopLimit == -1; }

bool AnimationSequence::isComplete() { return !this->loopsIndefinitely() && this->_loopCount >= this->_loopLimit; }

void AnimationSequence::update(const TimerProxy& timerProxy) {
  this->_sinceLastUpdate += timerProxy.getTimeDelta();
  if (_sinceLastUpdate > _frameShowLength && !this->isComplete()) {
    this->_spriteIdx = (this->_spriteIdx + 1) % this->_sprites.size();
    this->_sinceLastUpdate = 0;

    if (this->_spriteIdx == this->_sprites.size() - 1) {
      this->_loopCount++;
    }
  }
}

void AnimationSequence::reset() { this->_spriteIdx = 0; }
