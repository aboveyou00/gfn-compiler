#pragma once

#include "Emit/BranchingOpcode.h"

class OpBrTrue
    : public BranchingOpcode
{
public:
    OpBrTrue(OpcodeTag *tag);
    ~OpBrTrue();

    virtual void eval(EvalContext &ctx) const override;
};
