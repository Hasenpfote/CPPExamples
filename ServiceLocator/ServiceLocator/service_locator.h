#pragma once
#include <memory>
#include <unordered_map>
#include <cassert>
#include "service.h"
#include "singleton.h"

//#define ENABLE_TYPE_TEST

class ServiceLocator final : public Singleton<ServiceLocator>
{
    friend class Singleton<ServiceLocator>;
private:
#ifndef ENABLE_TYPE_TEST
    std::unordered_map<std::string, std::shared_ptr<IService>> service;
#else
    std::unordered_map<std::string, std::shared_ptr<void>> service;
#endif
private:
    ServiceLocator() = default;
public:
    ~ServiceLocator() = default;

public:
    template<typename T>
    void RegisterService(const std::shared_ptr<T>& object)
    {
#ifndef ENABLE_TYPE_TEST
        static_assert(std::is_base_of<IService, T>::value == true, "T must be derived from IService.");
#endif
        service[typeid(T).name()] = object;
    }

    template<typename T>
    void UnregisterService()
    {
#ifndef ENABLE_TYPE_TEST
        std::unordered_map<std::string, std::shared_ptr<IService>>::const_iterator it = service.find(typeid(T).name());
#else
        std::unordered_map<std::string, std::shared_ptr<void>>::const_iterator it = service.find(typeid(T).name());
#endif
        if(it != service.cend()){
            service.erase(it);
        }
    }

    template<typename T>
    std::weak_ptr<T> GetService() const
    {
#ifndef ENABLE_TYPE_TEST
        std::unordered_map<std::string, std::shared_ptr<IService>>::const_iterator it = service.find(typeid(T).name());
#else
        std::unordered_map<std::string, std::shared_ptr<void>>::const_iterator it = service.find(typeid(T).name());
#endif
        if(it != service.cend()){
#ifndef ENABLE_TYPE_TEST
            return std::dynamic_pointer_cast<T>(it->second);
#else
            return std::static_pointer_cast<T>(it->second);
#endif
        }
        assert(!"Unbale to find a service.");
        return std::weak_ptr<T>();
    }
};