#pragma once

#include "Emit/BranchingOpcode.h"

class OpBranch
    : public BranchingOpcode
{
public:
    OpBranch(OpcodeTag *tag);
    ~OpBranch();

    virtual void eval(EvalContext &ctx) const override;
};
