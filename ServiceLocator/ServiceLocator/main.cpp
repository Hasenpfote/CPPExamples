#include "service_locator.h"
#include "console_log_service.h"
#include "file_log_service.h"
#include "null_audio_service.h"

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
#if 1
    {
        auto audio = std::unique_ptr<NullAudioService>(new NullAudioService());
        ServiceLocator::Provide<IAudioService>(std::move(audio));
    }
#endif
    auto audio_service = ServiceLocator::GetService<IAudioService>();
}