#pragma once

#include "Emit/BranchingOpcode.h"

class OpBrFalse
    : public BranchingOpcode
{
public:
    OpBrFalse(OpcodeTag *tag);
    ~OpBrFalse();

    virtual void eval(EvalContext &ctx) const override;
};
