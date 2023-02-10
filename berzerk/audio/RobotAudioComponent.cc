#include "RobotAudioComponent.hh"

#include "Configs.hh"

RobotAudioComponent::RobotAudioComponent(const std::string& assetsDirPath)
    : AudioComponent(assetsDirPath),
      _shooting(this->createMix_Chunk(ROBOT_SHOOTING_SOUND_PATH)),
      _death(this->createMix_Chunk(ROBOT_DEATH_SOUND_PATH)) {}
void RobotAudioComponent::playShooting() const { this->playSound(this->_shooting); }
void RobotAudioComponent::playDeath() const { this->playSound(this->_death); }
