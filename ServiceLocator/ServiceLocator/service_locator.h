#pragma once
#include <memory>
#include <unordered_map>
#include <cassert>

//#define ENABLE_TYPE_TEST

class IService
{
public:
    IService() = default;
    virtual ~IService() = default;
};

class ServiceLocator final
{
private:
#ifndef ENABLE_TYPE_TEST
    static std::unordered_map<std::string, std::shared_ptr<IService>> map;
#else
    static std::unordered_map<std::string, std::shared_ptr<void>> map;
#endif

public:
    ServiceLocator() = delete;
    ~ServiceLocator() = delete;

    template<typename T>
    static void Provide(const std::shared_ptr<T>& object)
    {
        map[typeid(T).name()] = object;
    }

    template<typename T>
    static T* GetService()
    {
        auto ptr = map[typeid(T).name()];
        assert(ptr && "Unbale to find a service.");
        return std::static_pointer_cast<T>(ptr).get();
    }
};