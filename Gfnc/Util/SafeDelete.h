#pragma once

namespace Gfn::Compiler
{
    template <typename T>
    void SafeDelete(T *&ptr)
    {
        if (ptr != nullptr)
        {
            delete ptr;
            ptr = nullptr;
        }
    }

    template <typename T>
    void SafeDeleteArray(T **&ptr)
    {
        if (ptr != nullptr)
        {
            delete[] ptr;
            ptr = nullptr;
        }
    }
}
