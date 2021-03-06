#include "stdafx.h"
#include "Emit/BranchingOpcode.h"

namespace Gfn::Compiler::Emit
{
    BranchingOpcode::BranchingOpcode(OpcodeTag *tag)
        : m_tag(tag)
    {
    }
    BranchingOpcode::~BranchingOpcode()
    {
    }

    OpcodeTag *BranchingOpcode::tag() const
    {
        return this->m_tag;
    }

    void BranchingOpcode::eval(Eval::EvalStack&) const
    {
        throw std::logic_error("Branch instructions can't be evaluated using just the stack."s);
    }
}
