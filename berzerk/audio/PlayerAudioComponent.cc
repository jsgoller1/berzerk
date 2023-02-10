#include "PlayerAudioComponent.hh"

#include "Configs.hh"

PlayerAudioComponent::PlayerAudioComponent(const std::string& assetsDirPath)
    : AudioComponent(assetsDirPath),
      _shooting(this->createMix_Chunk(PLAYER_SHOOTING_SOUND_PATH)),
      _death(this->createMix_Chunk(PLAYER_DEATH_SOUND_PATH)) {}

void PlayerAudioComponent::playShooting() const { this->playSound(this->_shooting); }
void PlayerAudioComponent::playDeath() const { this->playSound(this->_death); }
