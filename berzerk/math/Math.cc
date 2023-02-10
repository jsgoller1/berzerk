#include "Math.hh"

#include <random>

int randInt(const int rangeMin, const int rangeMax) {
  // obtain a random number from hardware
  std::random_device rd;
  // seed the generator
  std::mt19937 gen(rd());
  // define the range
  std::uniform_int_distribution<> distribution(rangeMin, rangeMax);

  return distribution(gen);
}

int absval(int val) { return val * ((val > 0) ? 1 : -1); }
