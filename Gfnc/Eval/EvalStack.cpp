#include "stdafx.h"
#include "Eval/EvalStack.h"

namespace Gfn::Compiler::Eval
{
    EvalStack::EvalStack()
    {
    }
    EvalStack::~EvalStack()
    {
    }

    int32_t EvalStack::peek() const
    {
        return this->m_stack.top();
    }

    uint32_t EvalStack::size() const
    {
        return (uint32_t)this->m_stack.size();
    }

    int32_t EvalStack::pop()
    {
        auto val = this->m_stack.top();
        this->m_stack.pop();
        return val;
    }

    std::tuple<int32_t, int32_t> EvalStack::pop2()
    {
        auto val2 = this->pop();
        auto val1 = this->pop();
        return std::tuple<int32_t, int32_t>(val1, val2);
    }

    void EvalStack::push(int32_t val)
    {
        this->m_stack.push(val);
    }
}
