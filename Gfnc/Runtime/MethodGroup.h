#pragma once

#include <vector>

namespace Gfn::Compiler::Runtime
{
    class RuntimeType;
    class MethodOverload;

    class MethodGroup
    {
    public:
        MethodGroup();
        ~MethodGroup();

        void addOverload(MethodOverload *overload);
        MethodOverload *findOverload(const std::vector<RuntimeType*> &args) const;

    private:
        std::vector<MethodOverload*> m_overloads;
    };
}
