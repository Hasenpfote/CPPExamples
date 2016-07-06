#include <thread>
#include "service_locator.h"
#include "log_service.h"
#include "audio_service.h"

static example::service::ServiceLocator sl;

void do_something()
{
    auto service = sl.GetService<LogService>();
    if(auto sp = service.lock()){
        sp->Write("Hello world.");
    }
}

void do_work1()
{
    constexpr auto max_count = 300;
    auto count = 0;
    while(count < max_count){
        auto service = sl.GetService<LogService>();
        if(auto sp = service.lock()){
            sp->Write("aaa");
        }
        if((count % 2) == 0){
            sl.UnregisterService<AudioService>();
        }
        else{
            sl.RegisterService<AudioService>(std::make_shared<AudioService>());
        }
        count++;
    }
}

void do_work2()
{
    constexpr auto max_count = 300;
    auto count = 0;
    while(count < max_count){
        auto service = sl.GetService<AudioService>();
        if(auto sp = service.lock()){
            sp->Play("bbb");
        }
        count++;
    }
}

void main()
{
    sl.RegisterService<LogService>(std::make_shared<LogService>());
    //sl.UnregisterService<LogService>();
    do_something();

    sl.RegisterService<AudioService>(std::make_shared<AudioService>());
    std::thread th1(do_work1);
    std::thread th2(do_work2);
    th1.join();
    th2.join();
}