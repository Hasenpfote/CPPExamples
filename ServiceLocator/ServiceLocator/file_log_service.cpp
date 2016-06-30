#include "file_log_service.h"

FileLogService::FileLogService(const std::tr2::sys::path& filepath)
{
    ofs = std::unique_ptr<std::ofstream>(new std::ofstream());
    ofs->open(filepath.string(), std::ios::out);
    if(ofs->fail()){
        throw std::runtime_error("Unable to open an output stream.");
    }
}

#include <iostream>
FileLogService::~FileLogService()
{
    std::cout << __func__ << std::endl;
}

void FileLogService::Write(const std::string& buffer)
{
    *ofs << buffer.c_str() << std::endl;
}