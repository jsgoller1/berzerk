#pragma once

#include <string>

#include "SDL2/SDL_mixer.h"

class AudioComponent {
 public:
  AudioComponent(const std::string& assetsDirPath);
  const std::string& getAssetsDirPath() const;

 protected:
  void playSound(Mix_Chunk* sound) const;
  Mix_Chunk* createMix_Chunk(const std::string& rpath) const;

 private:
  const std::string& _assetsDirPath;
};
