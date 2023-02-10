#include "LevelDataProxy.hh"

LevelDataProxy::LevelDataProxy(int* const gameScore, int* const livesCount)
    : _gameScore(gameScore), _livesCount(livesCount) {}
void LevelDataProxy::addScore(const int addedAmount) { (*this->_gameScore) += addedAmount; }
int LevelDataProxy::getScore() const { return *this->_gameScore; }
int LevelDataProxy::getLivesCount() const { return *this->_livesCount; }
