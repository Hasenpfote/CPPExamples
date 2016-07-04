#include "file_appender.h"

namespace example{ namespace mylog{

void FileAppender::Write(const std::string& buffer)
{
    *ofs << buffer.c_str() << std::endl;
}

}}