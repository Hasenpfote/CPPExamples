#pragma once
#include "log_service.h"

class ConsoleLogService final : public ILogService
{
public:
    ConsoleLogService() = default;
    ~ConsoleLogService();
    void Write(const std::string& buffer);
};