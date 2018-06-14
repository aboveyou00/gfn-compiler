#pragma once

#include <cstdint>
#include <string>

namespace Gfn::Compiler
{
    class GfnCompiler
    {
    public:
        GfnCompiler();
        ~GfnCompiler();

        int32_t eval(const std::string &src);
    };
}
