#pragma once

namespace example{ namespace mylog{

template<typename T>
void Logger::AddAppender(const std::shared_ptr<IAppender>& appender)
{
    static_assert(std::is_base_of<IAppender, T>::value == true, "T must be derived from IAppender.");
    AddAppender(typeid(T), appender);
}

template<typename T>
void Logger::RemoveAppender()
{
    static_assert(std::is_base_of<IAppender, T>::value == true, "T must be derived from IAppender.");
    RemoveAppender(typeid(T));
}

}}