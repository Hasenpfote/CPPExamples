#pragma once
#include <string>

class ILog
{
public:
    ILog() = default;
    virtual ~ILog() = default;
    virtual void Write(const std::string& buffer) = 0;
};