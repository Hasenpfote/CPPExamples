#include <iostream>
#include "singleton.h"
#include "foo.h"
#include "bar.h"

void main()
{
    Bar::GetMutableInstance();
    Foo::GetMutableInstance();
}