#pragma once
#include <cassert>

namespace example{namespace range{

template <typename T>
range_iterator<T>::range_iterator(T position)
    : position(position)
{
}

template <typename T>
bool range_iterator<T>::operator == (const range_iterator& rhs) const
{
    return position == rhs.position;
}

template <typename T>
bool range_iterator<T>::operator != (const range_iterator& rhs) const
{
    return position != rhs.position;
}

template <typename T>
range_iterator<T>& range_iterator<T>::operator ++ ()
{
    ++position;
    return *this;
}

template <typename T>
range_iterator<T> range_iterator<T>::operator ++ (int)
{
    range_iterator temp = *this;
    ++position;
    return temp;
}

template <typename T>
T& range_iterator<T>::operator * ()
{
    return position;
}

template <typename T>
const T& range_iterator<T>::operator * () const
{
    return position;
}

template <typename T>
range<T>::range(const T& first, const T& last)
    : first(first), last(last)
{
    assert(first <= last);
}

template <typename T>
typename range<T>::iterator range<T>::begin() const
{
    return iterator(first);
}

template <typename T>
typename range<T>::iterator range<T>::end() const
{
    return iterator(last);
}

}}