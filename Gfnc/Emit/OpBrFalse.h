#pragma once

#include "Emit/BranchingOpcode.h"

namespace Gfn::Compiler::Emit
{
    class OpBrFalse
        : public BranchingOpcode
    {
    public:
        OpBrFalse(OpcodeTag *tag);
        ~OpBrFalse();

        virtual void eval(Eval::EvalContext &ctx) const override;
    };
}
