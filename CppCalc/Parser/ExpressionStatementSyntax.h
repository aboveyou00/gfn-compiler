#pragma once
#include "Parser/StatementSyntax.h"

class ExpressionSyntax;

class ExpressionStatementSyntax :
    public StatementSyntax
{
public:
    static ExpressionStatementSyntax *tryParse(Cursor<Token*> &cursor);

public:
    ExpressionStatementSyntax(uint32_t startIndex, uint32_t length, ExpressionSyntax *expr);
    ~ExpressionStatementSyntax();

    ExpressionSyntax *expr() const;

    virtual bool tryResolveTypes() override;
    virtual void assertTypesAreResolved() const override;

    virtual void emit(MethodBuilder &mb) const override;

    virtual void repr(std::stringstream &stream) const;

private:
    ExpressionSyntax *m_expr;
};
