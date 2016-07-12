#pragma once
#include <cassert>

namespace example{ namespace service{

template<typename T>
void ServiceLocator::RegisterService(const std::shared_ptr<IService>& service)
{
#ifdef ENABLE_THREAD_SAFE
    std::lock_guard<std::mutex> lg(m);
#endif
    static_assert(std::is_base_of<IService, T>::value == true, "T must be derived from IService.");
    this->service[typeid(T)] = service;
}

template<typename T>
void ServiceLocator::UnregisterService()
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
std::weak_ptr<T> ServiceLocator::GetService() const
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

}}