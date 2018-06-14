#include "stdafx.h"

#include "Parser/SyntaxTreeParser.h"

#include "Parser/ExpressionSyntax.h"
#include "Parser/StatementSyntax.h"
#include "Tokenizer/Token.h"

namespace Gfn::Compiler::Parser
{
    SyntaxTreeParser::SyntaxTreeParser()
    {
    }
    SyntaxTreeParser::~SyntaxTreeParser()
    {
    }

    ExpressionSyntax *SyntaxTreeParser::parseExpression(std::vector<Tokenizer::Token*> &tokens)
    {
        Cursor<Tokenizer::Token*> cursor(tokens.data(), (uint32_t)tokens.size());
        auto expr = tryParseSyntax<ExpressionSyntax>(cursor);

        if (cursor.isDone() || !cursor.current()->isEndOfFile())
        {
            throw std::invalid_argument("Failed to parse expression from tokens. Missing end of file.");
        }
        cursor.next();

        return expr;
    }

    std::vector<StatementSyntax*> *SyntaxTreeParser::parseCompilationUnit(std::vector<Tokenizer::Token*> &tokens)
    {
        auto statements = new std::vector<StatementSyntax*>();

        Cursor<Tokenizer::Token*> cursor(tokens.data(), (uint32_t)tokens.size());

        while (true)
        {
            if (cursor.isDone())
            {
                throw std::invalid_argument("Failed to parse compilation unit from tokens. Missing end of file.");
            }
            else if (cursor.current()->isEndOfFile())
            {
                cursor.next();
                break;
            }

            auto stmt = StatementSyntax::tryParse(cursor);
            if (!stmt)
            {
                throw std::invalid_argument("Failed to parse compilation unit from tokens. Missing end of file.");
            }
            statements->push_back(stmt);
        }

        return statements;
    }
}
