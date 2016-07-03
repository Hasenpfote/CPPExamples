#pragma once
#include <memory>
#include <mutex>

class ILog;

class Logger final
{
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
    std::shared_ptr<ILog> log;
    Severity severity;
    std::mutex m;

public:
    Logger(const std::shared_ptr<ILog> log) : log(log), severity(Severity::Verbose)
    {
    }
    ~Logger() = default;

    void SetSeverity(Severity severity);
    void Log(Severity severity, const std::string& filename, int line, const std::string& message);
};