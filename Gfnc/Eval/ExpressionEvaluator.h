#pragma once

#include <cstdint>

class ExpressionSyntax;

class ExpressionEvaluator
{
public:
    ExpressionEvaluator();
    ~ExpressionEvaluator();

    int32_t eval(ExpressionSyntax *expr);
};
