#include <iostream>
#include "console_log_service.h"

ConsoleLogService::~ConsoleLogService()
{
    std::cout << __func__ << std::endl;
}

void ConsoleLogService::Write(const std::string& buffer)
{
    std::cout << buffer.c_str() << std::endl;
}