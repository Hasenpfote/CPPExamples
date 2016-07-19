#pragma once
#include <iostream>
#include "singleton.h"

class Bar : public example::Singleton<Bar>
{
    friend class example::Singleton<Bar>;

private:
    Bar()
    {
        std::cout << __func__ << std::endl;
    }
public:
    ~Bar()
    {
        std::cout << __func__ << std::endl;
    }
    void DoSomething()
    {
        std::cout << __func__ << std::endl;
    }
};
