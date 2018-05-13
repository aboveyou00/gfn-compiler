#pragma once

#include "Emit/Opcode.h"

#include <cstdint>

class OpLdcI4
    : public Opcode
{
public:
    OpLdcI4(int32_t val);
    ~OpLdcI4();

    int32_t value() const;

    virtual void eval(EvalStack &stack) const override;

private:
    int32_t m_val;
};
