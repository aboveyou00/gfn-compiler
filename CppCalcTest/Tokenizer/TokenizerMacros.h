#pragma once
#include "Tokenizer/Tokenizer.h"
#include "Tokenizer/Token.h"

#define TOKENIZE_SOURCE(str)\
    Tokenizer tokenizer;\
    auto tokens = tokenizer.tokenize(str);\
    auto currentTokenIdx = 0;

#define EXPECT_INTEGER_LITERAL(val)\
    {\
        auto tok = tokens->at(currentTokenIdx);\
        EXPECT_TRUE(tok != nullptr);\
        EXPECT_TRUE(tok->isIntLiteral());\
        EXPECT_TRUE(tok->intLiteral() == val);\
        currentTokenIdx++;\
    }

#define EXPECT_KEYWORD(val)\
    {\
        auto tok = tokens->at(currentTokenIdx);\
        EXPECT_TRUE(tok != nullptr);\
        EXPECT_TRUE(tok->isKeyword());\
        EXPECT_TRUE(tok->keyword() == val);\
        currentTokenIdx++;\
    }

#define EXPECT_BOOLEAN_LITERAL(val)\
    {\
        auto tok = tokens->at(currentTokenIdx);\
        EXPECT_TRUE(tok != nullptr);\
        EXPECT_TRUE(tok->isBooleanLiteral());\
        EXPECT_TRUE(tok->booleanLiteral() == val);\
        currentTokenIdx++;\
    }

#define EXPECT_ANY_INTEGER_LITERAL()\
    {\
        auto tok = tokens->at(currentTokenIdx);\
        EXPECT_TRUE(tok != nullptr);\
        EXPECT_TRUE(tok->isIntLiteral());\
        currentTokenIdx++;\
    }

#define EXPECT_OPERATOR(val)\
    {\
        auto tok = tokens->at(currentTokenIdx);\
        EXPECT_TRUE(tok != nullptr);\
        EXPECT_TRUE(tok->isOperator());\
        EXPECT_TRUE(tok->op() == val);\
        currentTokenIdx++;\
    }

#define EXPECT_ANY_OPERATOR()\
    {\
        auto tok = tokens->at(currentTokenIdx);\
        EXPECT_TRUE(tok != nullptr);\
        EXPECT_TRUE(tok->isOperator());\
        currentTokenIdx++;\
    }

#define EXPECT_END_OF_FILE()\
    {\
        auto tok = tokens->at(currentTokenIdx);\
        EXPECT_TRUE(tok != nullptr);\
        EXPECT_TRUE(tok->isEndOfFile());\
        currentTokenIdx++;\
    }

#define EXPECT_NO_MORE_TOKENS()\
    EXPECT_TRUE(tokens->size() == currentTokenIdx);
