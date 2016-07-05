#include "service_locator.h"
#include "log_service.h"

static example::service::ServiceLocator sl;

void do_something()
{
    auto service = sl.GetService<LogService>();
    if(auto sp = service.lock()){
        sp->Write("Hello world.");
    }
}

void main()
{
    sl.RegisterService<LogService>(std::make_shared<LogService>());
    //sl.UnregisterService<LogService>();

    do_something();
}