#include "stdafx.h"

#include "Eval/ExpressionEvaluator.h"

#include "Parser/ExpressionSyntax.h"
#include "Emit/MethodBuilder.h"
#include "Emit/Opcode.h"
#include "Eval/EvalContext.h"

namespace Gfn::Compiler::Eval
{
    ExpressionEvaluator::ExpressionEvaluator()
    {
    }
    ExpressionEvaluator::~ExpressionEvaluator()
    {
    }

    int32_t ExpressionEvaluator::eval(Parser::ExpressionSyntax *expr)
    {
        Emit::MethodBuilder mb;
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
}
