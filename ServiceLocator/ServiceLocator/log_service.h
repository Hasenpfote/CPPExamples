#pragma once
#include "service_locator.h"

class ILogService : public IService
{
public:
    ILogService() = default;
    virtual ~ILogService() = default;
    virtual void Write(const std::string& buffer) = 0;
};