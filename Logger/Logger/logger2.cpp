#include <cassert>
#include <sstream>
#include <chrono>
#include <iomanip>
#include <mutex>
#include "log.h"
#include "logger2.h"

static std::string GetTimestamp(std::string& format)
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
    ss << std::put_time(&tm, format.c_str());
    return ss.str();
}

static std::string SeverityToString(Logger2::Severity severity)
{
    switch(severity){
    case Logger2::Severity::Verbose:
        return "V";
    case Logger2::Severity::Debug:
        return "D";
    case Logger2::Severity::Info:
        return "I";
    case Logger2::Severity::Warning:
        return "W";
    case Logger2::Severity::Error:
        return "E";
    case Logger2::Severity::Fatal:
        return "F";
    default:
        return "U";
    }
}

class NullLog final : public ILog
{
public:
    NullLog() = default;
    ~NullLog() = default;
    void Write(const std::string& buffer){}
};

class Logger2::Impl final
{
public:
    Impl()
    {
        null_log = std::make_shared<NullLog>();
        log = null_log;
        format = "%Y/%m/%d %T";
    }
    ~Impl() = default;

    Impl(const Impl&) = delete;
    Impl& operator = (const Impl&) = delete;
    Impl(Impl&&) = delete;
    Impl& operator = (Impl&&) = delete;

    void Provide(const std::shared_ptr<ILog>& log);
    void SetSeverity(Severity severity);
    void Log(Severity severity, const std::string& filename, int line, const std::string& message);
    void SetTimestampFormat(const std::string& format);

private:
    std::shared_ptr<ILog> log;
    std::shared_ptr<ILog> null_log;
    Severity severity;
    std::string format;
    std::mutex m;
};

void Logger2::Impl::Provide(const std::shared_ptr<ILog>& log)
{
    std::lock_guard<std::mutex> lg(m);
    this->log = (log)? log : null_log;
}

void Logger2::Impl::SetSeverity(Severity severity)
{
    std::lock_guard<std::mutex> lg(m);
    this->severity = severity;
}

void Logger2::Impl::Log(Severity severity, const std::string& filename, int line, const std::string& message)
{
    std::lock_guard<std::mutex> lg(m);
    if(severity < this->severity)
        return;
    auto s = SeverityToString(severity);
    std::ostringstream oss;
    oss << GetTimestamp(format) << " " << s << "/" << filename << "(" << line << ") - " << message;
    log->Write(oss.str());
}

void Logger2::Impl::SetTimestampFormat(const std::string& format)
{
    std::lock_guard<std::mutex> lg(m);
    this->format = format;
};

Logger2::Logger2()
    : pimpl(std::make_unique<Impl>())
{
}

Logger2::~Logger2() = default;

void Logger2::Provide(const std::shared_ptr<ILog>& log)
{
    pimpl->Provide(log);
}

void Logger2::SetSeverity(Severity severity)
{
    pimpl->SetSeverity(severity);
}

void Logger2::Log(Severity severity, const std::string& filename, int line, const std::string& message)
{
    pimpl->Log(severity, filename, line, message);
}

void Logger2::SetTimestampFormat(const std::string& format)
{
    pimpl->SetTimestampFormat(format);
}