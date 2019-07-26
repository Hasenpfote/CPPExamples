#pragma once
#include <type_traits>
#include <queue>
#include <mutex>
#include <condition_variable>

template<typename T>
class blocking_queue final
{
public:
    blocking_queue() = default;
    ~blocking_queue() = default;

    blocking_queue(const blocking_queue&) = delete;
    blocking_queue& operator = (const blocking_queue&) = delete;
    blocking_queue(blocking_queue&&) = delete;
    blocking_queue& operator = (blocking_queue&&) = delete;

    template<typename U = T>
    std::enable_if_t<std::is_copy_constructible<U>::value, void>
    push(const T& item)
    {
        {
            std::unique_lock<std::mutex> lock(mutex_);
            queue_.push(item);
        }
        cv_.notify_one();
    }

    template<typename U = T>
    std::enable_if_t<std::is_move_constructible<U>::value, void>
    push(T&& item)
    {
        {
            std::unique_lock<std::mutex> lock(mutex_);
            queue_.emplace(std::move(item));
        }
        cv_.notify_one();
    }

    template<typename U = T>
    std::enable_if_t<std::is_copy_assignable<U>::value and not std::is_move_assignable<U>::value, bool>
    pop(T& item)
    {
        std::unique_lock<std::mutex> lock(mutex_);
        cv_.wait(lock, [this] { return is_done_ || !queue_.empty(); });
        if(queue_.empty())
            return false;
        item = queue_.front();
        queue_.pop();
        return true;
    }

    template<typename U = T>
    std::enable_if_t<std::is_move_assignable<U>::value, bool>
    pop(T& item)
    {
        std::unique_lock<std::mutex> lock(mutex_);
        cv_.wait(lock, [this] { return is_done_ || !queue_.empty(); });
        if(queue_.empty())
            return false;
        item = std::move(queue_.front());
        queue_.pop();
        return true;
    }

    void shutdown() noexcept
    {
        {
            std::unique_lock<std::mutex> lock(mutex_);
            is_done_ = true;
        }
        cv_.notify_all();
    }

    bool empty() const noexcept
    {
        std::lock_guard<std::mutex> lock(mutex_);
        return queue_.empty();
    }

    auto size() const noexcept
    {
        std::lock_guard<std::mutex> lock(mutex_);
        return queue_.size();
    }

private:
    std::queue<T> queue_;
    mutable std::mutex mutex_;
    std::condition_variable cv_;
    bool is_done_ = false;
};