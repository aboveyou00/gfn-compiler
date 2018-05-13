#include "stdafx.h"
#include "Tokenizer/EndOfFileToken.h"

EndOfFileToken::EndOfFileToken(uint32_t startIndex)
    : Token(startIndex, 0)
{
}
EndOfFileToken::~EndOfFileToken()
{
}

bool EndOfFileToken::isEndOfFile() const
{
    return true;
}

void EndOfFileToken::repr(std::stringstream &stream) const
{
    stream << "%%EOF%%";
}
