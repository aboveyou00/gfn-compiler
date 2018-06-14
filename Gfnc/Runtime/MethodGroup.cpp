#include "stdafx.h"
#include "Runtime/MethodGroup.h"

#include "Runtime/MethodOverload.h"

namespace Gfn::Compiler::Runtime
{
    MethodGroup::MethodGroup()
    {
    }
    MethodGroup::~MethodGroup()
    {
    }

    void MethodGroup::addOverload(MethodOverload *overload)
    {
        //TODO: ensure the overload does not shadow/is not shadowed by any other overload
        this->m_overloads.push_back(overload);
    }

    MethodOverload *MethodGroup::findOverload(const std::vector<RuntimeType*> &args) const
    {
        for (auto it = this->m_overloads.begin(); it != this->m_overloads.end(); it++)
        {
            auto overload = *it;
            auto overloadArgs = overload->argTypes();
            if (overloadArgs.size() != args.size()) continue;
            auto isSame = true;
            for (auto q = 0u; q < overloadArgs.size(); q++)
            {
                if (overloadArgs.at(q) != args.at(q))
                {
                    isSame = false;
                    break;
                }
            }
            if (!isSame) continue;

            return overload;
        }
        return nullptr;
    }
}
