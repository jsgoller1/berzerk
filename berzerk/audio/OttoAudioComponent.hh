#pragma once

#include <string>

#include "AudioComponent.hh"

class OttoAudioComponent : public AudioComponent {
 public:
  OttoAudioComponent(const std::string& assetsDirPath);
  void playIntruderAlert() const;

 private:
  Mix_Chunk* _intruderAlert;
};
