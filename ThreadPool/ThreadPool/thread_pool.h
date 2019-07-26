#pragma once
#include <cassert>
#include <thread>
#include <vector>
#include <functional>
#include <future>
#include "queue.h"

class ThreadPool
{
public:
    ThreadPool(std::size_t num_threads = std::thread::hardware_concurrency())
    {
        assert(num_threads > 0);
        for(decltype(num_threads) i = 0; i < num_threads; i++)
        {
            threads_.emplace_back(
                [this]
                {
                    while(true)
                    {
                        Process f;
                        if(!queue_.pop(f))
                            break;
                        f();
                    }
                }
            );
        }
    }

    virtual ~ThreadPool()
    {
        queue_.shutdown();
        for(auto& thread : threads_)
            thread.join();
    }

    ThreadPool(const ThreadPool&) = delete;
    ThreadPool& operator = (const ThreadPool&) = delete;
    ThreadPool(ThreadPool&&) = delete;
    ThreadPool& operator = (ThreadPool&&) = delete;

    template<typename F, typename... Args>
    void EnqueueWork(F&& f, Args&&... args)
    {
        queue_.push([=] { f(args...); });
    }

    template<typename F, typename... Args>
    auto EnqueueTask(F&& f, Args&&... args)
    {
#if (__cplusplus > 201402L) || (defined(_MSC_VER) && (_MSVC_LANG > 201402L))
        using result_type = std::invoke_result_t<F, Args...>;
#else
        using result_type = std::result_of_t<F(Args...)>;
#endif
        auto task = std::make_shared<std::packaged_task<result_type()>>(std::bind(std::forward<F>(f), std::forward<Args>(args)...));
        auto res = task->get_future();
        queue_.push([task] { (*task)(); });
        return res;
    }

private:
    using Process = std::function<void(void)>;
    blocking_queue<Process> queue_;

    std::vector<std::thread> threads_;
};