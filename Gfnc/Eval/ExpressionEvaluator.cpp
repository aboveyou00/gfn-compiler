#include "stdafx.h"

#include "Eval/ExpressionEvaluator.h"

#include "Parser/ExpressionSyntax.h"
#include "Emit/MethodBuilder.h"
#include "Emit/Opcode.h"
#include "Eval/EvalContext.h"

ExpressionEvaluator::ExpressionEvaluator()
{
}
ExpressionEvaluator::~ExpressionEvaluator()
{
}

int32_t ExpressionEvaluator::eval(ExpressionSyntax *expr)
{
    MethodBuilder mb;
    expr->emit(mb);
    mb.finalize();

    auto &ops = mb.ops();
    EvalContext ctx(ops);

    while (ctx.nextInstructionIndex() != ops.size())
    {
        auto instr = ops.at(ctx.nextInstructionIndex()++);
        instr->eval(ctx);
    }

    return ctx.stack().pop();
}
