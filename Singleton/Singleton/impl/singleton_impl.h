#pragma once

namespace example{
#ifndef ENABLE_BIND_VERSION
template<typename T> std::unique_ptr<T> Singleton<T>::instance = nullptr;

template<typename T>
template<typename... Arguments>
T& Singleton<T>::GetMutableInstance(Arguments&&... args)
{
    return GetInstance(std::forward<Arguments>(args)...);
}

template<typename T>
template<typename... Arguments>
const T& Singleton<T>::GetConstInstance(Arguments&&... args)
{
    return GetInstance(std::forward<Arguments>(args)...);
}

template<typename T>
template<typename... Arguments>
T& Singleton<T>::GetInstance(Arguments&&... args)
{
    std::call_once(
        GetOnceFlag(),
        [](Arguments&&... args)
            {
                std::cout << "initialize." << std::endl;
                instance.reset(new T(std::forward<Arguments>(args)...));
            },
        std::forward<Arguments>(args)...
        );
    return *instance;
}

template<typename T>
std::once_flag& Singleton<T>::GetOnceFlag()
{
    static std::once_flag once;
    return once;
}
#else
template<typename T>
template<typename... Arguments>
T& Singleton<T>::GetMutableInstance(Arguments&&... args)
{
    return GetInstance(args...);
}

template<typename T>
template<typename... Arguments>
const T& Singleton<T>::GetConstInstance(Arguments&&... args)
{
    return GetInstance(args...);
}

template<typename T>
template<typename... Arguments>
T& Singleton<T>::GetInstance(const Arguments&... args)
{
    // インスタンスの多重生成の回避.
    static auto once_func = std::bind(CreateInstance<Arguments...>, std::ref(args)...); // 値渡しの回避.
    return Apply(once_func);
}

template<typename T>
T& Singleton<T>::Apply(const std::function<T*()>& func)
{
    static std::unique_ptr<T> instance(func()); // 一度だけ初期化される.
    return *instance;
}

template<typename T>
template<typename... Arguments>
T* Singleton<T>::CreateInstance(const Arguments&... args)
{
    return new T(args...);
}
#endif
}