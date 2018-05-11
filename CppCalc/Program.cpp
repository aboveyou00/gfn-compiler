#include "stdafx.h"

#include <iostream>

#include "CppCalc.h"

int32_t main(uint32_t argc, char **argv)
{
    CppCalc calculator;

    std::cout << "1 + 2 = " << calculator.Calculate("1 + 2") << std::endl;

    int val;
    std::cin >> val;

    return 0;
}
