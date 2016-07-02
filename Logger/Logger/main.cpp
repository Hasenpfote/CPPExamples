#include <sstream>
#include <thread>
#include "logger.h"
#include "console_log.h"
#include "file_log.h"

static Logger logger(std::make_shared<ConsoleLog>());
//static Logger logger(std::make_shared<FileLog>("log.txt"));

static constexpr auto max = 10;

void do_worker1()
{
    auto i = 0;
    std::ostringstream oss;
    oss << std::this_thread::get_id();
    while(i < max){
        logger.Log(Logger::Severity::Debug, __FILE__, __LINE__, oss.str());
        i++;
        std::this_thread::sleep_for(std::chrono::microseconds(1));
    }
}

void do_worker2()
{
    auto i = 0;
    std::ostringstream oss;
    oss << std::this_thread::get_id();
    while(i < max){
        logger.Log(Logger::Severity::Error, __FILE__, __LINE__, oss.str());
        i++;
        std::this_thread::sleep_for(std::chrono::microseconds(1));
    }
}

void main()
{
    //logger.SetSeverity(Logger::Severity::Fatal);

    std::thread t1(do_worker1);
    std::thread t2(do_worker2);
    t1.join();
    t2.join();
}