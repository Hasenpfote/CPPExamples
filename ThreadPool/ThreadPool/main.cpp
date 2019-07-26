#include <iostream>
#include <sstream>
#include <cstdlib>
#include "measure.h"
#include "thread_pool.h"

const int COUNT = 100000;
const int REPS = 10;

void test1()
{
    srand(0);
    ThreadPool tp;
    for(int i = 0; i < COUNT; ++i)
        tp.EnqueueWork(
            [i]
            {
                int reps = REPS + (REPS * (rand() % 5));
                for (int n = 0; n < reps; ++n)
                    int x = i + rand();
            }
        );
}

void test2()
{
    ThreadPool tp;
    auto res = tp.EnqueueTask(
        []
        {
            return 123;
        }
    );
    std::cout << res.get() << std::endl;
}

int main()
{
    std::cout << _MSVC_LANG << std::endl;
#if 1
    test1();
    test2();
#else
    auto diff = std::chrono::duration_cast<std::chrono::milliseconds>(measure(test1));
    std::cout << diff.count() << std::endl;
#endif
    std::cout << "done." << std::endl;
}