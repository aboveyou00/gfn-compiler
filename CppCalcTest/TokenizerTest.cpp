#include "pch.h"
#include "TokenizerMacros.h"

TEST(Tokenizer_tokenize, EmptyString) {
    TOKENIZE_SOURCE(""s);

    EXPECT_END_OF_FILE();
    EXPECT_NO_MORE_TOKENS();
}

TEST(Tokenizer_tokenize, IsolatedIntegerLiteral) {
    TOKENIZE_SOURCE("42"s);

    EXPECT_INTEGER_LITERAL(42);

    EXPECT_END_OF_FILE();
    EXPECT_NO_MORE_TOKENS();
}

TEST(Tokenizer_tokenize, IsolatedOperator) {
    TOKENIZE_SOURCE("*"s);

    EXPECT_OPERATOR("*"s);

    EXPECT_END_OF_FILE();
    EXPECT_NO_MORE_TOKENS();
}

TEST(Tokenizer_tokenize, NegativeIntegerLiteral) {
    TOKENIZE_SOURCE("-42"s);

    EXPECT_OPERATOR("-"s);
    EXPECT_INTEGER_LITERAL(42);

    EXPECT_END_OF_FILE();
    EXPECT_NO_MORE_TOKENS();
}

TEST(Tokenizer_tokenize, WhitespaceIntegerLiteral) {
    TOKENIZE_SOURCE("   42   "s);

    EXPECT_INTEGER_LITERAL(42);

    EXPECT_END_OF_FILE();
    EXPECT_NO_MORE_TOKENS();
}

TEST(Tokenizer_tokenize, BinaryExpression) {
    TOKENIZE_SOURCE("1 + 2"s);

    EXPECT_INTEGER_LITERAL(1);
    EXPECT_OPERATOR("+"s);
    EXPECT_INTEGER_LITERAL(2);

    EXPECT_END_OF_FILE();
    EXPECT_NO_MORE_TOKENS();
}

TEST(Tokenizer_tokenize, ComplexExpression) {
    TOKENIZE_SOURCE("(1 + 2) * 3"s);

    EXPECT_OPERATOR("("s);
    EXPECT_INTEGER_LITERAL(1);
    EXPECT_OPERATOR("+"s);
    EXPECT_INTEGER_LITERAL(2);
    EXPECT_OPERATOR(")"s);
    EXPECT_OPERATOR("*"s);
    EXPECT_INTEGER_LITERAL(3);

    EXPECT_END_OF_FILE();
    EXPECT_NO_MORE_TOKENS();
}
