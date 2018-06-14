#include "stdafx.h"
#include "Eval/EvalContext.h"

#include "Emit/Opcode.h"
#include "Emit/OpcodeTag.h"

EvalContext::EvalContext(const std::vector<Opcode*> &ops)
    : m_opcodes(ops)
{
}
EvalContext::~EvalContext()
{
}

const std::vector<Opcode*> &EvalContext::ops() const
{
    return this->m_opcodes;
}

EvalStack &EvalContext::stack()
{
    return this->m_stack;
}
uint32_t &EvalContext::nextInstructionIndex()
{
    return this->m_nextInstructionIndex;
}

void EvalContext::branchTo(OpcodeTag *tag)
{
    auto &ops = this->m_opcodes;
    for (auto q = 0u; q < ops.size(); q++)
    {
        auto instr = ops.at(q);
        if (instr->hasTag(tag))
        {
            this->m_nextInstructionIndex = q;
            return;
        }
    }
    throw std::logic_error("Can't branch to the tag \""s + tag->name() + "\". It doesn't exist!"s);
}
