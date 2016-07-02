#pragma once
#include <memory>
#include <fstream>
#include <filesystem>
#include "log.h"

class FileLog final : public ILog
{
private:
    std::unique_ptr<std::ofstream> ofs;

public:
    FileLog(const std::tr2::sys::path& filepath)
        : ofs(std::make_unique<std::ofstream>(filepath))
    {
    }
    ~FileLog() = default;
    void Write(const std::string& buffer) override;
};