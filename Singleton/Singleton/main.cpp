#include <iostream>
#include <chrono>
#include <thread>
#include <cassert>
#include "foobar.h"

void do_something1()
{
    Foo::Vector v;
    v.push_back(1);
    v.push_back(2);
    v.push_back(3);
    const int count = 100000;
    int i = 0;
    while(i < count)
    {
        auto& ref = Foo::GetConstInstance(v);
    }
}

void do_something2()
{
    const int count = 100000;
    int i = 0;
    while (i < count)
    {
        auto& ref = Foo::GetConstInstance(4,5,6);
    }
}

int main()
{
    std::cout << __func__ << ": begin" << std::endl;
#if 1
    {
        Foo::Vector v;
        v.push_back(1);
        auto& ref1 = Foo::GetMutableInstance(v);
        auto& ref2 = Foo::GetConstInstance(4, 5, 6);
        std::cout << "0x" << &ref1 << std::endl;
        std::cout << "0x" << &ref2 << std::endl;
        assert(&ref1 == &ref2);
        ref1.Func();
        ref2.Func();
    }
#endif
#if 1
    const int count = 100;
    int i = 0;
    auto start = std::chrono::system_clock::now();
    while(i < count)
    {
        auto& ref = Foo::GetConstInstance(4, 5, 6);
        i++;
    }
    auto end = std::chrono::system_clock::now();
    auto diff = end - start;
    std::cout << "elapsed time = " << std::chrono::duration_cast<std::chrono::nanoseconds>(diff).count() << " nsec." << std::endl;
#else
    std::thread th1(do_something1);
    std::thread th2(do_something2);
    th1.join();
    th2.join();
#endif
    std::cout << __func__ << ": end" << std::endl;
    return 1;
}