#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
#include "range.h"

using irange = example::range::range<int>;

void func(const std::vector<irange>& ranges)
{
    auto temp = ranges;
    std::sort(
        temp.begin(),
        temp.end(),
        [](const irange& lhs, const irange& rhs) -> bool
        {
            if(*lhs.begin() < *rhs.begin())
                return true;
            if(*lhs.begin() > *rhs.begin())
                return false;
            return *lhs.end() < *rhs.end();
        }
    );
    temp.erase(
        std::unique(
                temp.begin(),
                temp.end(),
                [](const irange& lhs, const irange& rhs) -> bool
                {
                    if(*lhs.begin() != *rhs.begin())
                        return false;
                    if(*lhs.end() != *rhs.end())
                        return false;
                    return true;
                }
            ),
        temp.end()
    );

    for(auto& range : temp){
        std::cout << *(range.begin()) << " - " << *(range.end()) << std::endl;
    }
}

void test(const example::range::range<int>& range)
{
    std::cout << "Basic for loops:" << std::endl;
    for (auto& it = range.begin(); it != range.end(); ++it) {
        std::cout << *it << ' ';
    }
    std::cout << std::endl;
    //
    std::cout << "Range-based for loops:" << std::endl;
    for (auto value : range) {
        std::cout << value << ' ';
    }
    std::cout << std::endl;
    //
    std::cout << "for_each loops:" << std::endl;
    std::for_each(
        range.begin(),
        range.end(),
        [](int value){ std::cout << value << ' '; }
    );
    std::cout << std::endl;
    //
    auto it = std::find(range.begin(), range.end(), 3);
    //it++;
    std::cout << std::boolalpha << "find: " << (it != range.end()) << std::endl;
    //
    std::cout << "distance: " << std::distance(range.begin(), range.end()) << std::endl;
    //
    std::cout << "accumulate: " << std::accumulate(range.begin(), range.end(), 0) << std::endl;
}

void main()
{
    using namespace example::range;

    {
        std::cout << sizeof(range<int>) << std::endl;
        std::cout << sizeof(range<int>::iterator) << std::endl;
    }
    //
    {
        std::cout << "[case1]" << std::endl;
        test(range<int>(-5, 10));
        std::cout << "[case2]" << std::endl;
        test(range<int>(10, -5));
    }
    //
    {
        std::vector<irange> v;
        v.push_back(irange(3,5));
        v.push_back(irange(0,1));
        v.push_back(irange(2,4));
        v.push_back(irange(0,1));
        v.push_back(irange(2,3));
        v.push_back(irange(2,4));
        std::cout << "before" << std::endl;
        for(auto& r : v){
            std::cout << *(r.begin()) << " - " << *(r.end()) << std::endl;
        }

        std::cout << "after" << std::endl;
        func(v);
    }
}