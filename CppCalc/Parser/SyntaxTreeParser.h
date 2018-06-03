#pragma once

#include <vector>

class Token;
class ExpressionSyntax;
class StatementSyntax;

class SyntaxTreeParser
{
public:
    SyntaxTreeParser();
    ~SyntaxTreeParser();

    ExpressionSyntax *parseExpression(std::vector<Token*> &tokens);
    std::vector<StatementSyntax*> *parseCompilationUnit(std::vector<Token*> &tokens);
};
