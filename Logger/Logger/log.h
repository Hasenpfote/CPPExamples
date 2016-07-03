#pragma once
#include <string>

class ILog
{
public:
    ILog() = default;
    virtual ~ILog() = default;

    ILog(const ILog&) = delete;
    ILog& operator = (const ILog&) = delete;
    ILog(ILog&&) = delete;
    ILog& operator = (ILog&&) = delete;

    virtual void Write(const std::string& buffer) = 0;
};