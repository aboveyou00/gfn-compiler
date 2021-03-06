#pragma once

#include "Emit/Opcode.h"

#include <cstdint>

namespace Gfn::Compiler::Emit
{
    class OpLdcI4
        : public Opcode
    {
    public:
        OpLdcI4(int32_t val);
        ~OpLdcI4();

        int32_t value() const;

        virtual void eval(Eval::EvalStack &stack) const override;

    private:
        int32_t m_val;
    };
}
