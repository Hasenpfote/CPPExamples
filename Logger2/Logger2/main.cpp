#include <thread>
#include <sstream>
#include <iostream>
#include "singleton_logger.h"
#include "console_appender.h"
#include "rolling_file_appender.h"

static constexpr auto max_output = 1000;

static void do_worker()
{
    auto i = 0;
    auto id = std::this_thread::get_id();
    std::ostringstream oss;
    auto& inst = Logger::GetInstance();
    while(i < max_output){
        oss << "[" << id << "] - " << i;
        inst.Log(Logger::Severity::Debug, __FILE__, __LINE__, oss.str());
        i++;
        std::this_thread::sleep_for(std::chrono::milliseconds(1));
        oss.str("");
        oss.clear(std::stringstream::goodbit);
    }
}

void main()
{
    Logger::GetInstance().AddAppender<mylog::ConsoleAppender>(std::make_shared<mylog::ConsoleAppender>());
    Logger::GetInstance().AddAppender<mylog::RollingFileAppender>(std::make_shared<mylog::RollingFileAppender>("Logs/log.txt", 10));

    std::thread t1(do_worker);
    std::thread t2(do_worker);
    t1.join();
    t2.join();
    std::cout << "Done." << std::endl;
}