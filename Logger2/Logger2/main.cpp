#include <thread>
#include <sstream>
#include <iostream>
#include "singleton_logger.h"
#include "console_appender.h"
#include "rolling_file_appender.h"

static constexpr auto max_output = 10;

static void do_worker()
{
    auto i = 0;
    auto id = std::this_thread::get_id();
    auto& inst = Logger::GetInstance();
    while(i < max_output){
        LOG_D("[" << id << "] - " << i);
        i++;
        std::this_thread::sleep_for(std::chrono::milliseconds(1));
    }
}

void main()
{
#ifdef NDEBUG
    Logger::GetInstance().SetSeverity(Logger::Severity::Fatal);
#else
    Logger::GetInstance().SetSeverity(Logger::Severity::Verbose);
#endif
    Logger::GetInstance().AddAppender<mylog::ConsoleAppender>(std::make_shared<mylog::ConsoleAppender>());
    Logger::GetInstance().AddAppender<mylog::RollingFileAppender>(std::make_shared<mylog::RollingFileAppender>("Logs/log.txt", 10));
    Logger::GetInstance().RemoveAppender<mylog::RollingFileAppender>();

    std::thread t1(do_worker);
    std::thread t2(do_worker);
    t1.join();
    t2.join();
    std::cout << "Done." << std::endl;
}