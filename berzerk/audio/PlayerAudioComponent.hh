#pragma once

#include "AudioComponent.hh"

class PlayerAudioComponent : public AudioComponent {
 public:
  PlayerAudioComponent(const std::string& assetsDirPath);
  void playShooting() const;
  void playDeath() const;

 private:
  Mix_Chunk* _shooting;
  Mix_Chunk* _death;
};
