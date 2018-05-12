#include "stdafx.h"

#include "CppCalc.h"

#include <stack>

#include "Tokenizer.h"
#include "Token.h"
#include "SyntaxTreeParser.h"
#include "ExpressionSyntax.h"

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

    std::stack<int32_t> stack;
    expr->eval(stack);

    for (auto iter = tokens->begin(); iter != tokens->end(); iter++)
    {
        delete *iter;
    }
    tokens->clear();
    delete tokens;
    delete expr;

    return stack.top();
}
