#pragma once

#include <cstdint>
#include <string>

class CppCalc
{
public:
    CppCalc();
    ~CppCalc();

    int32_t eval(const std::string &src);
};
