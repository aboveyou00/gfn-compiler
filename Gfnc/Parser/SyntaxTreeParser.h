#pragma once

#include <vector>

namespace Gfn::Compiler::Tokenizer
{
    class Token;
}

namespace Gfn::Compiler::Parser
{
    class ExpressionSyntax;
    class StatementSyntax;

    class SyntaxTreeParser
    {
    public:
        SyntaxTreeParser();
        ~SyntaxTreeParser();

        ExpressionSyntax *parseExpression(std::vector<Tokenizer::Token*> &tokens);
        std::vector<StatementSyntax*> *parseCompilationUnit(std::vector<Tokenizer::Token*> &tokens);
    };
}
