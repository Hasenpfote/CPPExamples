#pragma once
#include <memory>
#include <string>

class ILog;

class Logger2 final
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
    Logger2();
    ~Logger2();

    Logger2(const Logger2&) = delete;
    Logger2& operator = (const Logger2&) = delete;
    Logger2(Logger2&&) = delete;
    Logger2& operator = (Logger2&&) = delete;

    void Provide(const std::shared_ptr<ILog>& log);
    void SetSeverity(Severity severity);
    void Log(Severity severity, const std::string& filename, int line, const std::string& message);
    void SetTimestampFormat(const std::string& format); // Use for std::put_time.

private:
    class Impl;
    std::unique_ptr<Impl> pimpl;
};