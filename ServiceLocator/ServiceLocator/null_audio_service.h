#pragma once
#include "audio_service.h"

class NullAudioService final : public IAudioService
{
public:
    NullAudioService() = default;
    ~NullAudioService() = default;
    void Play(const std::string& name) override {}
};