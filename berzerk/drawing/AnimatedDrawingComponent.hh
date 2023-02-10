#pragma once

#include <memory>

#include "AnimationSequence.hh"
#include "DrawingComponent.hh"
#include "Time.hh"

// Forward decls
class PositionComponent;

class AnimatedDrawingComponent : public DrawingComponent {
 public:
  AnimatedDrawingComponent(PositionComponent& _positionComponent, const int height, const int width,
                           DrawingProxy& drawingProxy, std::shared_ptr<AnimationSequence> animationSequence);

  // Get the current sprite by getting the next animation
  void draw() override;
  std::shared_ptr<Sprite> getCurrentSprite() const override;

  void updateAnimationSequence(const TimerProxy& timerProxy);
  void setAnimationSequence(std::shared_ptr<AnimationSequence> animation);
  AnimationSequence& getAnimationSequence() const;

 private:
  PositionComponent& _positionComponent;
  std::shared_ptr<AnimationSequence> _animationSequence;
};
