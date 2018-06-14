#pragma once

#include "Emit/Opcode.h"

class OpMul
    : public Opcode
{
public:
    OpMul();
    ~OpMul();

    virtual void eval(EvalStack &stack) const override;
};
