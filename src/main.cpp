#include "FastPimpl.hpp"
#include "Example.h"

#include <iostream>

int main(int argc, char* argv[])
{
    utils::FastPimpl<Example, sizeof(Example), alignof(Example)> pimpl1;
    *pimpl1 = Example(42);

    utils::FastPimpl<Example, sizeof(Example), alignof(Example)> pimpl2 = std::move(pimpl1);

    std::cout << "Value: " << pimpl2->value << std::endl;
}