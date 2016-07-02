#include <iostream>
#include "console_log.h"

void ConsoleLog::Write(const std::string& buffer)
{
    std::cout << buffer.c_str() << std::endl;
}