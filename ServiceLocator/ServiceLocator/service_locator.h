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
    static void RegisterService(const std::shared_ptr<T>& object)
    {
#ifndef ENABLE_TYPE_TEST
        static_assert(std::is_base_of<IService, T>::value == true, "T must be derived from IService.");
#endif
        map[typeid(T).name()] = object;
    }

    template<typename T>
    static void UnregisterService()
    {
        auto& it = map.find(typeid(T).name());
        if(it != map.end()){
            map.erase(it);
        }
    }

    template<typename T>
    static std::weak_ptr<T> GetService()
    {
        auto ptr = map[typeid(T).name()];
        assert(ptr && "Unbale to find a service.");
#ifndef ENABLE_TYPE_TEST
        return std::dynamic_pointer_cast<T>(ptr);
#else
        return std::static_pointer_cast<T>(ptr);
#endif
    }
};