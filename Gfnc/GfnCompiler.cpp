#include "stdafx.h"

#include "GfnCompiler.h"

#include "Tokenizer/Tokenizer.h"
#include "Tokenizer/Token.h"
#include "Parser/SyntaxTreeParser.h"
#include "Parser/ExpressionSyntax.h"
#include "Eval/ExpressionEvaluator.h"
#include "Runtime/RuntimeType.h"

namespace Gfn::Compiler
{
    GfnCompiler::GfnCompiler()
    {
        Runtime::RuntimeType::prepareRuntimeTypes();
    }
    GfnCompiler::~GfnCompiler()
    {
    }

    int32_t GfnCompiler::eval(const std::string &src)
    {
        Tokenizer::Tokenizer tokenizer;
        auto tokens = tokenizer.tokenize(src);

        Parser::SyntaxTreeParser parser;
        auto expr = parser.parseExpression(*tokens);

        if (!expr->tryResolveType()) throw std::logic_error("Failed to resolve expression type."s);

        Eval::ExpressionEvaluator evaluator;
        auto result = evaluator.eval(expr);

        for (auto iter = tokens->begin(); iter != tokens->end(); iter++)
        {
            delete *iter;
        }
        tokens->clear();
        delete tokens;
        delete expr;

        return result;
    }
}
