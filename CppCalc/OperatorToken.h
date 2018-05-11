#pragma once

#include "Token.h"

class OperatorToken :
    public Token
{
public:
    OperatorToken(uint32_t startIndex, uint32_t length, std::string op);
    ~OperatorToken();

    virtual bool isOperator() const override;
    virtual const std::string &op() const override;

    virtual void repr(std::stringstream &stream) const override;

private:
    std::string m_op;
};

