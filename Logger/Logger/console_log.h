#pragma once
#include "log.h"

class ConsoleLog final : public ILog
{
public:
    ConsoleLog() = default;
    ~ConsoleLog() = default;
    void Write(const std::string& buffer) override;
};