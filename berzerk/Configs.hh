#pragma once
#include <set>
#include <string>

#include "Vect2D.hh"

// Sprite sheet paths
const std::string LEVEL_SPRITE_SHEET_PATH = std::string{"textures/level-sprites.png"};
const std::string PLAYER_SPRITE_SHEET_PATH = std::string{"textures/player-sprites.png"};
const std::string ROBOT_SPRITE_SHEET_PATH = std::string{"textures/robot-sprites.png"};
const std::string OTTO_SPRITE_SHEET_PATH = std::string{"textures/otto-sprites.png"};
const std::string BULLET_SPRITE_SHEET_PATH = std::string{"textures/bullet-sprites.png"};
const std::string TEXT_SPRITE_SHEET_PATH = std::string{"textures/text-sprites.png"};

// Audio paths
const std::string LEVEL_EXIT_CLEAR_SOUND_PATH = std::string{"audio/level/level-exit-clear.mp3"};
const std::string LEVEL_EXIT_COWARDLY_SOUND_PATH = std::string{"audio/level/level-exit-cowardly.mp3"};
const std::string TAUNT_ATTACK_IT_SOUND_PATH = std::string{"audio/level/taunt-attack-it.mp3"};
const std::string TAUNT_ATTACK_THE_INTRUDER_SOUND_PATH =
    std::string{"audio/level/taunt-attack-the-intruder.mp3"};
const std::string TAUNT_DESTROY_THE_INTRUDER_SOUND_PATH =
    std::string{"audio/level/taunt-destroy-the-intruder.mp3"};
const std::string TAUNT_GET_IT_SOUND_PATH = std::string{"audio/level/taunt-get-it.mp3"};
const std::string TAUNT_GET_THE_HUMANOID_SOUND_PATH =
    std::string{"audio/level/taunt-get-the-humanoid.mp3"};
const std::string TAUNT_KILL_THE_INTRUDER_SOUND_PATH =
    std::string{"audio/level/taunt-kill-the-intruder.mp3"};
const std::string OTTO_INTRUDER_ALERT_SOUND_PATH =
    std::string{"audio/otto/otto-entry-intruder-alert.mp3"};
const std::string PLAYER_DEATH_SOUND_PATH = std::string{"audio/player/player-death.mp3"};
const std::string PLAYER_SHOOTING_SOUND_PATH = std::string{"audio/player/player-shooting.wav"};
const std::string ROBOT_DEATH_SOUND_PATH = std::string{"audio/robot/robot-death.mp3"};
const std::string ROBOT_SHOOTING_SOUND_PATH = std::string{"audio/robot/robot-shoot.mp3"};

// Screen
constexpr int DEFAULT_SCREEN_WIDTH = 1400;
constexpr int DEFAULT_SCREEN_HEIGHT = 900;
constexpr int INTERNAL_PLAY_AREA_WIDTH = DEFAULT_SCREEN_WIDTH - 200;
constexpr int INTERNAL_PLAY_AREA_HEIGHT = DEFAULT_SCREEN_HEIGHT - 200;

// Player behavior
constexpr int PLAYER_MAX_X = (INTERNAL_PLAY_AREA_WIDTH / 2);
constexpr int PLAYER_MIN_X = -PLAYER_MAX_X;
constexpr int PLAYER_MAX_Y = (INTERNAL_PLAY_AREA_HEIGHT / 2);
constexpr int PLAYER_MIN_Y = -PLAYER_MAX_Y;
constexpr int PLAYER_ANIMATION_FRAME_SHOW_LENGTH_MS = 30;
constexpr int PLAYER_DYING_ANIMATION_LOOP_COUNT = 2;
constexpr int PLAYER_SHOOT_DELAY_MS = 750;
constexpr int PLAYER_MOVE_SPEED = 5;

// Player sprite
constexpr int PLAYER_SPRITE_WIDTH_PX = 8;
constexpr int PLAYER_SPRITE_HEIGHT_PX = 16;
constexpr int PLAYER_SPRITE_BOUNDARY_WIDTH_PX = 1;
constexpr int PLAYER_DEFAULT_WIDTH = 35;
constexpr int PLAYER_DEFAULT_HEIGHT = 70;

// Robot behavior
// TODO: Robot should move, shoot, and animate faster as fewer remain
constexpr int ROBOT_COUNT = 3;
constexpr int ROBOT_MOVE_SPEED = 1;
constexpr int ROBOT_DEFAULT_WIDTH = 40;
constexpr int ROBOT_DEFAULT_HEIGHT = 55;
constexpr int ROBOT_DYING_WIDTH = 80;
constexpr int ROBOT_DYING_HEIGHT = 80;
constexpr int ROBOT_SHOOT_DELAY_MS = 750;
constexpr int ROBOT_PURSUIT_DISTANCE_PX = 900;
constexpr int ROBOT_SHOOTING_ERROR_MARGIN_PX = 15;
enum RobotWallAvoidancePolicy
{
    ALWAYS,
    SOMETIMES,
    NEVER
};

// Robot sprite
constexpr int ROBOT_ANIMATION_FRAME_SHOW_LENGTH_MS = 150;
constexpr int ROBOT_SPRITE_WIDTH_PX = 8;
constexpr int ROBOT_SPRITE_HEIGHT_PX = 12;
constexpr int ROBOT_SPRITE_BOUNDARY_WIDTH_PX = 1;
constexpr int ROBOT_DYING_SPRITE_HEIGHT_PX = 16;
constexpr int ROBOT_DYING_SPRITE_WIDTH_PX = 16;

