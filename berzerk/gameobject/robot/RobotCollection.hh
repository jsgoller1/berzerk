#pragma once

#include <vector>

#include "Configs.hh"
#include "GameObjectCollection.hh"
#include "Robot.hh"
#include "Time.hh"

// fwd decl
class LevelShootingProxy;
class PlayerPositionProxy;
class RobotSpriteManager;
class RobotAudioComponent;

class RobotCollection : public GameObjectCollection {
 public:
  // TODO: The default constructor here is stinky; there's no reason to create an empty robot collection since we have
  // no insert method (though we could). It exists solely so we can use it in Level's ctor() so RobotCollection can be
  // initialized, then replaced with a correctly constructed one.
  RobotCollection() = default;
  RobotCollection(const int levelNo, const std::vector<Vect2D>& startPositions, LevelShootingProxy& levelShootingProxy,
                  DrawingProxy& drawingProxy, PlayerPositionProxy& playerPositionProxy,
                  RobotSpriteManager& robotSpriteManager, const RobotAudioComponent& robotAudioComponent,
                  const WallCollisionProxy& collisionProxy,
                  const RobotWallAvoidancePolicy avoidWalls = RobotWallAvoidancePolicy::NEVER);
  Robot* get(const size_t index) const override;
  size_t size() const override;

  int removeMarked();
  void update(const TimerProxy& timerProxy);

 private:
  std::vector<std::unique_ptr<Robot>> _robots;

  void erase(const size_t index);
};
