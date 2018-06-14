#pragma once

#include <vector>
#include <functional>

namespace Gfn::Compiler::Emit
{
    class MethodBuilder;
}

namespace Gfn::Compiler::Runtime
{
    class RuntimeType;

    class MethodOverload
    {
    protected:
        MethodOverload(RuntimeType *returnType, std::vector<RuntimeType*> argTypes);

    public:
        MethodOverload(RuntimeType *returnType, std::vector<RuntimeType*> argTypes, std::function<void(Emit::MethodBuilder &mb)> emitInvoke);
        MethodOverload();
        ~MethodOverload();

        RuntimeType *returnType() const;
        const std::vector<RuntimeType*> &argTypes() const;
        virtual void emitInvoke(Emit::MethodBuilder &mb) const;

    private:
        RuntimeType *m_returnType;
        std::vector<RuntimeType*> m_argTypes;
        std::function<void(Emit::MethodBuilder &mb)> m_emitInvoke;
    };
}
