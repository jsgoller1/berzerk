#include "Level.hh"

#include <iostream>

#include "Bullet.hh"
#include "BulletSpriteManager.hh"
#include "Configs.hh"
#include "Direction.hh"
#include "InputHandler.hh"
#include "LevelAudioComponent.hh"
#include "LevelDataProxy.hh"
#include "LevelHelpers.hh"
#include "LevelSpriteManager.hh"
#include "Math.hh"
#include "OttoAudioComponent.hh"
#include "OttoSpriteManager.hh"
#include "PlayerPositionProxy.hh"
#include "PlayerSpriteManager.hh"
#include "RobotAudioComponent.hh"
#include "RobotSpriteManager.hh"

Level::Level(const int levelNo, LevelDataProxy& levelDataProxy, DrawingProxy& drawingProxy,
             const LevelSpriteManager& levelSpriteManager, const LevelAudioComponent& levelAudioComponent,
             const PlayerSpriteManager& playerSpriteManager, const PlayerAudioComponent& playerAudioComponent,
             RobotSpriteManager& robotSpriteManager, const RobotAudioComponent& robotAudioComponent,
             OttoSpriteManager& ottoSpriteManager, const OttoAudioComponent& ottoAudioComponent,
             BulletSpriteManager& bulletSpriteManager)
    : _levelAudioComponent(levelAudioComponent),
      _drawingProxy(drawingProxy),
      _levelDataProxy(levelDataProxy),
      _walls(this->generateWalls(), levelSpriteManager, this->_drawingProxy),
      _player(Player(getPlayerSpawnPoint(), Vect2D(0, 0), this->_levelShootingProxy, drawingProxy, playerSpriteManager,
                     playerAudioComponent)),
      _playerPositionProxy(PlayerPositionProxy(this->_player)),
      _robots(levelNo, this->generateRobotStartPositions(ROBOT_COUNT), this->_levelShootingProxy, this->_drawingProxy,
              this->_playerPositionProxy, robotSpriteManager, robotAudioComponent, this->_walls.getWallCollisionProxy(),
              this->getRobotWallAvoidancePolicy(levelNo)),
      _bullets(levelNo, bulletSpriteManager, drawingProxy),
      _levelShootingProxy(LevelShootingProxy(this->_bullets)),
      _otto(Otto(levelNo, Vect2D(-2000, -2000), this->_drawingProxy, this->_playerPositionProxy, ottoSpriteManager,
                 ottoAudioComponent)) {}

void Level::update(const InputHandler& inputHandler, const TimerProxy& timerProxy) {
  this->_robots.update(timerProxy);
  this->_player.update(inputHandler, timerProxy);
  this->_bullets.update(timerProxy);
  this->_otto.update(timerProxy);
  this->handleTauntingSounds(timerProxy);

  this->handleCollisions();
  this->removeMarked();
}

void Level::draw() {
  // The drawing order here matters; we want to draw robots before walls, so their explosion animation is drawn under
  // wall (otherwise it will block out part of the wall; might want to use color keying for this. Player's death
  // animation should be drawn over the wall, so they are drawn last.
  this->_robots.draw();
  this->_player.draw();
  this->_bullets.draw();
  this->_walls.draw();
  this->_otto.draw();
}

bool Level::isFinished() const { return this->playerAtExit() || this->_player.isDead(); }

bool Level::isCleared() const { return this->_robots.size() == 0; }

Direction Level::getPlayerExit() const {
  // TODO: For now, these are hardcoded. Will this work if the screen is larger and the textures are scaled up?

  Vect2D pos = this->_player.getPosition();
  Direction exit = Direction::None();
  if (pos.x <= PLAYER_MIN_X) {
    exit = Direction::West();
  } else if (PLAYER_MAX_X <= pos.x) {
    exit = Direction::East();
  } else if (pos.y <= PLAYER_MIN_Y) {
    exit = Direction::South();
  } else if (PLAYER_MAX_Y <= pos.y) {
    exit = Direction::North();
  }
  return exit;
}

bool Level::playerAtExit() const { return this->getPlayerExit() != Direction::None(); }

