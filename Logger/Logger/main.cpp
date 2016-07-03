#include <iostream>
#include <sstream>
#include <thread>
#include "console_log.h"
#include "file_log.h"
#include "rolling_file_log.h"

#define ENABLE_SINGLETON_LOGGER
#define ENABLE_LOGGER2

#ifdef ENABLE_SINGLETON_LOGGER
#include "singleton_logger.h"
#else
 #ifndef ENABLE_LOGGER2
#include "logger.h"
static Logger logger(std::make_shared<ConsoleLog>());
//static Logger logger(std::make_shared<FileLog>("Logs/log.txt"));
//static Logger logger(std::make_shared<RollingFileLog>("Logs/log.txt", 10));
#else
#include "logger2.h"
static Logger2 logger;
#endif
#endif

static constexpr auto max_output = 1000;

void do_worker()
{
    auto i = 0;
    auto id = std::this_thread::get_id();
    std::ostringstream oss;
    while(i < max_output){
        oss << "[" << id << "] - " << i;
#ifdef ENABLE_SINGLETON_LOGGER
        SingletonLogger::GetInstance().Log(Logger2::Severity::Debug, __FILE__, __LINE__, oss.str());
#else
 #ifndef ENABLE_LOGGER2
        logger.Log(Logger::Severity::Debug, __FILE__, __LINE__, oss.str());
 #else
        logger.Log(Logger2::Severity::Debug, __FILE__, __LINE__, oss.str());
 #endif
#endif
        i++;
        std::this_thread::sleep_for(std::chrono::milliseconds(1));
        oss.str("");
        oss.clear(std::stringstream::goodbit);
    }
}

void main()
{
#ifdef ENABLE_SINGLETON_LOGGER
    SingletonLogger::GetInstance().SetSeverity(Logger2::Severity::Debug);
    SingletonLogger::GetInstance().Provide(std::make_shared<ConsoleLog>());
#else
 #ifdef ENABLE_LOGGER2
    //logger.Provide(std::make_shared<RollingFileLog>("Logs/log.txt", 10));
    logger.Provide(std::make_shared<ConsoleLog>());
 #endif
    //logger.SetSeverity(Logger::Severity::Fatal);
#endif
    std::thread t1(do_worker);
    std::thread t2(do_worker);
    t1.join();
    t2.join();
    std::cout << "Done." << std::endl;
}