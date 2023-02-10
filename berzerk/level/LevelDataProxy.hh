#pragma once

class LevelDataProxy {
 public:
  LevelDataProxy(int* const gameScore, int* const livesCount);
  void addScore(const int addedAmount);
  int getScore() const;
  int getLivesCount() const;

 private:
  int* const _gameScore;
  int* const _livesCount;
};
