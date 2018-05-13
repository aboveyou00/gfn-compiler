#pragma once

#include <vector>

class Token;
class ExpressionSyntax;

class SyntaxTreeParser
{
public:
    SyntaxTreeParser();
    ~SyntaxTreeParser();

    ExpressionSyntax *parse(std::vector<Token*> &tokens);
};
