#pragma once
#include <memory>

template<typename T>
class Singleton
{
public:
    Singleton(const Singleton &) = delete;
    Singleton& operator=(const Singleton &) = delete;
    Singleton(Singleton &&) = delete;
    Singleton& operator=(Singleton &&) = delete;

    static T& GetInstance(){
        static std::unique_ptr<T> instance(T::CreateInstance());
        return *instance;
    }

private:
    static T* CreateInstance(){ return new T(); }

protected:
    Singleton() = default;
    ~Singleton() = default;

};