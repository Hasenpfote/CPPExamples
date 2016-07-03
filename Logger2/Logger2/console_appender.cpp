#include <iostream>
#include "console_appender.h"

namespace mylog{

void ConsoleAppender::Write(const std::string& buffer)
{
    std::cout << buffer.c_str() << std::endl;
}

}