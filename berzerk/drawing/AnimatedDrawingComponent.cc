#include "AnimatedDrawingComponent.hh"

AnimatedDrawingComponent::AnimatedDrawingComponent(PositionComponent& positionComponent, const int height,
                                                   const int width, DrawingProxy& drawingProxy,
                                                   std::shared_ptr<AnimationSequence> animation)
    : DrawingComponent(positionComponent, height, width, drawingProxy),
      _positionComponent(positionComponent),
      _animationSequence(animation) {}

std::shared_ptr<Sprite> AnimatedDrawingComponent::getCurrentSprite() const {
  return this->_animationSequence->getCurrentSprite();
}

void AnimatedDrawingComponent::updateAnimationSequence(const TimerProxy& timerProxy) {
  return this->_animationSequence->update(timerProxy);
}

AnimationSequence& AnimatedDrawingComponent::getAnimationSequence() const { return *this->_animationSequence; }

void AnimatedDrawingComponent::setAnimationSequence(std::shared_ptr<AnimationSequence> animation) {
  this->_animationSequence = animation;
}

void AnimatedDrawingComponent::draw() {
  this->getDrawingProxy().draw(this->_positionComponent.getPosition(), this->getWidth(), this->getHeight(),
                               this->_animationSequence->getCurrentSprite());
}
