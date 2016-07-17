/*!
* @file singleton.h
* @brief CRTP(Curiously Recurring Template Pattern) singleton class.
* @author Hasenpfote
* @date 2016/07/15
*/
#pragma once
#include <memory>
#include <functional>
#include <mutex>

//#define ENABLE_BIND_VERSION

namespace example{

#ifndef ENABLE_BIND_VERSION
// GetInstance の引数は何でも受け付ける.
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

    static std::once_flag& GetOnceFlag();

    static std::unique_ptr<T> instance;
};
#else
// GetInstance の引数は rvalue を受け付けない.
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
    static T& GetInstance(const Arguments&... args);

    static T& Apply(const std::function<T*()>& func);

    template<typename... Arguments>
    static T* CreateInstance(const Arguments&... args);
};
#endif
}

#include "impl/singleton_impl.h"