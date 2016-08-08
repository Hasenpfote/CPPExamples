#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
#include "range.h"

using irange = example::range::range<int>;

std::vector<irange> RemoveOverlaps(const std::vector<irange>& ranges)
{
    auto temp = ranges;
    //
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
    //
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
    //
    std::vector<irange> result;
    result.reserve(temp.size());
    for(auto it = temp.begin(); it != temp.end(); ++it){
        auto b = *it->begin();
        auto e = *it->end();
        for(auto it2 = it + 1; it2 != temp.end(); ++it2){
            if(*it2->end() <= e){
                it = it2;
            }
            else
            if(*it2->begin() <= e){
                e = *it2->end();
                it = it2;
            }
            else{
                break;
            }
        }
        result.emplace_back(b, e);
    }
    result.shrink_to_fit();
    return result;
}

void test(const example::range::range<int>& range)
{
    std::cout << "Basic for loops:" << std::endl;
    for(auto it = range.begin(); it != range.end(); ++it){
        std::cout << *it << ' ';
    }
    std::cout << std::endl;
    //
    std::cout << "Range-based for loops:" << std::endl;
    for(auto value : range){
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
        v.emplace_back(4, 9);
        v.emplace_back(0, 1);
        //v.emplace_back(6, 2);
        v.emplace_back(2, 4);
        v.emplace_back(0, 3);
        v.emplace_back(11,15);
        v.emplace_back(3, 5);

        std::cout << "before" << std::endl;
        for(auto& r : v){
            std::cout << *(r.begin()) << " - " << *(r.end()) << std::endl;
        }

        auto v2 = RemoveOverlaps(v);

        std::cout << "after" << std::endl;
        for(auto& r : v2){
            std::cout << *(r.begin()) << " - " << *(r.end()) << std::endl;
        }
    }
}