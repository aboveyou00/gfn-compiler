#pragma once

#include "Emit/BranchingOpcode.h"

namespace Gfn::Compiler::Emit
{
    class OpBranch
        : public BranchingOpcode
    {
    public:
        OpBranch(OpcodeTag *tag);
        ~OpBranch();

        virtual void eval(Eval::EvalContext &ctx) const override;
    };
}
