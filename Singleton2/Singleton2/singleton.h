/*!
* @file singleton.h
* @brief CRTP(Curiously Recurring Template Pattern) singleton class.
* @author Hasenpfote
* @date 2016/07/19
*/
#pragma once
#include <memory>
#include <functional>
#include <mutex>
#include <stack>

namespace example{

class SingletonFinalizer final
{
    using Callback = std::function<void()>;

public:
    static void Register(const Callback& cb);
    static void Finalize();

private:
    static std::stack<Callback> cbs;
};

template<typename T>
class Singleton
{
protected:
    Singleton() = default;
    ~Singleton() = default;

public:
    Singleton(const Singleton&) = delete;
    Singleton& operator=(const Singleton&) = delete;
    Singleton(Singleton&&) = delete;
    Singleton& operator=(Singleton&&) = delete;

    template<typename... Arguments>
    static T& GetMutableInstance(Arguments&&... args);

    template<typename... Arguments>
    static const T& GetConstInstance(Arguments&&... args);

private:
    template<typename... Arguments>
    static T& GetInstance(Arguments&&... args);

    static void DestroyInstance();

    static std::once_flag& GetOnceFlag();

    static std::unique_ptr<T> instance;
};

}

#include "impl/singleton_impl.h"