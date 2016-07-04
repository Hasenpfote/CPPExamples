#pragma once
#include <iostream>
#include <string>
#include "service.h"

class LogService : public example::service::IService
{
public:
    LogService() = default;
    virtual ~LogService() = default;
    virtual void Write(const std::string& buffer)
    {
        std::cout << buffer << std::endl;
    }
};