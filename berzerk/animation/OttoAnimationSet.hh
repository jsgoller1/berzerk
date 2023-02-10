#pragma once
#include <memory>

#include "AnimationSequence.hh"

// Fwd decl
class OttoSpriteManager;

class OttoAnimationSet {
 public:
  OttoAnimationSet(const OttoSpriteManager& ottoSpriteManager);
  std::shared_ptr<AnimationSequence> outOfPlay() const;
  std::shared_ptr<AnimationSequence> spawning() const;
  std::shared_ptr<AnimationSequence> chasing() const;

 private:
  std::shared_ptr<AnimationSequence> _outOfPlay;
  std::shared_ptr<AnimationSequence> _spawning;
  std::shared_ptr<AnimationSequence> _chasing;
};
