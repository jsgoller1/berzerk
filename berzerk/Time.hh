#pragma once

#include "SDL2/SDL.h"

// TODO: may want sleep() method

typedef Uint64 time_ms;

// Fwd decl
class Timer;

class TimerProxy {
 public:
  TimerProxy(const Timer& SDL_TimerID);
  time_ms getCurrentTime() const;
  time_ms getTimeDelta() const;

 private:
  const Timer& _timer;
};

class Timer {
 public:
  Timer();
  void tick();
  void reset();
  time_ms getCurrentTime() const;
  time_ms getTimeDelta() const;

  TimerProxy& getProxy();

 private:
  time_ms _startTime;
  time_ms _currentTick;
  time_ms _previousTick;
  TimerProxy _proxy = TimerProxy(*this);
};
