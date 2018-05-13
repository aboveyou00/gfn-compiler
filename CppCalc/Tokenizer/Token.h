#pragma once

#include <cstdint>
#include <ostream>
#include <sstream>

class Token
{
public:
    Token(uint32_t startIndex, uint32_t length);
    ~Token();

    uint32_t startIndex() const;
    uint32_t length() const;
    uint32_t endIndex() const;

    virtual bool isIntLiteral() const;
    virtual uint64_t intLiteral() const;

    virtual bool isOperator() const;
    virtual const std::string &op() const;

    virtual bool isEndOfFile() const;

    virtual void repr(std::stringstream &stream) const = 0;
    std::string stringify() const;
    virtual void stringify(std::stringstream &stream) const;
    static friend std::stringstream &operator<<(std::stringstream &stream, const Token &tok);
    static friend std::ostream &operator<<(std::ostream &stream, const Token &tok);

private:
    uint32_t m_startIndex, m_length;
};
