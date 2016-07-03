﻿/*!
* @file rolling_file_appender.h
* @brief Log appender for file.
* @author Hasenpfote
* @date 2016/07/03
*/
#pragma once
#include <fstream>
#include <memory>
#include <filesystem>
#include <cassert>
#include "appender.h"

namespace mylog{

class RollingFileAppender final : public IAppender
{
public:
    RollingFileAppender(const std::tr2::sys::path& filepath, int max_files = 1, std::size_t max_file_size = 1024)
        : ofs(std::make_unique<std::ofstream>()), filepath(filepath), max_files(max_files), max_file_size(max_file_size)
    {
        assert(max_files > 0);
    }
    ~RollingFileAppender() = default;
    void Write(const std::string& buffer) override;

private:
    std::unique_ptr<std::ofstream> ofs;
    std::tr2::sys::path filepath;
    std::size_t max_file_size;
    int max_files;
};

}