#pragma once
#include <functional>
#include <chrono>

template<typename F, typename... Args>
auto measure(F&& f, Args&& ... args)
{
    auto begin = std::chrono::steady_clock::now();
    std::invoke(std::forward<F>(f), std::forward<Args>(args)...);
    auto end = std::chrono::steady_clock::now();
    return end - begin;
}