// Bullet behavior
constexpr int BULLET_DEFAULT_SPEED = 7;
constexpr int BULLET_DEFAULT_HEIGHT = 25;
constexpr int BULLET_DEFAULT_WIDTH = 25;

// Bullet sprite
constexpr int BULLET_SPRITE_WIDTH_PX = 7;
constexpr int BULLET_SPRITE_HEIGHT_PX = 7;
constexpr int BULLET_SPRITE_BOUNDARY_WIDTH_PX = 2;

// Otto sprite
constexpr int OTTO_SPRITE_WIDTH_PX = 8;
constexpr int OTTO_SPRITE_HEIGHT_PX = 16;
constexpr int OTTO_CHARACTER_WIDTH_PX = 50;
constexpr int OTTO_CHARACTER_HEIGHT_PX = 50;
constexpr int OTTO_SPRITE_BOUNDARY_WIDTH_PX = 1;

// Wall behavior
constexpr int WALL_THICCNESS = 10;
constexpr int VERTICAL_WALL_WIDTH = WALL_THICCNESS;
constexpr int VERTICAL_WALL_HEIGHT = INTERNAL_PLAY_AREA_HEIGHT / 3;
constexpr int HORIZONTAL_WALL_WIDTH = INTERNAL_PLAY_AREA_WIDTH / 5;
constexpr int HORIZONTAL_WALL_HEIGHT = WALL_THICCNESS;

// Level behavior, see Level.hh for explanation of what indexes represent
constexpr int EXIT_N = 2;
constexpr int EXIT_S = 17;
constexpr int EXIT_W = 26;
constexpr int EXIT_E = 31;
const std::set<int> HORIZONTAL_EXIT_WALLS{EXIT_N, EXIT_S};
const std::set<int> VERTICAL_EXIT_WALLS{EXIT_W, EXIT_E};
const std::set<int> HORIZONTAL_BORDER_WALLS{0, 1, 3, 4, 15, 16, 18, 19};
const std::set<int> VERTICAL_BORDER_WALLS{20, 32, 25, 37};
const std::set<int> HORIZONTAL_INTERNAL_WALLS{5, 6, 7, 8, 9, 10, 11, 12, 13, 14};
const std::set<int> VERTICAL_INTERNAL_WALLS{21, 22, 23, 24, 27, 28, 29, 30, 33, 34, 35, 36};
constexpr int GENERATED_WALL_COUNT = 6;
constexpr int ROOM_COUNT = 15;

const Vect2D CELL_0_CENTER = Vect2D(-HORIZONTAL_WALL_WIDTH * 2, VERTICAL_WALL_HEIGHT);
const Vect2D NORTH_SPAWN = Vect2D(0, VERTICAL_WALL_HEIGHT);
const Vect2D EAST_SPAWN = Vect2D(HORIZONTAL_WALL_WIDTH * 2, 0);
const Vect2D SOUTH_SPAWN = Vect2D(0, -VERTICAL_WALL_HEIGHT);
const Vect2D WEST_SPAWN = Vect2D(HORIZONTAL_WALL_WIDTH * -2, 0);

// UI Behavior
constexpr int LEVEL_UI_MARGIN_VERTICAL_WIDTH = 40;
constexpr int UI_SCOREBOARD_DIGIT_PLACES = 5;
constexpr int TEXT_SPRITE_WIDTH_PX = 8;
constexpr int TEXT_SPRITE_HEIGHT_PX = 9;
constexpr int TEXT_SPRITE_BOUNDARY_WIDTH_PX = 1;
constexpr int TEXT_WIDTH_PX = 20;
constexpr int TEXT_HEIGHT_PX = 30;
constexpr int TEXT_BOUNDARY_WIDTH_PX = 5;
const Vect2D UI_TOP_LEFT =
    Vect2D((-INTERNAL_PLAY_AREA_WIDTH / 2) + 20, (-INTERNAL_PLAY_AREA_HEIGHT / 2) - LEVEL_UI_MARGIN_VERTICAL_WIDTH);
// const Vect2D UI_TOP_LEFT = Vect2D(0, 0);

// Misc
constexpr int DEFAULT_ANIMATION_FRAME_SHOW_LENGTH_MS = 150;
const Vect2D TOP_LEFT = Vect2D::zero();
constexpr int BULLET_SPAWN_HORIZONTAL_OFFSET_DISTANCE_PX = 30;
constexpr int BULLET_SPAWN_VERTICAL_OFFSET_DISTANCE_PX = 45;
constexpr int NO_COLLISION = -1;
constexpr int ROBOT_KILLED_SCORE = 50;
constexpr int SCORE_LEVEL_THRESHOLD = 200;
constexpr int LEVEL_START_DELAY_MS = 2000;
constexpr int ROBOT_COLLISION_TEST_MOVES_COUNT = 15;
constexpr int OTTO_ENTRANCE_TIME_THRESHOLD_MS = 15000; // 15 seconds
constexpr int OTTO_JUMP_VERTICAL_MOVEMENT_DELAY_MS = 200;
const Vect2D OTTO_FIRST_JUMP_OFFSET_PX = Vect2D(0, 25);
const Vect2D OTTO_STANDARD_JUMP_OFFSET_PX = Vect2D(0, 10);
constexpr int LEVEL_TAUNT_FREQUENCY_MS = 4000;
