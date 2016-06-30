#pragma once
#include <memory>
#include <unordered_map>
#include <cassert>

class IService
{
public:
    IService() = default;
    virtual ~IService() = default;
};

class ServiceLocator final
{
private:
    static std::unordered_map<std::string, std::shared_ptr<IService>> map;

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