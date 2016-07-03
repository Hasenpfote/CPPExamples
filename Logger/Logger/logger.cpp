#include <sstream>
#include <chrono>
#include <iomanip>
#include "log.h"
#include "logger.h"

static std::string GetTimestamp()
{
    const auto now = std::chrono::system_clock::now();
    const auto time = std::chrono::system_clock::to_time_t(now);
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

static std::string SeverityToString(Logger::Severity severity)
{
    switch(severity){
    case Logger::Severity::Verbose:
        return "V";
    case Logger::Severity::Debug:
        return "D";
    case Logger::Severity::Info:
        return "I";
    case Logger::Severity::Warning:
        return "W";
    case Logger::Severity::Error:
        return "E";
    case Logger::Severity::Fatal:
        return "F";
    default:
        return "U";
    }
}

void Logger::SetSeverity(Severity severity)
{
    std::lock_guard<std::mutex> lg(m);
    this->severity = severity;
}

void Logger::Log(Severity severity, const std::string& filename, int line, const std::string& message)
{
    std::lock_guard<std::mutex> lg(m);
    if(severity < this->severity)
        return;
    auto s = SeverityToString(severity);
    std::ostringstream oss;
    oss << GetTimestamp() << " " << s << "/" << filename << "(" << line << ") - " << message;
    log->Write(oss.str());
}