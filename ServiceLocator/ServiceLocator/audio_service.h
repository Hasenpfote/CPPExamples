#pragma once
#include "service.h"

class IAudioService : public IService
{
public:
    IAudioService() = default;
    virtual ~IAudioService() = default;
    virtual void Play(const std::string& name) = 0;
};