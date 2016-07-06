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
#include <typeindex>

#define ENABLE_THREAD_SAFE

#ifdef ENABLE_THREAD_SAFE
#include <mutex>
#endif

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
#ifdef ENABLE_THREAD_SAFE
        std::lock_guard<std::mutex> lg(m);
#endif
        static_assert(std::is_base_of<IService, T>::value == true, "T must be derived from IService.");
        this->service[typeid(T)] = service;
    }

    template<typename T>
    void UnregisterService()
    {
#ifdef ENABLE_THREAD_SAFE
        std::lock_guard<std::mutex> lg(m);
#endif
        static_assert(std::is_base_of<IService, T>::value == true, "T must be derived from IService.");
        auto& it = service.find(typeid(T));
        if(it != service.end()){
            service.erase(it);
        }
    }

    template<typename T>
    std::weak_ptr<T> GetService() const
    {
#ifdef ENABLE_THREAD_SAFE
        std::lock_guard<std::mutex> lg(m);
#endif
        static_assert(std::is_base_of<IService, T>::value == true, "T must be derived from IService.");
        auto& it = service.find(typeid(T));
        if(it != service.cend()){
            return std::dynamic_pointer_cast<T>(it->second);
        }
        //assert(!"Unbale to find a service.");
        return std::weak_ptr<T>();
    }

private:
    std::unordered_map<std::type_index, std::shared_ptr<IService>> service;
#ifdef ENABLE_THREAD_SAFE
    mutable std::mutex m;
#endif
};

}}