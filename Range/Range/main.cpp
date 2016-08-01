#include <iostream>
#include <vector>
#include <algorithm>
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

#if 0
    using CharRange = range<std::uint32_t>;

    const auto r = CharRange(1, 10);

    for(auto& it = r.begin(); it != r.end(); it++){
        std::cout << *it << std::endl;
    }

    for(auto& i : r){
        std::cout << i << std::endl;
    }
#else
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
#endif
}