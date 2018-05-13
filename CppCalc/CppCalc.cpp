#include "stdafx.h"

#include "CppCalc.h"

#include "Tokenizer/Tokenizer.h"
#include "Tokenizer/Token.h"
#include "Parser/SyntaxTreeParser.h"
#include "Parser/ExpressionSyntax.h"
#include "Eval/ExpressionEvaluator.h"

CppCalc::CppCalc()
{
}

CppCalc::~CppCalc()
{
}

int32_t CppCalc::eval(const std::string &src)
{
    Tokenizer tokenizer;
    auto tokens = tokenizer.tokenize(src);

    SyntaxTreeParser parser;
    auto expr = parser.parse(*tokens);

    ExpressionEvaluator evaluator;
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
