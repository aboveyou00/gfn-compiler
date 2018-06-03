#pragma once
#include "Parser/StatementSyntax.h"

class ExpressionSyntax;

class PrintStatementSyntax :
    public StatementSyntax
{
public:
    static PrintStatementSyntax *tryParse(Cursor<Token*> &cursor);

public:
    PrintStatementSyntax(uint32_t startIndex, uint32_t length, ExpressionSyntax *expr, bool isPuts);
    ~PrintStatementSyntax();

    ExpressionSyntax *expr() const;
    bool isPuts() const;

    virtual bool tryResolveTypes() override;
    virtual void assertTypesAreResolved() const override;

    virtual void emit(MethodBuilder &mb) const override;

    virtual void repr(std::stringstream &stream) const;

private:
    ExpressionSyntax *m_expr;
    bool m_isPuts;
};
