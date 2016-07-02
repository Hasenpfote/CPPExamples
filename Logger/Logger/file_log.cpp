#include "file_log.h"

void FileLog::Write(const std::string& buffer)
{
    *ofs << buffer.c_str() << std::endl;
}