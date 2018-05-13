#include "stdafx.h"

#include "Eval/ExpressionEvaluator.h"

#include "Parser/ExpressionSyntax.h"
#include "Emit/Opcode.h"
#include "Eval/EvalStack.h"

ExpressionEvaluator::ExpressionEvaluator()
{
}
ExpressionEvaluator::~ExpressionEvaluator()
{
}

int32_t ExpressionEvaluator::eval(ExpressionSyntax *expr)
{
    std::vector<Opcode*> ops;
    expr->emit(ops);

    EvalStack stack;
    for (auto it = ops.begin(); it != ops.end(); it++)
    {
        (*it)->eval(stack);
    }
    return stack.pop();
}
