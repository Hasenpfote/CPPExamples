#pragma once
#include "logger2.h"
#include "singleton.h"

class SingletonLogger final : public Logger2, public Singleton<SingletonLogger>
{
    friend class Singleton<SingletonLogger>;
private:
    SingletonLogger() = default;
public:
    ~SingletonLogger() = default;
};