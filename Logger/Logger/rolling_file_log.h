#pragma once
#include <cassert>
#include <memory>
#include <fstream>
#include <filesystem>
#include "log.h"

class RollingFileLog final : public ILog
{
private:
    std::unique_ptr<std::ofstream> ofs;
    std::tr2::sys::path filepath;
    std::size_t max_file_size;
    int max_files;

public:
    RollingFileLog(const std::tr2::sys::path& filepath, int max_files = 1, std::size_t max_file_size = 1024)
        : ofs(std::make_unique<std::ofstream>()), filepath(filepath), max_files(max_files), max_file_size(max_file_size)
    {
        assert(max_files > 0);
    }
    ~RollingFileLog() = default;
    void Write(const std::string& buffer) override;
};