void Level::handleCollisions() {
  /*
  - Player dies if they collide with robots, bullets, otto, or walls
  - Robots die if they collide with player, robotos, bullets, otto, or walls
  - Bullets disappear if they collide with player, walls, robots, or otto
  - Otto and walls never disappear; Otto can pass through everything

  So we can cover all the above by testing as follows:
  - Player against robots, bullets, otto, and walls
  - Robots against robots, bullets, otto, and walls
  - Bullets against otto and walls

  There are not going to be that many walls, robots, or projectiles; probably 10
  robots and a player, each of whom can fire a projectile (so 22 objects at most). We
  could try doing 22 x 22 collision tests, but then we have to test walls on top of
  that. Another option would be a kind of space partitioning; we maintain a
  list-of-lists of the contents of every room (walls, projectiles, and characters). A
  character or projectile would test (based on its corners) what room its in before
  moving and then after, then update the list-of-lists accordingly. We also don't need
  to test collisions on anything that didn't move.
  */

  // NOTE: Bullet collisions need to be handled before player; otherwise, if a bullet collides with a wall and a player,
  // it will wind up killing the player. Same thing with robot collisions; there's an edge case where a player and robot
  // are standing very close on either side of a wall. If the robot explodes, its sprite will expand but it should not
  // cause the player to die (since there's a wall between them). Testing for robot/wall collisions before robot/player
  // collisions ensures this won't happen.

  this->_bullets.collisionTestAndResolve(&this->_otto);
  this->_bullets.collisionTestAndResolve(&this->_walls);

  this->_robots.collisionTestAndResolve(&this->_player);
  this->_bullets.collisionTestAndResolve(&this->_player);
  this->_walls.collisionTestAndResolve(&this->_player);
  if (this->_otto.collisionTest(this->_player)) {
    this->_player.resolveCollision(this->_otto);
    this->_otto.resolveCollision(this->_player);
  }

  this->_robots.collisionTestAndResolve(&this->_robots);
  this->_bullets.collisionTestAndResolve(&this->_robots);
  this->_walls.collisionTestAndResolve(&this->_robots);
  this->_robots.collisionTestAndResolve(&this->_otto);
}

void Level::removeMarked() {
  this->_bullets.removeMarked();
  int robotsKilled = this->_robots.removeMarked();
  if (!this->_player.isDead()) {
    // NOTE: In the original arcade, the player's score goes up any time a robot dies as long as the player isn't dead,
    // even if it's from a wall collision or robot friendly fire. This encourages the player to attempt to outsmart the
    // pathfinding system, and also incentivizes surviving longer.
    this->_levelDataProxy.addScore(ROBOT_KILLED_SCORE * robotsKilled);
  }
}

static Vect2D getOffset(const int i) {
  switch (i) {
    case 0:
      return Vect2D(Direction::South()) * int(ROBOT_DEFAULT_HEIGHT * 1.3);
    case 1:
      return Vect2D(Direction::North()) * int(ROBOT_DEFAULT_HEIGHT * 1.3);
    case 2:
      return Vect2D(Direction::East()) * ROBOT_DEFAULT_WIDTH * 2;
    default:
      return Vect2D(Direction::West()) * ROBOT_DEFAULT_WIDTH * 2;
  }
}

std::vector<Vect2D> Level::generateRobotStartPositions(const int robotsCount) {
  // TODO: Robots need to be generated to they don't spawn on top of player or walls. To do this,
  // We pick the center of a random room, then pick whether the robot spawns at the center or slightly offset to
  // N/S/E/W (but not close enough to hit the wall or the player), then use a set to ensure we don't put two in the same
  // place.
  std::set<Vect2D> startPositionsSet{};

  while ((int)startPositionsSet.size() < robotsCount) {
    startPositionsSet.insert(getCellCenter(randInt(0, 14)) + getOffset(randInt(0, 3)));
  }

  return std::vector<Vect2D>(startPositionsSet.begin(), startPositionsSet.end());
}

std::vector<int> Level::randomizeInternalWalls() {
  std::set<int> chosenWalls = std::set<int>();
  std::set<int> allInternalWallsSet = HORIZONTAL_INTERNAL_WALLS;
  allInternalWallsSet.insert(VERTICAL_INTERNAL_WALLS.begin(), VERTICAL_INTERNAL_WALLS.end());
  std::vector<int> allInternalWalls = std::vector<int>(allInternalWallsSet.begin(), allInternalWallsSet.end());
  while (chosenWalls.size() < GENERATED_WALL_COUNT) {
    chosenWalls.insert(allInternalWalls.at((size_t)randInt(0, (int)allInternalWalls.size() - 1)));
  }
  return std::vector<int>(chosenWalls.begin(), chosenWalls.end());
}

std::vector<int> Level::generateWalls() {
  std::vector<int> walls = this->randomizeInternalWalls();

  for (auto it = HORIZONTAL_BORDER_WALLS.begin(); it != HORIZONTAL_BORDER_WALLS.end(); it++) {
    walls.push_back(*it);
  }
  for (auto it = VERTICAL_BORDER_WALLS.begin(); it != VERTICAL_BORDER_WALLS.end(); it++) {
    walls.push_back(*it);
  }

  return walls;
}

Vect2D Level::getPlayerSpawnPoint() { return Vect2D(0, 250); }

RobotWallAvoidancePolicy Level::getRobotWallAvoidancePolicy(const int levelNo) const {
  if (levelNo == 0) {
    return RobotWallAvoidancePolicy::SOMETIMES;
  } else if (levelNo < 3) {
    return RobotWallAvoidancePolicy::SOMETIMES;
  } else {
    return RobotWallAvoidancePolicy::ALWAYS;
  }
}

void Level::handleTauntingSounds(const TimerProxy& timerProxy) {
  this->_sinceLastTaunt += timerProxy.getTimeDelta();
  if (this->_sinceLastTaunt >= LEVEL_TAUNT_FREQUENCY_MS) {
    this->_sinceLastTaunt = 0;
    this->_levelAudioComponent.playRandomizedTaunt();
  }
}
