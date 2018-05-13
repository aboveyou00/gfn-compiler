#include "stdafx.h"

#include "Parser/SyntaxTreeParser.h"

#include "Parser/ExpressionSyntax.h"
#include "Tokenizer/Token.h"

SyntaxTreeParser::SyntaxTreeParser()
{
}
SyntaxTreeParser::~SyntaxTreeParser()
{
}

ExpressionSyntax *SyntaxTreeParser::parse(std::vector<Token*> &tokens)
{
    Cursor<Token*> cursor(tokens.data(), (uint32_t)tokens.size());
    auto expr = tryParseSyntax<ExpressionSyntax>(cursor);

    if (cursor.isDone() || !cursor.current()->isEndOfFile())
    {
        throw std::invalid_argument("Failed to parse expression from tokens. Missing end of file.");
    }
    cursor.next();

    return expr;
}
