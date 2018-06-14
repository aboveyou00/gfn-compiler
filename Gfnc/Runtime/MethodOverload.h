#pragma once

#include <vector>
#include <functional>

class RuntimeType;
class MethodBuilder;

class MethodOverload
{
protected:
    MethodOverload(RuntimeType *returnType, std::vector<RuntimeType*> argTypes);

public:
    MethodOverload(RuntimeType *returnType, std::vector<RuntimeType*> argTypes, std::function<void(MethodBuilder &mb)> emitInvoke);
    MethodOverload();
    ~MethodOverload();

    RuntimeType *returnType() const;
    const std::vector<RuntimeType*> &argTypes() const;
    virtual void emitInvoke(MethodBuilder &mb) const;

private:
    RuntimeType *m_returnType;
    std::vector<RuntimeType*> m_argTypes;
    std::function<void(MethodBuilder &mb)> m_emitInvoke;
};
