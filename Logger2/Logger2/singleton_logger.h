#pragma once
#include "logger.h"
#include "singleton.h"

class Logger final : public mylog::Logger, public Singleton<Logger>
{
    friend class Singleton<Logger>;
private:
    Logger() = default;
public:
    ~Logger() = default;
};