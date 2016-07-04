/*!
* @file service_locator.h
* @brief Service locator class.
* @author Hasenpfote
* @date 2016/07/04
*/
#pragma once
#include <unordered_map>
#include <memory>
#include <cassert>

namespace example{ namespace service{

class IService;

class ServiceLocator
{
public:
    ServiceLocator() = default;
    virtual ~ServiceLocator() = default;

    ServiceLocator(const ServiceLocator&) = delete;
    ServiceLocator& operator = (const ServiceLocator&) = delete;
    ServiceLocator(ServiceLocator&&) = delete;
    ServiceLocator& operator = (ServiceLocator&&) = delete;

    template<typename T>
    void RegisterService(const std::shared_ptr<IService>& service)
    {
        static_assert(std::is_base_of<IService, T>::value == true, "T must be derived from IService.");
        this->service[typeid(T).name()] = service;
    }

    template<typename T>
    void UnregisterService()
    {
        static_assert(std::is_base_of<IService, T>::value == true, "T must be derived from IService.");
        auto& it = service.find(typeid(T).name());
        if(it != service.end()){
            service.erase(it);
        }
    }

    template<typename T>
    std::weak_ptr<T> GetService() const
    {
        static_assert(std::is_base_of<IService, T>::value == true, "T must be derived from IService.");
        auto& it = service.find(typeid(T).name());
        if(it != service.cend()){
            return std::dynamic_pointer_cast<T>(it->second);
        }
        assert(!"Unbale to find a service.");
        return std::weak_ptr<T>();
    }

private:
    std::unordered_map<std::string, std::shared_ptr<IService>> service;
};

}}