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

#define ENABLE_TEST_1       // 引数は何でも受け付ける.
//#define ENABLE_TEST_2       // 引数は rvalue を受け付けない.


namespace example{

#ifdef ENABLE_TEST_1
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
    static T& GetMutableInstance(Arguments&&... args)
    {
        return GetInstance(std::forward<Arguments>(args)...);
    }

    template<typename... Arguments>
    static const T& GetConstInstance(Arguments&&... args)
    {
        return GetInstance(std::forward<Arguments>(args)...);
    }

private:
    template<typename... Arguments>
    static T& GetInstance(Arguments&&... args)
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

    static std::once_flag& GetOnceFlag()
    {
        static std::once_flag once;
        return once;
    }

    static std::unique_ptr<T> instance;
};

template<typename T> std::unique_ptr<T> Singleton<T>::instance = nullptr;
#endif
#ifdef ENABLE_TEST_2
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
    static T& GetInstance(const Arguments&... args)
    {
        // インスタンスの多重生成の回避.
        static auto once_func = std::bind(CreateInstance<Arguments...>, std::ref(args)...); // 値渡しの回避.
        return Apply(once_func);
    }

private:
    static T& Apply(const std::function<T*()>& func)
    {
        static std::unique_ptr<T> instance(func()); // 一度だけ初期化される.
        return *instance;
    }

    template<typename... Arguments>
    static T* CreateInstance(const Arguments&... args)
    {
        return new T(args...);
    }
};
#endif

}