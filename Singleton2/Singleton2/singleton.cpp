#include <iostream>
#include "singleton.h"

namespace example{

static std::stack<SingletonFinalizer::Callback> cbs;
static std::once_flag once;

void SingletonFinalizer::Register(const Callback& cb)
{
    std::cout << __func__ << std::endl;
    std::call_once(once, []()
    {
        std::cout << __func__ << "atexit" << std::endl;
        // 指定された関数は、プログラムの終了処理において、static変数の破棄が行われる前に呼び出される。
        std::atexit(SingletonFinalizer::Finalize);
    });
    cbs.push(cb);
}

void SingletonFinalizer::Finalize()
{
    std::cout << __func__ << std::endl;
    while(!cbs.empty()){
        auto& cb = cbs.top();
        cb();
        cbs.pop();
    }
}

}