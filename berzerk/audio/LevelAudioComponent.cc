#include "LevelAudioComponent.hh"

#include "Configs.hh"
#include "Math.hh"

LevelAudioComponent::LevelAudioComponent(const std::string& assetsDirPath)
    : AudioComponent(assetsDirPath),
      _levelExitClear(this->createMix_Chunk(LEVEL_EXIT_CLEAR_SOUND_PATH)),
      _levelExitCowardly(this->createMix_Chunk(LEVEL_EXIT_COWARDLY_SOUND_PATH)),
      _tauntAttackIt(this->createMix_Chunk(TAUNT_ATTACK_IT_SOUND_PATH)),
      _tauntAttackTheIntruder(this->createMix_Chunk(TAUNT_ATTACK_THE_INTRUDER_SOUND_PATH)),
      _tauntDestroyTheIntruder(this->createMix_Chunk(TAUNT_DESTROY_THE_INTRUDER_SOUND_PATH)),
      _tauntGetIt(this->createMix_Chunk(TAUNT_GET_IT_SOUND_PATH)),
      _tauntGetTheHumanoid(this->createMix_Chunk(TAUNT_GET_THE_HUMANOID_SOUND_PATH)),
      _tauntKillTheIntruder(this->createMix_Chunk(TAUNT_KILL_THE_INTRUDER_SOUND_PATH)) {}
void LevelAudioComponent::playEscapeBrave() const { this->playSound(this->_levelExitClear); }
void LevelAudioComponent::playEscapeCowardly() const { this->playSound(this->_levelExitCowardly); }
void LevelAudioComponent::playRandomizedTaunt() const {
  int tauntChoice = randInt(0, 5);
  switch (tauntChoice) {
    case 0:
      this->playSound(this->_tauntAttackIt);
      break;
    case 1:
      this->playSound(this->_tauntAttackTheIntruder);
      break;
    case 2:
      this->playSound(this->_tauntDestroyTheIntruder);
      break;
    case 3:
      this->playSound(this->_tauntGetIt);
      break;
    case 4:
      this->playSound(this->_tauntGetTheHumanoid);
      break;
    case 5:
      this->playSound(this->_tauntKillTheIntruder);
      break;
    default:
      break;
  }
}
