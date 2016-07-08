#include "file_appender.h"

namespace example{ namespace mylog{

FileAppender::FileAppender(const std::tr2::sys::path& filepath)
    : ofs(std::make_unique<std::ofstream>(filepath))
{
}

void FileAppender::Write(const std::string& buffer)
{
    *ofs << buffer.c_str() << std::endl;
}

}}