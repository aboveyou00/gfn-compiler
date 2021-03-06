#pragma once

#include <string>

#include "Util/Cursor.h"

namespace Gfn::Compiler::Tokenizer
{
    class Token;
    class IntegerLiteralToken;
    class StringLiteralToken;
    class OperatorToken;

    class Tokenizer
    {
    public:
        Tokenizer();
        ~Tokenizer();

        std::vector<Token*> *tokenize(const std::string &src);

    private:
        void collectWhitespace(Cursor<char> &cursor);
        Token *tryCollectToken(Cursor<char> &cursor);
        IntegerLiteralToken *tryCollectIntegerLiteralToken(Cursor<char> &cursor);
        StringLiteralToken *tryCollectStringLiteralToken(Cursor<char> &cursor);
        Token *tryCollectIdentifierOrKeywordToken(Cursor<char> &cursor);
        OperatorToken *tryCollectOperatorToken(Cursor<char> &cursor);

        bool isValidIdentifierStartChar(char chr);
        bool isValidIdentifierChar(char chr);
    };
}
