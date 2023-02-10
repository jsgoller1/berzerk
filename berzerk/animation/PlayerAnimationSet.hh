#pragma once

#include <memory>

#include "AnimationSequence.hh"

// Fwd decls
class PlayerSpriteManager;
class Direction;

class PlayerAnimationSet {
 public:
  PlayerAnimationSet(const PlayerSpriteManager& playerSpriteManager);

  std::shared_ptr<AnimationSequence> idle() const;
  std::shared_ptr<AnimationSequence> movingE() const;
  std::shared_ptr<AnimationSequence> movingW() const;
  std::shared_ptr<AnimationSequence> shootingN() const;
  std::shared_ptr<AnimationSequence> shootingE() const;
  std::shared_ptr<AnimationSequence> shootingS() const;
  std::shared_ptr<AnimationSequence> shootingW() const;
  std::shared_ptr<AnimationSequence> shootingNE() const;
  std::shared_ptr<AnimationSequence> shootingSE() const;
  std::shared_ptr<AnimationSequence> shootingNW() const;
  std::shared_ptr<AnimationSequence> shootingSW() const;
  std::shared_ptr<AnimationSequence> dying() const;
  std::shared_ptr<AnimationSequence> dead() const;
  std::shared_ptr<AnimationSequence> shooting(const Direction& direction) const;

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
  std::shared_ptr<AnimationSequence> _shootingNE;
  std::shared_ptr<AnimationSequence> _shootingSE;
  std::shared_ptr<AnimationSequence> _shootingNW;
  std::shared_ptr<AnimationSequence> _shootingSW;
  std::shared_ptr<AnimationSequence> _dying;
  std::shared_ptr<AnimationSequence> _dead;
  void initIdle(const PlayerSpriteManager& playerSpriteManager);
  void initMoving(const PlayerSpriteManager& playerSpriteManager);
  void initShooting(const PlayerSpriteManager& playerSpriteManager);
  void initDeath(const PlayerSpriteManager& playerSpriteManager);
};
