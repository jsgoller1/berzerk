#pragma once

#include <memory>
#include <string>
#include <vector>

#include "Configs.hh"
#include "Sprite.hh"
#include "Time.hh"

class AnimationSequence {
  /*
   * AnimationSequence is an opaque container containing a selection of images from a spritesheet to be
   * used in an animation, along with logic/state for animating them.
   */
 public:
  AnimationSequence(const std::string name, int loopLimit = -1);
  AnimationSequence(const std::string name, const std::shared_ptr<Sprite> sprite, int loopLimit = -1);
  AnimationSequence(const std::string name, const std::vector<std::shared_ptr<Sprite>> sprites,
                    const time_ms frameShowLength, int loopLimit = -1);
  void addSprite(const std::shared_ptr<Sprite> sprite);

  void setFrameShowLength(const time_ms frameShowLength);
  time_ms getFrameShowLength() const;
  time_ms getSinceLastUpdate() const;

  bool loopsIndefinitely();
  bool isComplete();
  std::shared_ptr<Sprite> getCurrentSprite() const;
  void update(const TimerProxy& timerProxy);
  void reset();

 private:
  std::string _name;
  int _loopLimit = -1;
  int _loopCount = 0;
  time_ms _sinceLastUpdate = 0;
  time_ms _frameShowLength = DEFAULT_ANIMATION_FRAME_SHOW_LENGTH_MS;
  unsigned int _spriteIdx = 0;
  std::vector<std::shared_ptr<Sprite>> _sprites;
};
