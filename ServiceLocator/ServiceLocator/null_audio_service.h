#pragma once
#include <iostream>
#include "audio_service.h"

class NullAudioService final : public IAudioService
{
public:
    NullAudioService() = default;
    ~NullAudioService()
    {
        std::cout << __func__ << std::endl;
    }
    void Play(const std::string& name) override {}
};