#pragma once

#include "Parser/Syntax.h"

class Token;
class MethodBuilder;

class StatementSyntax
    : public Syntax
{
public:
    static StatementSyntax *tryParse(Cursor<Token*> &cursor);

public:
    StatementSyntax(uint32_t startIndex, uint32_t length);
    ~StatementSyntax();

    virtual bool tryResolveTypes() = 0;
    virtual void assertTypesAreResolved() const = 0;

    virtual void emit(MethodBuilder &mb) const = 0;
};
