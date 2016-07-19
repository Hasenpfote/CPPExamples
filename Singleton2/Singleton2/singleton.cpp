#include "singleton.h"

namespace example{

std::stack<SingletonFinalizer::Callback> SingletonFinalizer::cbs;

void SingletonFinalizer::Register(const Callback& cb)
{
    cbs.push(cb);
}

void SingletonFinalizer::Finalize()
{
    while(!cbs.empty()){
        auto& cb = cbs.top();
        cb();
        cbs.pop();
    }
}

}