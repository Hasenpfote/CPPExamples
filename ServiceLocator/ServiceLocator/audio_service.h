#pragma once
#include "service_locator.h"

class IAudioService : public IService
{
public:
    IAudioService() = default;
    virtual ~IAudioService() = default;
    virtual void Play(const std::string& name) = 0;
};