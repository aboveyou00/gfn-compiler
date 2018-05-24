#pragma once

#include "Eval/EvalContext.h"
#include "Eval/EvalStack.h"

class OpcodeTag;

class Opcode
{
public:
    Opcode();
    ~Opcode();

    const std::vector<OpcodeTag*> &tags() const;
    bool hasTag(OpcodeTag *tag) const;

    void addTag(OpcodeTag *tag);

    virtual void eval(EvalContext &ctx) const;
    virtual void eval(EvalStack &stack) const = 0;

private:
    std::vector<OpcodeTag*> m_tags;
};
