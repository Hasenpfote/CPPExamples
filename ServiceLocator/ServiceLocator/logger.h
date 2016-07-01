#pragma once
#include <sstream>
#include "singleton.h"

class Logger final : public Singleton<Logger>
{
    friend class Singleton<Logger>;
public:
    enum class Severity
    {
        Verbose = 0,
        Debug = 1,
        Info = 2,
        Warning = 3,
        Error = 4,
        Fatal = 5
    };

private:
    Severity severity;

private:
    Logger() : severity(Severity::Verbose)
    {
    }

public:
    ~Logger() = default;

    void Log(const std::string& message);
    void SetSeverity(Severity severity){ this->severity = severity; }
    Severity GetSeverity() const { return severity; }
    std::string GetTimestamp() const;

    template<Severity severity>
    std::string GetSeverityString() const
    {
        switch(severity){
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
};

#define SHORT_FILENAME (std::strrchr(__FILE__, '/') ? std::strrchr(__FILE__, '/') + 1 : std::strrchr(__FILE__, '\\') ? std::strrchr(__FILE__, '\\') + 1 : __FILE__)

#define LOG(severity, message)\
    do{\
        auto& inst = Logger::GetInstance();\
        if(severity >= inst.GetSeverity()){\
            std::ostringstream oss;\
            oss << inst.GetTimestamp() << " " << inst.GetSeverityString<severity>() << SHORT_FILENAME << "(" << __LINE__ << ") - " << message;\
            inst.Log(oss.str());\
        }\
    }while(false)
#define NOLOG(message)\
    do{\
        static_cast<void>((true ? static_cast<void>(0) : static_cast<void>((std::ostringstream() << message))));\
    }while(false)

#ifdef NDEBUG
#define LOG_V(message)  NOLOG(message)
#define LOG_D(message)  NOLOG(message)
#define LOG_I(message)  LOG(Logger::Severity::Info, message)
#define LOG_W(message)  LOG(Logger::Severity::Warning, message)
#define LOG_E(message)  LOG(Logger::Severity::Error, message)
#define LOG_F(message)  LOG(Logger::Severity::Fatal, message)
#else
#define LOG_V(message)  LOG(Logger::Severity::Verbose, message)
#define LOG_D(message)  LOG(Logger::Severity::Debug, message)
#define LOG_I(message)  LOG(Logger::Severity::Info, message)
#define LOG_W(message)  LOG(Logger::Severity::Warning, message)
#define LOG_E(message)  LOG(Logger::Severity::Error, message)
#define LOG_F(message)  LOG(Logger::Severity::Fatal, message)
#endif