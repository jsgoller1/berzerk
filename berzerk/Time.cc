#include "Time.hh"

TimerProxy::TimerProxy(const Timer& timer) : _timer(timer) {}
time_ms TimerProxy::getCurrentTime() const { return this->_timer.getCurrentTime(); }
time_ms TimerProxy::getTimeDelta() const { return this->_timer.getTimeDelta(); }

Timer::Timer() { this->reset(); }

void Timer::tick() {
  this->_previousTick = this->_currentTick;
  this->_currentTick = SDL_GetTicks64();
}

void Timer::reset() {
  this->_startTime = SDL_GetTicks64();
  this->_currentTick = this->_startTime;
  this->_previousTick = this->_startTime;
}

time_ms Timer::getCurrentTime() const { return this->_currentTick - this->_startTime; }
time_ms Timer::getTimeDelta() const { return this->_currentTick - this->_previousTick; }
TimerProxy& Timer::getProxy() { return this->_proxy; }
