#pragma once
#include <sstream>

class Logger final
{
public:
    enum class Severity
    {
        Verbose,
        Debug,
        Info,
        Warning,
        Error,
        Fatal
    };

public:
    Logger() = delete;
    ~Logger() = delete;

    static std::string GetTime();

    template<Severity severity>
    static std::string Logger::GetSeverity()
    {
        switch (severity) {
        case Severity::Verbose:
            return "V/";
        case Severity::Debug:
            return "D/";
        case Severity::Info:
            return "I/";
        case Severity::Warning:
            return "W/";
        case Severity::Error:
            return "E/";
        case Severity::Fatal:
            return "F/";
        default:
            return "U/";
        }
    }

    static void Log(const std::string& buffer);
};

#define LOG(severity, message)\
    do{\
        std::ostringstream oss;\
        oss << Logger::GetTime() << " " << Logger::GetSeverity<severity>() << __FILE__ << "(" << __LINE__ << ") " << message;\
        Logger::Log(oss.str());\
    }while(false)

#define LOG_V(message)  LOG(Logger::Severity::Verbose, message)
#define LOG_D(message)  LOG(Logger::Severity::Debug, message)
#define LOG_I(message)  LOG(Logger::Severity::Info, message)
#define LOG_W(message)  LOG(Logger::Severity::Warning, message)
#define LOG_E(message)  LOG(Logger::Severity::Error, message)
#define LOG_F(message)  LOG(Logger::Severity::Fatal, message)