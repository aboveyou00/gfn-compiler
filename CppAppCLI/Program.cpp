#include "stdafx.h"

#include <iostream>

#include "CppCalc.h"

int32_t main(uint32_t argc, char **argv)
{
    CppCalc calc;

    auto expr = "2 < 5 && true false true true true false (false) true"s;

    std::cout << expr << " = "s << calc.eval(expr) << std::endl;

    int val;
    std::cin >> val;

    return 0;
}
