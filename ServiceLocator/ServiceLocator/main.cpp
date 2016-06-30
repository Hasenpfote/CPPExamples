#include <iostream>
#include "service_locator.h"
#include "console_log_service.h"
#include "file_log_service.h"
#include "null_audio_service.h"
#include "unknown_service.h"

void main()
{
    std::weak_ptr<ILogService> log_service;
    // console
    {
        auto clog = std::make_unique<ConsoleLogService>();
        ServiceLocator::RegisterService<ILogService>(std::move(clog));
    }
    log_service = ServiceLocator::GetService<ILogService>();
    if(auto sp = log_service.lock()){
        sp->Write("aaaaaa");
    }
    // file
    {
        auto flog = std::make_unique<FileLogService>("log.txt");
        ServiceLocator::RegisterService<ILogService>(std::move(flog));
    }
    log_service = ServiceLocator::GetService<ILogService>();
    if(auto sp = log_service.lock()){
        sp->Write("aaaaaa");
    }
    // audio
    {
        //auto audio = std::make_unique<NullAudioService>();
        //ServiceLocator::RegisterService<IAudioService>(std::move(audio));
        auto audio = std::make_shared<NullAudioService>();
        ServiceLocator::RegisterService<IAudioService>(audio);
    }
    auto audio_service = ServiceLocator::GetService<IAudioService>();
#if 1
    ServiceLocator::UnregisterService<IAudioService>();
#endif
    if(auto sp = audio_service.lock()){
        sp->Play("aaaaaa");
    }
    //
#ifdef ENABLE_TYPE_TEST
    {
        auto unknown = std::unique_ptr<IUnknownService>(new IUnknownService());
        ServiceLocator::RegisterService<IUnknownService>(std::move(unknown));
    }
    auto unknown_service = ServiceLocator::GetService<IUnknownService>();
    if(auto sp = unknown_service.lock()){
        sp->DoSomething();
    }
#endif
}