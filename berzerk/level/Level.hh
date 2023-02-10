#pragma once
#include <memory>
#include <string>
#include <vector>

#include "BulletCollection.hh"
#include "Configs.hh"
#include "LevelAudioComponent.hh"
#include "LevelShootingProxy.hh"
#include "Otto.hh"
#include "Player.hh"
#include "Robot.hh"
#include "RobotCollection.hh"
#include "Time.hh"
#include "Vect2D.hh"
#include "Wall.hh"
#include "WallCollection.hh"

// Fwd decls
class Bullet;
class BulletSpriteManager;
class Direction;
class DrawingProxy;
class InputHandler;
class LevelSpriteManager;
class OttoSpriteManager;
class PlayerSpriteManager;
class PlayerPositionProxy;
class RobotSpriteManager;
class LevelDataProxy;

/*
 * Berserk levels are always the same size and are always constructed the same way,
 * so we can safely label each wall and then use constants to grab specific ones.
 * We can also index each cell in a similar fashion (shown by numbers in the center of each cell)
 *
 *   ————0———— ————1———— ————2———— ————3————  ————4————
 *  |         |         |         |          |         |
 *  20   0    21   1    22   2    23   3     24   4    25
 *  |         |         |         |          |         |
 *   ————5———— ————6———— ————7———— ————8————— ————9————
 *  |         |         |         |          |         |
 *  26   5    27   6    28   7    29   8     30   9    31
 *  |         |         |         |          |         |
 *   ————10——— ————11——— ————12——— ————13———— ————14————
 *  |         |         |         |          |         |
 *  32   10   33   11   34   12   35   13    36   14   37
 *  |         |         |         |          |         |
 *   ————15——— ————16——— ————17——— ————18———— ————19————
 */

class Level {
 public:
  Level(const int levelNo, LevelDataProxy& levelDataProxy, DrawingProxy& drawingProxy,
        const LevelSpriteManager& levelSpriteManager, const LevelAudioComponent& levelAudioComponent,
        const PlayerSpriteManager& playerSpriteManager, const PlayerAudioComponent& playerAudioComponent,
        RobotSpriteManager& robotSpriteManager, const RobotAudioComponent& robotAudioComponent,
        OttoSpriteManager& ottoSpriteManager, const OttoAudioComponent& ottoAudioComponent,
        BulletSpriteManager& bulletSpriteManager);

  void update(const InputHandler& inputHandler, const TimerProxy& timerProxy);
  void draw();

  bool isFinished() const;
  bool isCleared() const;
  bool playerAtExit() const;
  Direction getPlayerExit() const;

 private:
  // Level
  LevelAudioComponent _levelAudioComponent;
  DrawingProxy& _drawingProxy;
  LevelDataProxy& _levelDataProxy;

  // Walls
  WallCollection _walls;

  // Player
  Player _player;
  PlayerPositionProxy _playerPositionProxy;

  // Robots
  RobotCollection _robots;

  // Bullets
  BulletCollection _bullets;
  LevelShootingProxy _levelShootingProxy;

  // Otto
  Otto _otto;

  void handleCollisions();
  void removeMarked();
  std::vector<Vect2D> generateRobotStartPositions(const int robotsCount);
  std::vector<int> randomizeInternalWalls();
  std::vector<int> generateWalls();
  Vect2D getPlayerSpawnPoint();
  RobotWallAvoidancePolicy getRobotWallAvoidancePolicy(const int levelNo) const;
  void handleTauntingSounds(const TimerProxy& timerProxy);
  time_ms _sinceLastTaunt = 0;
};
