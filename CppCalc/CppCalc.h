#pragma once

#include <cstdint>
#include <string>

class CppCalc
{
public:
    CppCalc();
    ~CppCalc();

    int64_t eval(const std::string &src);
};
