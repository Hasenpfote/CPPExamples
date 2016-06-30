#include <iostream>
#include "service_locator.h"
#include "console_log_service.h"
#include "file_log_service.h"
#include "null_audio_service.h"

class IUnknownService
{
public:
    IUnknownService() = default;
    virtual ~IUnknownService() = default;
    virtual void DoSomething()
    {
        std::cout << __func__ << std::endl;
    }
};

void main()
{
    ILogService* log_service = nullptr;
    // console
    {
        auto clog = std::unique_ptr<ConsoleLogService>(new ConsoleLogService());
        ServiceLocator::Provide<ILogService>(std::move(clog));
    }
    log_service = ServiceLocator::GetService<ILogService>();
    if(log_service){
        log_service->Write("aaaaaa");
    }
    // file
    {
        auto flog = std::unique_ptr<FileLogService>(new FileLogService("log.txt"));
        ServiceLocator::Provide<ILogService>(std::move(flog));
    }
    log_service = ServiceLocator::GetService<ILogService>();
    if(log_service){
        log_service->Write("aaaaaa");
    }
    // audio
    {
        auto audio = std::unique_ptr<NullAudioService>(new NullAudioService());
        ServiceLocator::Provide<IAudioService>(std::move(audio));
    }
    auto audio_service = ServiceLocator::GetService<IAudioService>();
    audio_service->Play("aaaaaa");
    //
#ifdef ENABLE_TYPE_TEST
    {
        auto unknown = std::unique_ptr<IUnknownService>(new IUnknownService());
        ServiceLocator::Provide<IUnknownService>(std::move(unknown));
    }
    auto unknown_service = ServiceLocator::GetService<IUnknownService>();
    unknown_service->DoSomething();
#endif
}