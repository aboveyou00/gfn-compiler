#pragma once

#include <vector>
#include <functional>

class RuntimeType;
class Opcode;

class MethodOverload
{
protected:
    MethodOverload(RuntimeType *returnType, std::vector<RuntimeType*> argTypes);

public:
    MethodOverload(RuntimeType *returnType, std::vector<RuntimeType*> argTypes, std::function<void(std::vector<Opcode*> &ops)> emitInvoke);
    MethodOverload();
    ~MethodOverload();

    RuntimeType *returnType() const;
    const std::vector<RuntimeType*> &argTypes() const;
    virtual void emitInvoke(std::vector<Opcode*> &ops) const;

private:
    RuntimeType *m_returnType;
    std::vector<RuntimeType*> m_argTypes;
    std::function<void(std::vector<Opcode*> &ops)> m_emitInvoke;
};
