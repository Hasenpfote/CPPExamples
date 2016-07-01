#include <iostream>
#include "service_locator.h"
#include "console_log_service.h"
#include "file_log_service.h"
#include "null_audio_service.h"
#include "unknown_service.h"
#include "logger.h"

void main()
{
    auto& inst = ServiceLocator::GetInstance();
    std::weak_ptr<ILogService> log_service;
    // console
    {
        auto clog = std::make_unique<ConsoleLogService>();
        inst.RegisterService<ILogService>(std::move(clog));
    }
    log_service = inst.GetService<ILogService>();
    if(auto sp = log_service.lock()){
        sp->Write("aaaaaa");
    }

    Logger::GetInstance().SetSeverity(Logger::Severity::Verbose);
    LOG_V("verbose");
    LOG_D("debug");
    LOG_I("info");
    LOG_W("warning");
    LOG_E("error");
    LOG_F("fatal");

    // file
    {
        auto flog = std::make_unique<FileLogService>("log.txt");
        inst.RegisterService<ILogService>(std::move(flog));
    }
    log_service = inst.GetService<ILogService>();
    if(auto sp = log_service.lock()){
        sp->Write("aaaaaa");
    }
    // audio
    {
        //auto audio = std::make_unique<NullAudioService>();
        //ServiceLocator::RegisterService<IAudioService>(std::move(audio));
        auto audio = std::make_shared<NullAudioService>();
        inst.RegisterService<IAudioService>(audio);
    }
    auto audio_service = inst.GetService<IAudioService>();
#if 1
    inst.UnregisterService<IAudioService>();
#endif
    if(auto sp = audio_service.lock()){
        sp->Play("aaaaaa");
    }
    //
#ifdef ENABLE_TYPE_TEST
    {
        auto unknown = std::unique_ptr<IUnknownService>(new IUnknownService());
        inst.RegisterService<IUnknownService>(std::move(unknown));
    }
    auto unknown_service = inst.GetService<IUnknownService>();
    if(auto sp = unknown_service.lock()){
        sp->DoSomething();
    }
#endif
}