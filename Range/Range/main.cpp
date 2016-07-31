#include <iostream>
#include "range.h"

void main()
{
    using namespace example::range;

    const auto r = range<int>(-10, 1);

    for(auto& it = r.begin(); it != r.end(); it++){
        std::cout << *it << std::endl;
    }

    for(auto& i : r){
        std::cout << i << std::endl;
    }
}