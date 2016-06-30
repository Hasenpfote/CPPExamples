#pragma once
#include <memory>
#include <unordered_map>

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
        return std::static_pointer_cast<T>(map[typeid(T).name()]).get();
    }
};