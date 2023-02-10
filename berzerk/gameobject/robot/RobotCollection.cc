#include "RobotCollection.hh"

#include "Color.hh"
#include "LevelHelpers.hh"
#include "LevelShootingProxy.hh"
#include "PlayerPositionProxy.hh"
#include "RobotAudioComponent.hh"
#include "RobotSpriteManager.hh"
#include "Time.hh"

RobotCollection::RobotCollection(const int levelNo, const std::vector<Vect2D>& startPositions,
                                 LevelShootingProxy& levelShootingProxy, DrawingProxy& drawingProxy,
                                 PlayerPositionProxy& playerPositionProxy, RobotSpriteManager& robotSpriteManager,
                                 const RobotAudioComponent& robotAudioComponent,
                                 const WallCollisionProxy& collisionProxy, const RobotWallAvoidancePolicy avoidWalls)
    : _robots(std::vector<std::unique_ptr<Robot>>()) {
  robotSpriteManager.setColorMask(getLevelColor(levelNo));

  for (size_t i = 0; i < startPositions.size(); i++) {
    this->_robots.push_back(std::unique_ptr<Robot>(new Robot(startPositions.at(i), Vect2D::zero(), levelShootingProxy,
                                                             drawingProxy, playerPositionProxy, robotSpriteManager,
                                                             robotAudioComponent, collisionProxy, avoidWalls)));
  }
}
Robot* RobotCollection::get(const size_t index) const { return this->_robots.at(index).get(); }
size_t RobotCollection::size() const { return this->_robots.size(); }

int RobotCollection::removeMarked() {
  int numberRemoved = 0;
  for (size_t i = 0; i < this->size(); i++) {
    if (this->_robots[i]->getShouldRemove()) {
      this->erase(i);
      numberRemoved++;
    }
  }
  return numberRemoved;
}

void RobotCollection::update(const TimerProxy& timerProxy) {
  for (size_t i = 0; i < this->size(); i++) {
    this->_robots[i]->update(timerProxy);
  }
}

void RobotCollection::erase(const size_t index) { this->_robots.erase(this->_robots.begin() + (long)index); }
