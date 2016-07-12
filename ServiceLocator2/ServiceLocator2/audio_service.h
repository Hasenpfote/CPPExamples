#pragma once
#include <iostream>
#include <string>
#include "service.h"

class AudioService : public example::service::IService
{
public:
    AudioService() = default;
    virtual ~AudioService() = default;
    virtual void Play(const std::string& buffer)
    {
    }
};