#pragma once

#include "Parser/Syntax.h"

#include <stack>

class Token;
class Opcode;

class ExpressionSyntax
    : public Syntax
{
public:
    static ExpressionSyntax *tryParse(Cursor<Token*> &cursor);

public:
    ExpressionSyntax(uint32_t startIndex, uint32_t length);
    ~ExpressionSyntax();

    virtual void emit(std::vector<Opcode*> &ops) const = 0;
};

template <typename T>
inline ExpressionSyntax *tryParseSyntax(Cursor<Token*> &cursor)
{
    static_assert(std::is_base_of<ExpressionSyntax, T>::value, "tryParseSyntax only works on types that extend ExpressionSyntax");
    return T::tryParse(cursor);
}
template <typename T>
inline ExpressionSyntax *parseSyntax(Cursor<Token*> &cursor)
{
    auto result = tryParseSyntax<T>(cursor);
    if (result == nullptr) throw std::logic_error("Failed to parse syntax."s);
    return result;
}
