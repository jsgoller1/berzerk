#pragma once

#include <memory>

#include "AnimationSequence.hh"

// Fwd decl
class RobotSpriteManager;
class Direction;

class RobotAnimationSet {
 public:
  RobotAnimationSet(const RobotSpriteManager& robotSpriteManager);

  std::shared_ptr<AnimationSequence> idle() const;
  std::shared_ptr<AnimationSequence> moving(const Direction& direction) const;
  std::shared_ptr<AnimationSequence> movingN() const;
  std::shared_ptr<AnimationSequence> movingE() const;
  std::shared_ptr<AnimationSequence> movingS() const;
  std::shared_ptr<AnimationSequence> movingW() const;
  std::shared_ptr<AnimationSequence> shootingN() const;
  std::shared_ptr<AnimationSequence> shootingE() const;
  std::shared_ptr<AnimationSequence> shootingS() const;
  std::shared_ptr<AnimationSequence> shootingW() const;
  std::shared_ptr<AnimationSequence> shooting(const Direction& direction) const;
  std::shared_ptr<AnimationSequence> dying() const;
  std::shared_ptr<AnimationSequence> dead() const;

 private:
  std::shared_ptr<AnimationSequence> _idle;
  std::shared_ptr<AnimationSequence> _movingN;
  std::shared_ptr<AnimationSequence> _movingE;
  std::shared_ptr<AnimationSequence> _movingS;
  std::shared_ptr<AnimationSequence> _movingW;
  std::shared_ptr<AnimationSequence> _shootingN;
  std::shared_ptr<AnimationSequence> _shootingE;
  std::shared_ptr<AnimationSequence> _shootingS;
  std::shared_ptr<AnimationSequence> _shootingW;
  std::shared_ptr<AnimationSequence> _dying;
  std::shared_ptr<AnimationSequence> _dead;

  void initIdle(const RobotSpriteManager& robotSpriteManager);
  void initMoving(const RobotSpriteManager& robotSpriteManager);
  void initShooting(const RobotSpriteManager& robotSpriteManager);
  void initDeath(const RobotSpriteManager& robotSpriteManager);
};
