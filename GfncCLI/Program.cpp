#include "stdafx.h"

#include <iostream>

#include "GfnCompiler.h"

using namespace Gfn::Compiler;

int32_t main(uint32_t, char**)
{
    GfnCompiler calc;

    auto expr = "2 < 5"s;

    std::cout << expr << " = "s << calc.eval(expr) << std::endl;

    int val;
    std::cin >> val;

    return 0;
}
