#pragma once

#include "Eval/EvalStack.h"

class Opcode
{
public:
    Opcode();
    ~Opcode();

    virtual void eval(EvalStack &stack) const = 0;
};
