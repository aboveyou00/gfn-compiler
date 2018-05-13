#pragma once

#include "Emit/Opcode.h"

class OpMod
    : public Opcode
{
public:
    OpMod();
    ~OpMod();

    virtual void eval(EvalStack &stack) const override;
};
