#pragma once

#include <cstdint>
#include <string>

class CppCalc
{
public:
    CppCalc();
    ~CppCalc();

    int64_t Calculate(const std::string &src);
};
