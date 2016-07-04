/*!
* @file service.h
* @brief Service interface.
* @author Hasenpfote
* @date 2016/07/04
*/
#pragma once

namespace example{ namespace service{

class IService
{
public:
    IService() = default;
    virtual ~IService() = default;

    IService(const IService&) = delete;
    IService& operator = (const IService&) = delete;
    IService(IService&&) = delete;
    IService& operator = (IService&&) = delete;
};

}}