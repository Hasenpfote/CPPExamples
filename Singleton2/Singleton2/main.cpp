#include <iostream>
#include "singleton.h"
#include "foo.h"
#include "bar.h"

void main()
{
    Foo::GetMutableInstance();
    Bar::GetMutableInstance();

    example::SingletonFinalizer::Finalize();
}