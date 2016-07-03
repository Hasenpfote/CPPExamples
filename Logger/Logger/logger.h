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

public:
    Logger(const std::shared_ptr<ILog>& log) : log(log), severity(Severity::Verbose)
    {
    }
    ~Logger() = default;

    Logger(const Logger&) = delete;
    Logger& operator = (const Logger&) = delete;
    Logger(Logger&&) = delete;
    Logger& operator = (Logger&&) = delete;

    void SetSeverity(Severity severity);
    void Log(Severity severity, const std::string& filename, int line, const std::string& message);

private:
    std::shared_ptr<ILog> log;
    Severity severity;
    std::mutex m;
};