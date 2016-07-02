#include <iostream>
#include <sstream>
#include <thread>
#include "logger.h"
#include "console_log.h"
#include "file_log.h"
#include "rolling_file_log.h"

//static Logger logger(std::make_shared<ConsoleLog>());
//static Logger logger(std::make_shared<FileLog>("Logs/log.txt"));
static Logger logger(std::make_shared<RollingFileLog>("Logs/log.txt", 10));

static constexpr auto max_output = 1000;

void do_worker()
{
    auto i = 0;
    auto id = std::this_thread::get_id();
    std::ostringstream oss;
    while(i < max_output){
        oss << "[" << id << "] - " << i;
        logger.Log(Logger::Severity::Debug, __FILE__, __LINE__, oss.str());
        i++;
        std::this_thread::sleep_for(std::chrono::milliseconds(1));
        oss.str("");
        oss.clear(std::stringstream::goodbit);
    }
}

void main()
{
    //logger.SetSeverity(Logger::Severity::Fatal);
    std::thread t1(do_worker);
    std::thread t2(do_worker);
    t1.join();
    t2.join();
    std::cout << "Done." << std::endl;
}