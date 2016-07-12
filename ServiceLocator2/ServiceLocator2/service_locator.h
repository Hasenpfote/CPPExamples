/*!
* @file service_locator.h
* @brief Service locator class.
* @author Hasenpfote
* @date 2016/07/04
*/
#pragma once
#include <unordered_map>
#include <memory>
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
    void RegisterService(const std::shared_ptr<IService>& service);

    template<typename T>
    void UnregisterService();

    template<typename T>
    std::weak_ptr<T> GetService() const;

private:
    std::unordered_map<std::type_index, std::shared_ptr<IService>> service;
#ifdef ENABLE_THREAD_SAFE
    mutable std::mutex m;
#endif
};

}}

#include "impl/service_locator_impl.h"