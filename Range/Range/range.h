/*!
* @file range.h
* @brief Simple range class.
* @author Hasenpfote
* @date 2016/07/31
*/
#pragma once
#include <type_traits>
#include <cassert>

namespace example{ namespace range{

template <typename T>
class range_iterator final
{
    static_assert(std::is_integral<T>::value, "T must be a integer type.");

public:
    range_iterator() = default;
    ~range_iterator() = default;

    range_iterator(const range_iterator&) = default;
    range_iterator& operator = (const range_iterator&) = default;
    range_iterator(range_iterator&&) = default;
    range_iterator& operator = (range_iterator&&) = default;

    explicit range_iterator(T position)
        : position(position)
    {
    }

    bool operator == (const range_iterator& rhs) const
    {
        return position == rhs.position;
    }

    bool operator != (const range_iterator& rhs) const
    {
        return position != rhs.position;
    }

    range_iterator& operator ++ ()
    {
        ++position;
        return *this;
    }

    range_iterator operator ++ (int)
    {
        range_iterator temp = *this;
        ++position;
        return temp;
    }

    T& operator * ()
    {
        return position;
    }

    const T& operator * () const
    {
        return position;
    }

private:
    T position;
};

template <typename T>
class range final
{
    static_assert(std::is_integral<T>::value, "T must be a integer type.");

public:
    using iterator = range_iterator<T>;

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