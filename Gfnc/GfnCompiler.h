#pragma once

#include <cstdint>
#include <string>

class GfnCompiler
{
public:
    GfnCompiler();
    ~GfnCompiler();

    int32_t eval(const std::string &src);
};
