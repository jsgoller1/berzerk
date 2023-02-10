#include "OttoAudioComponent.hh"

#include "Configs.hh"

OttoAudioComponent::OttoAudioComponent(const std::string& assetsDirPath)
    : AudioComponent(assetsDirPath), _intruderAlert(this->createMix_Chunk(OTTO_INTRUDER_ALERT_SOUND_PATH)) {}
void OttoAudioComponent::playIntruderAlert() const { this->playSound(this->_intruderAlert); }
