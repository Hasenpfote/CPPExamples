#include <chrono>
#include <iomanip>
#include "service_locator.h"
#include "log_service.h"
#include "logger.h"

std::string Logger::GetTimestamp() const
{
    auto now = std::chrono::system_clock::now();
    auto time = std::chrono::system_clock::to_time_t(now);
    std::tm tm;
#ifdef _WIN32
    localtime_s(&tm, &time);
#else
#error Platform not supported.
#endif
    std::stringstream ss;
    ss << std::put_time(&tm, "%c");
    return ss.str();
}

void Logger::Log(const std::string& message)
{
    auto service = ServiceLocator::GetInstance().GetService<ILogService>();
    if(auto sp = service.lock()){
        sp->Write(message);
    }
}