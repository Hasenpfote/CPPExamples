#pragma once
#include <iterator>
#include <type_traits>
#include <cassert>
#include "detail/range_iterator_base.h"

namespace example{ namespace range{

template <typename T>
class range final
{
    static_assert(std::is_integral<T>::value, "T must be a integer type.");

public:
    struct iterator final : public detail::range_iterator_base<T>
    {
    public:
        iterator(T position) : range_iterator_base<T>(position) {}
    };

public:
    range() = delete;
    ~range() = default;

    range(const range&) = default;
    range& operator = (const range&) = default;
    range(range&&) = default;
    range& operator = (range&&) = default;

    range(const T& first, const T& last)
        : first(first), last(last)
    {
        assert(first <= last);
    }

    iterator begin() const
    {
        return iterator(first);
    }
    iterator end() const
    {
        return iterator(last);
    }

private:
    T first;
    T last;
};

}}