#pragma once

#include <cstdint>

namespace Gfn::Compiler::Parser
{
    class ExpressionSyntax;
}

namespace Gfn::Compiler::Eval
{
    class ExpressionEvaluator
    {
    public:
        ExpressionEvaluator();
        ~ExpressionEvaluator();

        int32_t eval(Parser::ExpressionSyntax *expr);
    };
}
