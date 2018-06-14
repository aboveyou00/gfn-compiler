#pragma once

#include "Emit/Opcode.h"

class OpNeg
    : public Opcode
{
public:
    OpNeg();
    ~OpNeg();

    virtual void eval(EvalStack &stack) const override;
};
