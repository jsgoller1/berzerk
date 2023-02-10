#pragma once

#include "AudioComponent.hh"

class LevelAudioComponent : public AudioComponent {
 public:
  LevelAudioComponent(const std::string& assetsDirPath);
  void playEscapeBrave() const;
  void playEscapeCowardly() const;
  void playRandomizedTaunt() const;

 private:
  Mix_Chunk* _levelExitClear;
  Mix_Chunk* _levelExitCowardly;
  Mix_Chunk* _tauntAttackIt;
  Mix_Chunk* _tauntAttackTheIntruder;
  Mix_Chunk* _tauntDestroyTheIntruder;
  Mix_Chunk* _tauntGetIt;
  Mix_Chunk* _tauntGetTheHumanoid;
  Mix_Chunk* _tauntKillTheIntruder;
};
