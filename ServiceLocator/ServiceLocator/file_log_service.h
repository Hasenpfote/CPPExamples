#pragma once
#include <fstream>
#include <filesystem>
#include "log_service.h"

class FileLogService final : public ILogService
{
public:
    explicit FileLogService(const std::tr2::sys::path& filepath);
    ~FileLogService();
    void Write(const std::string& buffer) override;

private:
    std::unique_ptr<std::ofstream> ofs;
};