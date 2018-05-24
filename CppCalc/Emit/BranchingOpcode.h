#pragma once

#include "Emit/Opcode.h"

class BranchingOpcode
    : public Opcode
{
public:
    BranchingOpcode(OpcodeTag *tag);
    ~BranchingOpcode();

    OpcodeTag *tag() const;

    virtual void eval(EvalContext &ctx) const = 0;
    virtual void eval(EvalStack &stack) const override;

private:
    OpcodeTag *m_tag;
};
