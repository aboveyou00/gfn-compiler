#include "stdafx.h"
#include "Runtime/MethodOverload.h"

MethodOverload::MethodOverload(RuntimeType *returnType, std::vector<RuntimeType*> argTypes)
    : m_returnType(returnType), m_argTypes(argTypes), m_emitInvoke(nullptr)
{
}
MethodOverload::MethodOverload(RuntimeType *returnType, std::vector<RuntimeType*> argTypes, std::function<void(MethodBuilder &mb)> emitInvoke)
    : MethodOverload(returnType, argTypes)
{
    this->m_emitInvoke = emitInvoke;
}

MethodOverload::MethodOverload()
{
}
MethodOverload::~MethodOverload()
{
}

RuntimeType *MethodOverload::returnType() const
{
    return this->m_returnType;
}

const std::vector<RuntimeType*> &MethodOverload::argTypes() const
{
    return this->m_argTypes;
}

void MethodOverload::emitInvoke(MethodBuilder &mb) const
{
    if (this->m_emitInvoke == nullptr) throw std::logic_error("Can't emit invoke to a method overload that hasn't specified how to emit."s);
    this->m_emitInvoke(mb);
}
