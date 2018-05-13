#pragma once

#include "Emit/Opcode.h"

class OpDiv
    : public Opcode
{
public:
    OpDiv();
    ~OpDiv();

    virtual void eval(EvalStack &stack) const override;
};
