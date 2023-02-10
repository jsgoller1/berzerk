#include "AudioComponent.hh"

AudioComponent::AudioComponent(const std::string& assetsDirPath) : _assetsDirPath(assetsDirPath) {}
const std::string& AudioComponent::getAssetsDirPath() const { return this->_assetsDirPath; }
void AudioComponent::playSound(Mix_Chunk* sound) const { Mix_PlayChannel(-1, sound, 0); }
Mix_Chunk* AudioComponent::createMix_Chunk(const std::string& rpath) const {
  return Mix_LoadWAV((this->_assetsDirPath + rpath).c_str());
}
