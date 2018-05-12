#pragma once

#include "Syntax.h"

#include <stack>

class Token;

class ExpressionSyntax
    : public Syntax
{
public:
    ExpressionSyntax(uint32_t startIndex, uint32_t length);
    ~ExpressionSyntax();

    static ExpressionSyntax *tryParse(Cursor<Token*> &cursor);

    virtual void eval(std::stack<int32_t> &stack) const = 0;
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
