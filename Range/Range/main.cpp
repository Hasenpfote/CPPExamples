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

void main()
{
    using namespace example::range;

    {
        std::cout << sizeof(range<int>) << std::endl;
        std::cout << sizeof(range<int>::iterator) << std::endl;
    }
    //
    {
        const auto r = range<int>(-5, 10);

        auto it = std::find(r.begin(), r.end(), 3);
        std::cout << "find: " << *it << std::endl;
        //
        std::cout << "distance: " << std::distance(r.begin(), r.end()) << std::endl;
        //
        std::cout << "accumulate: " << std::accumulate(r.begin(), r.end(), 0) << std::endl;
        //
        for(auto value : range<unsigned int>(0, 9)){
            std::cout << value << ' ';
        }
        std::cout << std::endl;
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